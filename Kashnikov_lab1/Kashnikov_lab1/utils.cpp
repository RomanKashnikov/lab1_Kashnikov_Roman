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