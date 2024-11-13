#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>

#include "pipe.h"
#include "cs.h"
#include "utils.h"



using namespace std;

void name_validation(string& name) {
    cout << "Enter name:  ";
    getline(cin, name);
    while (name.length() == 0) {
        cout << "Input error, enter name:  ";
        getline(cin, name);
    }

    while (name[0] == ' ') {
        name.erase(0, 1);
    }
    while (name[name.length() - 1] == ' ') {
        name.erase(name.length() - 1, 1);
    }
}


void save_objects(const unordered_map<int, Pipe>& AllPipe, const unordered_map<int, CS>& AllCS) {
    int counter = 0;

    //cout << "file name: ";
    //name_validation(path_to_file);

    ofstream file("objects/objects.txt");

    if (file.is_open()) {
        file << Pipe::get_MaxID() << endl;
        file << CS::get_MaxID() << endl;

        if (!AllPipe.empty()) {
            for (auto& [_, pipe]: AllPipe) {
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
    }
    else {
        cout << "Error opening file" << endl;
    }

}

void download_objects(unordered_map<int, Pipe>& AllPipe, unordered_map<int, CS>& AllCS, unordered_set<int>& FilteredPipe, unordered_set<int>& FilteredCS) {
    int counter = 0;

    ifstream file("objects/objects.txt");

    if (file.is_open()) {
        AllPipe.clear();
        FilteredPipe.clear();

        AllCS.clear();
        FilteredCS.clear();

        string line;

        file >> line;
        Pipe::set_MaxID(atoi(line.c_str()));
        file >> line;
        CS::set_MaxID(atoi(line.c_str()));

        while (file >> line) {
            if (line == "Pipe") {
                load(file, AllPipe);
                ++counter;
            }

            if (line == "CS") {
                load(file, AllCS);
                ++counter;
            }
        }

        file.close();

        cout << counter << " objects was added" << endl;
    }
    else {
        cout << "Error opening file" << endl;
    }

}
