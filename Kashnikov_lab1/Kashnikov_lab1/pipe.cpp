﻿#include <iostream>
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
/*
double Pipe::get_lenght() const {
    return this->lenght;
}

int Pipe::get_diameter() const {
    return this->diameter;
}
*/
bool Pipe::get_repair() const {
    return this->repair;
}

void Pipe::set_repair(const bool new_repair) {
    this->repair = new_repair;
}

void Pipe::set_MaxID(const int new_MaxID){
    Pipe::MaxID = new_MaxID;
}

void Pipe::save(ofstream& file) const {
    file << "Pipe" << endl;
    file << this->id << endl;
    file << this->name << endl;
    file << this->lenght << endl;
    file << this->diameter << endl;
    file << this->repair << endl;
}

Pipe::Pipe() {
    id = ++MaxID;
    diameter = 0;
    lenght = 0;
    repair = false;
    name = "No Name";
}

Pipe::Pipe(ifstream& file) {
    file >> this->id;
    file.ignore(10000, '\n');
    getline(file >> ws, this->name);
    file >> this->lenght;
    file >> this->diameter;
    file >> this->repair;
}


istream& operator>>(istream& in, Pipe& pipe) {
    cout << "Add a Pipe:" << endl << endl;

    name_validation(pipe.name);

    pipe.lenght = input_validation<double>("Input lenght:  ", 0.000001, 2147483647);

    pipe.diameter = input_validation<int>("Input diameter:  ", 1, 2147483647);

    pipe.repair = input_validation<bool>("Is in repair? (1-Yes/0-No):  ", 0, 1);

    return in;
}

ostream& operator<<(ostream& out, const Pipe& pipe) {
    out << "Pipe " << pipe.id << endl <<
        "Name: " << pipe.name << endl <<
        "Diameter: " << pipe.diameter << endl <<
        "Lenght: " << pipe.lenght << endl <<
        "Status of repair: " << (pipe.repair ? "Yes" : "No") << endl << endl;
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