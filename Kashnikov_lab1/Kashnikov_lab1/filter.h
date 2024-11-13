#pragma once
#include <unordered_map>
#include <unordered_set>

#include "pipe.h"
#include "cs.h"
#include "utils.h"

using namespace std;


bool check_percent_in_work(const CS& cs, const int percent);

void filter_by_percent_in_work(const unordered_map<int, CS>& cs, unordered_set<int>& selected_css);

bool check_status_of_repair(const Pipe& pipe, const bool is_working);

void filter_by_status_of_repair(const unordered_map<int, Pipe>& pipes, unordered_set<int>& selected_pipes);



template<typename T, typename K>
using Filter = bool(*)(const T& obj, const K param);


template<typename T, typename K>
bool check_name(const T& obj, const K name) {
    return obj.get_name().find(name) != string::npos;
}


template<typename T, typename K>
void find_by_filter(const unordered_map<int, T>& obj, unordered_set<int>& selected_obj, Filter<T, K> func, const K param) {
    for (const auto& pair : obj) {
        if (func(pair.second, param)) {
            selected_obj.emplace(pair.first);
        }
    }
}


template<typename T>
unordered_set<int> filter_by_id(const T& set) {
    unordered_set<int> subset;
    int id;
    cout << "Filter by id" << endl << endl;
    cout << "0 - Exit: " << endl << endl;

    while (true) {
        id = input_validation<int>("Enter id: ", 0, 1000);

        if (id == 0) return subset;

        if (set.contains(id)) subset.emplace(id);
    }
}


template<typename T>
void filter_by_name(const unordered_map<int, T>& obj, unordered_set<int>& selected_obj) {
    cout << "Filter by name" << endl << endl;

    string name;
    name_validation(name);

    find_by_filter(obj, selected_obj, check_name, name);
}


template<typename T>
void select_all(const unordered_map<int, T>& obj, unordered_set<int>& selected_obj) {
    for (const auto& pair : obj) {
        selected_obj.emplace(pair.first);
    }
}


template<typename T>
void delete_by_filter(unordered_map<int, T>& obj, unordered_set<int>& selected_obj) {
    int counter = 0;
    for (auto it = selected_obj.begin(); it != selected_obj.end();) {
        erase_obj(obj, *it);
        it = selected_obj.erase(it);
        ++counter;
    }
    cout << counter << " objects was deleted!" << endl;
}