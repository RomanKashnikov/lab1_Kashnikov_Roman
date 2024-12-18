#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "pipe.h"
#include "utils.h"

using namespace std;


int Pipe::MaxID = 0;


int Pipe::get_MaxID() {
    return Pipe::MaxID;
}

int Pipe::get_id() const {
    return this->id;
}

string Pipe::get_name() const {
    return this->name;
}

int Pipe::get_diameter() const {
    return this->diameter;
}

int Pipe::get_length() const {
    return this->lenght;
}

int Pipe::get_MAXperfomance() const {
    return this->MAXperfomance * this->repair;
}

bool Pipe::get_repair() const {
    return this->repair;
}

vector<int> Pipe::get_links() const {
    return this->links;
}

bool Pipe::set_links(const int& out, const int& in) {
    this->links = {out, in};
    return 1;
}

void Pipe::set_repair(const bool new_repair) {
    this->repair = new_repair;
}

void Pipe::set_MaxID(const int new_MaxID){
    Pipe::MaxID = new_MaxID;
}

bool Pipe::InUsing() const {
    return (this->links[0]) || (this->links[1]);
}

Pipe::Pipe() {
    id = ++MaxID;
    lenght = 0;
    diameter = 0;
    MAXperfomance = 0;
    repair = false;
    name = "No Name";
}

Pipe::Pipe(const int& dmtr, const int& lenght) {
    cout << "Add a Pipe:" << endl << endl;

    cout << "Diameter:  " << dmtr << endl << endl;

    id = ++MaxID;

    name_validation(name);

    if (lenght != std::numeric_limits<int>::max()) {
        this->lenght = lenght;
    }
    else {
        this->lenght = input_validation<double>("Input lenght:  ", 0.000001, 2147483647);
    }

    diameter = dmtr;

    MAXperfomance = dictPerfomances.at(diameter);

    repair = input_validation<bool>("Is in repair? (1-Yes/0-No):  ", 0, 1);
}

void Pipe::save(ofstream& file) const {
    file << "Pipe" << endl;
    file << this->id << endl;
    file << this->name << endl;
    file << this->lenght << endl;
    file << this->diameter << endl;
    file << this->MAXperfomance << endl;
    file << this->repair << endl;
    file << this->links[0] << endl;
    file << this->links[1] << endl;
}

Pipe::Pipe(ifstream& file) {
    file >> this->id;
    file.ignore(10000, '\n');
    getline(file >> ws, this->name);
    file >> this->lenght;
    file >> this->diameter;
    file >> this->MAXperfomance;
    file >> this->repair;
    file >> this->links[0];
    file >> this->links[1];
}


istream& operator>>(istream& in, Pipe& pipe) {
    cout << "Add a Pipe:" << endl << endl;

    name_validation(pipe.name);

    pipe.lenght = input_validation<double>("Input lenght:  ", 0.000001, 2147483647);

    do {
        pipe.diameter = input_validation<int>("Input diameter (500/700/1000/1400):  ", 500, 1400);
    } while (pipe.diameter != 500 && pipe.diameter != 700 && pipe.diameter != 1000 && pipe.diameter != 1400);

    pipe.MAXperfomance = pipe.dictPerfomances.at(pipe.diameter);

    pipe.repair = input_validation<bool>("Is in repair? (1-Yes/0-No):  ", 0, 1);

    return in;
}

ostream& operator<<(ostream& out, const Pipe& pipe) {
    out << "Pipe " << pipe.id << endl <<
        "Name: " << pipe.name << endl <<
        "Diameter: " << pipe.diameter << endl <<
        "Lenght: " << pipe.lenght << endl <<
        "Perfomance: " << pipe.MAXperfomance << endl <<
        "Status of repair: " << (pipe.repair ? "Yes" : "No") << endl << endl
        
        << "Links{" << endl
        << "   " << "out: "
        << pipe.links[0] << " " << endl
        << "   " << "in: "
        << pipe.links[1] << " "
        << endl << "}" << endl;
    return out;
}


void package_edit_pipe(unordered_map<int, Pipe>& AllPipe, unordered_set<int>& FilteredPipe) {
    cout << "Editing status of repair" << endl << endl;

    bool new_status = input_validation<bool>("Enter new status of repair:  ", 0, 1);

    int counter = 0;
    for (const int& id : FilteredPipe) {
        AllPipe.find(id)->second.set_repair(new_status);
        ++counter;
    }
    cout << counter << " pipes were changed" << endl;
}