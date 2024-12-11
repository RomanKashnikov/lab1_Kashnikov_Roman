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


template<typename T, typename K>
using Func = bool(*)(const T& value, const K& range);

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

