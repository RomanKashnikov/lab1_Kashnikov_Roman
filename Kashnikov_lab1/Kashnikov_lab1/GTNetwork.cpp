#include <iostream>
#include <fstream>

#include "GTNetwork.h"
#include "filter.h"
#include "Kan_by_Volkov.h"
#include "Deikstra.h"
#include "Edmonds_Karp.h"


using namespace std;


bool GTNetwork::create_graph() {
    int counter = 0;
    this->graph.clear();

    for (const auto& [id, cs] : this->AllCS) {
        auto neighbours_AllPipe = cs.get_links()[1]; // ��������� �����
        if (neighbours_AllPipe.size()) {
            for (const auto& pipe_id : neighbours_AllPipe)
                this->graph[id].emplace(this->AllPipe.at(pipe_id).get_links()[1]);
        }
        else if (cs.InUsing()) {
            this->graph[id] = {};
        }
        ++counter;
    }
    return bool(counter);
}


void GTNetwork::print_graph() const {
    cout << "graph:" << endl;
    for (const auto& pair : this->graph) {
        cout << pair.first << ":";
        for (const auto& v : pair.second) {
            cout << " " << v;
        }
        cout << endl;
    }
}


bool GTNetwork::add_node() {
    if (AllCS.size() < 2)
        return false;

    unordered_set<int> values = { 500, 700, 1000, 1400 };

    int output_id;
    int input_id;
    int diameter;

    // ������ ������� �����
    do {
        output_id = input_validation<int>("Output id:  ", 0, CS::get_MaxID());
    } while (!AllCS.count(output_id));

    // ���� ������� �����
    do {
        input_id = input_validation<int>("Input id:  ", 0, CS::get_MaxID());
    } while (!AllCS.count(output_id) || input_id == output_id);

    do {
        diameter = input_validation<int>("Input diameter (500/700/1000/1400):  ", 0, 1400);
    } while (!values.count(diameter));
    
    int length = this->getAbsoluteDistance(output_id, input_id);
    int pipe_id = find_by_diameter(diameter, length);

    this->AllCS.at(output_id).addLink(1, pipe_id);
    this->AllPipe.at(pipe_id).set_links(output_id, input_id);
    this->AllCS.at(input_id).addLink(0, pipe_id);
    return true;
}


bool GTNetwork::make_TS() {
    this->order = Kan_by_Volkov(this->graph);

    cout << "TS: ";
    if (this->order.size()) {
        for (const auto& v : this->order)
            cout << v << " ";
    }
    else {
        cout << "graph has cycle or TS is empty set!" << endl;
    }

    cout << endl;

    return 1;
}


bool GTNetwork::eraseObjFromGraph(Pipe& pipe) {
    this->AllCS.at(pipe.get_links()[0]).delLink(1, pipe.get_id());
    this->AllCS.at(pipe.get_links()[1]).delLink(0, pipe.get_id());
    pipe.set_links(0, 0);

    return 1;
}


bool GTNetwork::eraseObjFromGraph(CS& cs) {
    for (auto& neig : cs.get_links()) {
        for (auto& pipe : neig) {
            this->eraseObjFromGraph(this->AllPipe.at(pipe));
        }
    }

    return 1;
}


bool GTNetwork::clear_graph() {
    for (auto& [id, _] : this->graph) {
        this->eraseObjFromGraph(this->AllCS.at(id));
    }
    return 1;
}


bool GTNetwork::save_objects() const  {
    string path_to_file;
    int counter = 0;

    cout << "Save in ... .txt" << endl;
    name_validation(path_to_file);

    ofstream file("objects/" + path_to_file + ".txt");

    if (file.is_open()) {
        file << Pipe::get_MaxID() << endl;
        file << CS::get_MaxID() << endl;

        if (!AllPipe.empty()) {
            for (auto& [_, pipe] : AllPipe) {
                pipe.save(file);
                ++counter;
            }
        }

        if (!AllCS.empty()) {
            for (auto& [_, cs] : AllCS) {
                cs.save(file);
                ++counter;
            }
        }

        file.close();

        cout << counter << " objects was saved" << endl;
        return 1;
    }
    else {
        cout << "Error opening file" << endl;
        return 0;
    }

}


bool GTNetwork::download_objects() {
    string path_to_file;
    int counter = 0;

    cout << "Download from ... .txt" << endl;
    name_validation(path_to_file);

    ifstream file("objects/" + path_to_file + ".txt");

    if (file.is_open()) {
        this->AllPipe.clear();
        this->FilteredPipe.clear();

        this->AllCS.clear();
        this->FilteredCS.clear();

        string line;

        file >> line;
        Pipe::set_MaxID(atoi(line.c_str()));
        file >> line;
        CS::set_MaxID(atoi(line.c_str()));

        while (file >> line) {
            if (line == "Pipe") {
                load_obj(file, AllPipe);
                ++counter;
            }

            if (line == "CS") {
                load_obj(file, AllCS);
                ++counter;
            }
        }

        file.close();

        cout << counter << " objects was added" << endl;
    }
    else {
        cout << "Error opening file" << endl;
        return 0;
    }
    return 1;
}


