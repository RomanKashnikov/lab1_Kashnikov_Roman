#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "cs.h"
#include "utils.h"

using namespace std;


int CS::MaxID = 0;


int CS::get_MaxID() {
    return CS::MaxID;
}

int CS::get_id() const {
    return this->id;
}

string CS::get_name() const {
    return this->name;
}
/*
int CS::get_amount_of_workspaces() const {
    return this->amount_of_workspaces;
}

int CS::get_workspaces_in_work() const {
    return this->workspaces_in_work;
}

int CS::get_efficiency() const {
    return this->efficiency;
}
*/
int CS::get_workload() const {
    return (100 * workspaces_in_work / amount_of_workspaces);
}
/*
void CS::set_workspaces_in_work(int new_workspaces_in_work) {
    this->workspaces_in_work = new_workspaces_in_work;
}*/

void CS::start_workspace() {
    if (workspaces_in_work != amount_of_workspaces) {
        ++workspaces_in_work;
    }
}

void CS::stop_workspace() {
    if (workspaces_in_work != 0) {
        --workspaces_in_work;
    }
}

void CS::set_MaxID(const int new_MaxID) {
    CS::MaxID = new_MaxID;
}


void CS::save(ofstream& file) const {
    file << "CS" << endl;
    file << this->id << endl;
    file << this->name << endl;
    file << this->amount_of_workspaces << endl;
    file << this->workspaces_in_work << endl;
    file << this->efficiency << endl;
}


CS::CS() {
    id = ++MaxID;
    name = "No Name";
    amount_of_workspaces = 0;
    workspaces_in_work = 0;
    efficiency = 0;
}

CS::CS(ifstream& file) {
    file >> this->id;
    file.ignore(10000, '\n');
    getline(file >> ws, this->name);
    file >> this->amount_of_workspaces;
    file >> this->workspaces_in_work;
    file >> this->efficiency;
}


istream& operator>>(istream& in, CS& cs) {
    cout << "Add a CS:" << endl << endl;

    name_validation(cs.name);

    cs.amount_of_workspaces = input_validation<int>("Input amount of workspaces:  ", 1, 2147483647);

    cs.workspaces_in_work = input_validation<int>("Input workspaces in work:  ", 0, cs.amount_of_workspaces);

    cs.efficiency = input_validation<int>("Efficiency (0-100):  ", 0, 100);

    return in;
}

ostream& operator<<(ostream& out, const CS& cs) {
    out << "CS " << cs.id << endl <<
           "Name: " << cs.name << endl <<
           "Amount of workspaces: " << cs.amount_of_workspaces << endl <<
           "Workspaces in work: " << cs.workspaces_in_work << endl <<
           "Efficiency: " << cs.efficiency << "%" << endl << endl;
    return out;
}


void package_edit_cs(unordered_map<int, CS>& AllCS, unordered_set<int>& FilteredCS) {
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
}