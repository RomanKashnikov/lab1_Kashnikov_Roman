#pragma once
#include <fstream>
#include <string>


using namespace std;

class Logger {
private:
    ofstream logfile;
public:
    Logger(const string& file_name);
    ~Logger();
};