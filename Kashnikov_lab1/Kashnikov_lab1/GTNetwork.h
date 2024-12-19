#pragma once
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>

#include "pipe.h"
#include "cs.h"
#include "utils.h"


using namespace std;

class GTNetwork {
private:
    template<typename T, typename K>
    using Filter = bool(GTNetwork::*)(const T& obj, const K& param);

    const int INF = std::numeric_limits<int>::max();

    unordered_map<int, Pipe> AllPipe;
    unordered_map<int, CS> AllCS;

    unordered_set<int> FilteredPipe;
    unordered_set<int> FilteredCS;

    unordered_map<int, unordered_set<int>> graph;
    vector<int> order;
    vector<int> min_path;
    vector<int> maxFlow_path;
    int maxFlow;

    bool eraseObjFromGraph(Pipe& pipe);
    bool eraseObjFromGraph(CS& cs);

    template<typename T>
    void erase_obj(T& objs, const int id);

    template<typename T>
    bool load_obj(ifstream& file, unordered_map<int, T>& objs);

    template<typename T, typename K>
    bool check_name(const T& obj, const K& name);
    bool check_status_of_repair(const Pipe& pipe, const bool& in_repair);
    bool check_percent_in_work(const CS& cs, const int& efficiency);
    bool check_by_diameter(const Pipe& pipe, const int& diameter);
    bool check_by_lenght(const Pipe& pipe, const int& length);

    template<typename T, typename K>
    bool find_by_filter(const unordered_map<int, T>& obj, unordered_set<int>& selected_obj, Filter<T, K> func, const K& param);
    int find_by_diameter(const int& diameter, const int& length);

    template<typename T>
    vector<T> metodDeikstra(T StartNode, T EndNode);

    template<typename T>
    bool bfs(T s, T t, unordered_map<T, T>& parent, unordered_map<T, unordered_map<T, int>>& capacity);

    template<typename T>
    int edmondsKarp(const T& source, const T& sink);

    template<typename T>
    vector<T> getMAXFlowPath(const T& source, const T& sink, const unordered_map<T, T>& parent);

    bool show_MinPath();
    bool show_maxFlow();

public:
    void print_graph() const;
    bool clear_graph();

    bool create_graph();
    bool add_node();

    bool delPipeFromGraph();
    bool delCSFromGraph();

    bool make_TS();
    int getDistance(const int& id_1, const int& id_2);
    int getAbsoluteDistance(const int& id_1, const int& id_2);
    bool find_min_dist();
    int getCapacity(const int& id_1, const int& id_2);
    bool count_maxFlow();

    template<typename T>
    unordered_set<int> filter_by_id(const T& set);
    bool clear_selected(const bool& choice);

    bool find_by_status_in_repair();
    bool find_by_percent_in_work();

    int add_Pipe();
    void print_filtered_pipes() const;
    bool set_pipes_by_id(const bool& choice);
    bool change_status_of_repair();
    bool find_pipes_by_name();
    bool select_all_pipes();
    bool delete_selected_pipes();

    int add_CS();
    void print_filtered_CS() const;
    bool set_cs_by_id(const bool& choice);
    bool change_workload();
    bool find_cs_by_name();
    bool select_all_cs();
    bool delete_selected_cs();
    unordered_set<int> get_IncidentPipes(const int& id_1, const int& id_2);

    bool save_objects() const;
    bool download_objects();

    friend ostream& operator << (ostream& os, const GTNetwork& gtn);
};

template<typename T>
bool GTNetwork::load_obj(ifstream& file, unordered_map<int, T>& objs) {
    T obj(file);
    objs.emplace(obj.get_id(), obj);
    return file.good();
}

template<typename T>
void GTNetwork::erase_obj(T& objs, const int id) {
    if (objs.contains(id)) {
        objs.erase(id);
    }
    else {
        cout << "There is not object with id " << id << endl;
    }
}