#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "pipe.h"
#include "cs.h"

using namespace std;


void name_validation(string& name);

void save_objects(const unordered_map<int, Pipe>& AllPipe, const unordered_map<int, CS>& AllCS);

void download_objects(unordered_map<int, Pipe>& AllPipe, unordered_map<int, CS>& AllCS, unordered_set<int>& FilteredPipe, unordered_set<int>& FilteredCS);

#define DELETE_OBJECTS(objects) objects.clear(); \
                                cout << "Filter cleared!" << endl;


template <typename T>
T input_validation(const string message, const int min, const int max) {
    T value;

    cout << message;
    while ((cin >> value).fail()
        || cin.peek() != '\n'
        || value < min || value > max)
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Try another value:  ";
    }
    cin.clear();
    cin.ignore(10000, '\n');
    cerr << value << endl;
    return value;
}


template<typename T>
void veiw_all(const string message, const unordered_map<int, T>& objects) {
    cout << message << endl << endl;
    if (objects.size() == 0) cout << "No objects" << endl;

    for (auto& [id, item] : objects)
    {
        cout << item << endl;
    }
    cout << endl << endl;
}

template<typename T>
void veiw_filtered(const string message, const unordered_map<int, T>& obj, const unordered_set<int>& filtered_obj) {
    cout << message << endl << endl;
    if (filtered_obj.size() == 0) cout << "No objects" << endl;

    for (const int& id : filtered_obj) {
        cout << obj.find(id)->second << endl;
    }
    cout << endl << endl;
}


template<typename T>
void add_object(unordered_map<int, T>& AllObjects) {
    T object;
    cin >> object;
    AllObjects.emplace(object.get_id(), object);
}

template<typename T>
void load(ifstream& file, unordered_map<int, T>& AllObjects) {
    T object(file);
    AllObjects.emplace(object.get_id(), object);
}

template<typename T>
void erase_obj(unordered_map<int, T>& objs, const int id) {
    if (objs.count(id)) {
        objs.erase(id);
    }
    else {
        cout << "There is not object with id " << id << endl;
    }
}