ostream& operator << (ostream& os, const GTNetwork& gtn) {
    if (gtn.AllPipe.empty()) {
        cout << "No AllPipe" << endl;
    }
    else {
        for (auto& pipe : gtn.AllPipe) {
            os << pipe.second << endl;
        }
    }

    if (gtn.AllCS.empty()) {
        cout << "No compressor stations" << endl;
    }
    else {
        for (auto& cs : gtn.AllCS) {
            cout << cs.second << endl;
        }
    }

    return os;
}


bool GTNetwork::change_status_of_repair() {
    int counter = 0;

    bool new_status = input_validation<bool>("Enter new status of repair:  ", 0, 1);

    for (const int& id : this->FilteredPipe) {
        this->AllPipe.find(id)->second.set_repair(new_status);
        ++counter;
    }
    cout << counter << " AllPipe were changed!" << endl;
    return 1;
}

bool GTNetwork::change_workload() {
    cout << "Editing workspaces in work" << endl << endl;
    cout << "0 - Stop workspace\n1 - Start workspace\n2 - Exit" << endl << endl;

    int operation;

    do {
        operation = input_validation<int>("Enter command:  ", 0, 2);

        switch (operation)
        {
        case 0:
            for (const int& id : FilteredCS) {
                AllCS.find(id)->second.stop_workspace();
            }
            break;
        case 1:
            for (const int& id : FilteredCS) {
                AllCS.find(id)->second.start_workspace();
            }
            break;
        }
    } while (operation != 2);
    return 0;
}


bool GTNetwork::delPipeFromGraph() {
    cout << "0 - Exit" << endl << endl;

    int id;

    while (true) {
        do {
            id = input_validation<int>("Input id:  ", 0, Pipe::get_MaxID());
            if (id == 0) break;
        } while (!AllPipe.count(id));

        if (id == 0) break;

        if (this->AllPipe.at(id).InUsing())
            this->eraseObjFromGraph(this->AllPipe.at(id));
    }

    return 1;
}

bool GTNetwork::delCSFromGraph() {
    cout << "0 - Exit" << endl << endl;

    int id;

    while (true) {
        do {
            id = input_validation<int>("Input id:  ", 0, CS::get_MaxID());
            if (id == 0) break;
        } while (!AllCS.count(id));

        if (id == 0) break;

        if (this->AllCS.at(id).InUsing())
            this->eraseObjFromGraph(this->AllCS.at(id));
    }

    return 1;
}


int GTNetwork::add_Pipe() {
    Pipe pipe;
    cin >> pipe;
    this->AllPipe.emplace(pipe.get_id(), pipe);

    return pipe.get_id();
}

int GTNetwork::add_CS() {
    CS cs;
    cin >> cs;
    this->AllCS.emplace(cs.get_id(), cs);

    return cs.get_id();
}


void GTNetwork::print_filtered_pipes() const {
    cout << "------------------------------\n        Filtered Pipes\n------------------------------" << endl << endl;
    if (this->FilteredPipe.size() == 0)
        cout << "No selected AllPipe!" << endl;

    for (const int& id : this->FilteredPipe) {
        cout << this->AllPipe.find(id)->second << endl;
    }
}


void GTNetwork::print_filtered_CS() const {
    if (this->FilteredCS.size() == 0)
        cout << "No selected CS!" << endl;

    for (const int& id : this->FilteredCS) {
        cout << this->AllCS.find(id)->second << endl;
    }
}

bool GTNetwork::set_pipes_by_id(const bool& choice) {
    if (!choice)
        this->FilteredPipe = this->filter_by_id(this->AllPipe);
    else
        this->FilteredPipe = this->filter_by_id(this->FilteredPipe);

    return 1;
}

bool GTNetwork::set_cs_by_id(const bool& choice) {
    if (!choice)
        this->FilteredCS = this->filter_by_id(this->AllCS);
    else
        this->FilteredCS = this->filter_by_id(this->FilteredCS);

    return 1;
}


bool GTNetwork::clear_selected(const bool& choice) {
    if (!choice)
        this->FilteredPipe.clear();
    else
        this->FilteredCS.clear();

    return 1;
}


bool GTNetwork::find_pipes_by_name() {
    cout << "Input name: ";
    string name;

    name_validation(name);

    find_by_filter(this->AllPipe, this->FilteredPipe, &GTNetwork::check_name, name);
    return 1;
}


bool GTNetwork::find_cs_by_name() {
    cout << "Input name: ";
    string name;

    name_validation(name);

    find_by_filter(this->AllCS, this->FilteredCS, &GTNetwork::check_name, name);
    return 1;
}


bool GTNetwork::select_all_pipes() {
    for (const auto& pair : this->AllPipe) {
        this->FilteredPipe.emplace(pair.first);
    }
    return 1;
}

bool GTNetwork::select_all_cs() {
    for (const auto& pair : this->AllCS) {
        this->FilteredCS.emplace(pair.first);
    }
    return 1;
}


