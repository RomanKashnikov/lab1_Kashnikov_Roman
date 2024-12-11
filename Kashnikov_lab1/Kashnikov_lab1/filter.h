#pragma once
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <string>

#include "GTNetwork.h"


using namespace std;


template<typename T, typename K>
bool GTNetwork::check_name(const T& obj, const K& name) {
    return obj.get_name().find(name) != string::npos;
}

template<typename T, typename K>
bool GTNetwork::find_by_filter(const std::unordered_map<int, T>& obj, std::unordered_set<int>& selected_obj, Filter<T, K> func, const K& param) {
    for (const auto& pair : obj) {
        if ((this->*func)(pair.second, param)) {
            selected_obj.emplace(pair.first);
        }
    }
    return 1;
}

template<typename T>
unordered_set<int> GTNetwork::filter_by_id(const T& set) {
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