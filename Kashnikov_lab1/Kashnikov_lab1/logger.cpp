#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

#include "logger.h"


using namespace std;

Logger::Logger(const string& file_name) {
    this->logfile.open("logger/" + file_name);
    if (!this->logfile.is_open()) {
        cout << "Error opening logger file!" << endl;
        return;
    }

    cerr.rdbuf(this->logfile.rdbuf());
}

Logger::~Logger() {
    if (this->logfile.is_open()) {
        this->logfile.close();
    }
}