bool GTNetwork::delete_selected_pipes() {
    int counter = 0;
    for (auto it = this->FilteredPipe.begin(); it != this->FilteredPipe.end();) {
        if (!this->AllPipe.at(*it).InUsing()) {
            erase_obj(this->AllPipe, *it);
            it = this->FilteredPipe.erase(it);
            ++counter;
        }
        else {
            cout << "Pipe " << *it << " used in graph" << endl;
            ++it;
        }
    }
    cout << counter << " AllPipe was erased!" << endl;
    return 1;
}


bool GTNetwork::delete_selected_cs() {
    int counter = 0;
    for (auto it = this->FilteredCS.begin(); it != this->FilteredCS.end();) {
        if (!this->AllCS.at(*it).InUsing()) {
            erase_obj(this->AllCS, *it);
            it = this->FilteredCS.erase(it);
            ++counter;
        }
        else {
            cout << "CS " << *it << " used in graph" << endl;
            ++it;
        }
    }
    cout << counter << " CS was erased!" << endl;
    return 1;
}

unordered_set<int> GTNetwork::get_IncidentPipes(const int& id_1, const int& id_2) {
    unordered_set<int> result = {};
    auto neighbours_pipes = this->AllCS.at(id_1).get_links()[1]; // ��������� �����
    for (const auto& pipeID : neighbours_pipes) {
        const Pipe& pipe = this->AllPipe.at(pipeID);
        if (pipe.get_links()[1] == id_2)
            result.emplace(pipeID);
    }
    return result;
}


int GTNetwork::getDistance(const int& id_1, const int& id_2) {
    const unordered_set<int> incidentPipes = this->get_IncidentPipes(id_1, id_2);
    if (!incidentPipes.size())
        return this->INF;

    for (const auto& pipeID : incidentPipes) {
        if (this->AllPipe.at(pipeID).get_repair())
            return this->AllPipe.at(pipeID).get_length();
    }
    return this->INF;
}


int GTNetwork::getAbsoluteDistance(const int& id_1, const int& id_2) {
    int len_1 = this->getDistance(id_1, id_2);
    int len_2 = this->getDistance(id_2, id_1);
    return min(len_1, len_2);
}


bool GTNetwork::show_MinPath() {
    cout << "min path: ";
    if (!this->min_path.size()) {
        cout << "cant find min path!" << endl;
        return 0;
    }
    if (this->min_path.size() > 1) {
        int dist = 0;
        for (int i = 0; i < this->min_path.size() - 1; ++i) {
            dist += this->getDistance(this->min_path[i], this->min_path[i + 1]);
            cout << this->min_path[i] << " ";
        }
        cout << this->min_path[this->min_path.size() - 1] << endl;
        cout << "Distance: " << dist << endl;
    }
    else {
        cout << this->min_path[0] << endl;
        cout << "Distance: " << 0 << endl;
    }
    cout << endl;
    return 1;
}


bool GTNetwork::find_min_dist() {
    if (!this->graph.size()) {
        cout << "No graph" << endl;
        return 0;
    }
    
    int start_id;
    int stop_id;

    //�����
    do {
        start_id = input_validation<int>("Start id:  ", 0, CS::get_MaxID());
    } while (!AllCS.count(start_id));

    //�����
    do {
        stop_id = input_validation<int>("Stop id:  ", 0, CS::get_MaxID());
    } while (!AllCS.count(stop_id) || start_id == stop_id);

    this->min_path = this->metodDeikstra(start_id, stop_id);

    return this->show_MinPath();
}


int GTNetwork::getCapacity(const int& id_1, const int& id_2) {
    const unordered_set<int> incidentPipes = this->get_IncidentPipes(id_1, id_2);
    int capacity = 0;
    for (const auto& pipeID : incidentPipes) {
        capacity += this->AllPipe.at(pipeID).get_MAXperfomance();
    }
    return capacity;
}


bool GTNetwork::show_maxFlow() {
    cout << "max flow path: ";
    for (const auto& csID : this->maxFlow_path) {
        cout << csID << " ";
    }
    cout << endl;

    cout << "max flow: " << this->maxFlow << endl;

    return 1;
}
bool GTNetwork::count_maxFlow() {
    if (!this->graph.size()) {
        cout << "No graph!" << endl;
        cout << "Max flow: 0" << endl;
        return 0;
    }

    int source_id;
    int sink_id;

    //�����
    do {
        source_id = input_validation<int>("Source id:  ", 0, CS::get_MaxID());
    } while (!AllCS.count(source_id));

    //�����
    do {
        sink_id = input_validation<int>("Sink id:  ", 0, CS::get_MaxID());
    } while (!AllCS.count(sink_id) || source_id == sink_id);

    
    vector<int> flowPath = this->metodDeikstra(source_id, sink_id);
    if (!flowPath.size()) {
        cout << "No path to flow: max flow = 0" << endl;
    }
    else if (flowPath.size() == 1) {
        cout << "max flow: INF" << endl;
        cout << "max flow path: " << flowPath[0] << endl;
    }
    else {
        this->maxFlow = this->edmondsKarp<int>(source_id, sink_id);
        return this->show_maxFlow();
    }
}