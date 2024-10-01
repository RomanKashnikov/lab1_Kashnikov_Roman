#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>


using namespace std;


struct PipeCharacteristic {
    string name;
    int length;
    int diameter;
    bool repair;
};

struct ORSCharacteristic {
    string name;
    int amount_of_workspaces;
    int workspaces_in_work;
    int efficiency;
};


void remove_spaces(string& word) {
    while (word[0] == ' ') {
        word.erase(0, 1);
    }
    while (word[word.length() - 1] == ' ') {
        word.erase(word.length() - 1, 1);
    }
}


int input_validation(int min, int max) {
    bool flag;
    string number_str;
    cin.clear();
    getline(cin, number_str);

    while (1) {
        flag = false;

        if (number_str.length() == 0) {
            flag = true;
        }
        if (1) {
            for (int i = 0; i < number_str.length(); i++) {
                if (number_str[i] < '0' || number_str[i] > '9') {
                    flag = true;
                    break;
                }
            }
        }
        if (((min != 0 || number_str.length() != 1) && number_str[0] == '0') || (atoi(number_str.c_str()) < min || atoi(number_str.c_str()) > max)) {
            flag = true;
        }
        
        if (flag) {
            cout << "Try another value:  ";
            cin.clear();
            getline(cin, number_str);
            continue;
        }

        return atoi(number_str.c_str());
    }
}


void name_validation(string& name) {
    cout << "Enter name:  ";
    getline(cin, name);
    while (name.length() == 0) {
        cout << "Input error, enter name:  ";
        getline(cin, name);
    }
    remove_spaces(name);
}


void add_pipe(PipeCharacteristic& pipe) //1
{
    cout << "Add a pipe:" << endl << endl;

    name_validation(pipe.name);

    cout << "Enter length:  ";       
    pipe.length = input_validation(1, 2147483647);

    cout << "Enter diameter:  ";
    pipe.diameter = input_validation(1, 2147483647);

    cout << "Is the pipe being repaired? (1-Yes/0-No):  ";
    pipe.repair = input_validation(0, 1);
}


void add_ORS(ORSCharacteristic& ors) //2
{
    cout << "Add a ORS:" << endl << endl;

    name_validation(ors.name);

    cout << "Enter amount of workspaces:  ";
    ors.amount_of_workspaces = input_validation(1, 2147483647);

    cout << "Workspaces in work:  ";
    ors.workspaces_in_work = input_validation(0, ors.amount_of_workspaces);

    cout << "Efficiency of ORS (0-100):  ";
    ors.efficiency = input_validation(0, 100);
}


void veiw_pipe(const PipeCharacteristic& pipe) {
    cout << "Pipe" << endl;
    cout << "Name:  " << pipe.name << endl;
    cout << "Length:  " << pipe.length << endl;
    cout << "Diameter:  " << pipe.diameter << endl;
    cout << "Is in repair:  " << ((pipe.repair) ? "Yes" : "No") << endl << endl;
}

void veiw_ors(const ORSCharacteristic& ors) {
    cout << "ORS" << endl;
    cout << "Name:  " << ors.name << endl;
    cout << "Amount of workspaces:  " << ors.amount_of_workspaces << endl;
    cout << "Workspaces in work:  " << ors.workspaces_in_work << endl;
    cout << "Efficiency:  " << ors.efficiency << "%" << endl << endl;
}

void veiw_objects(const PipeCharacteristic& pipe, const ORSCharacteristic& ors, bool pipe_flag, bool ors_flag) //3
{
    if (!(pipe_flag || pipe_flag)) {
        cout << "There is no objects." << endl;
    }
    else {
        if (pipe_flag) {
            veiw_pipe(pipe);
        }
        if (ors_flag) {
            veiw_ors(ors);
        }
    }
}


void edit_pipe(PipeCharacteristic& pipe, bool pipe_flag) //4
{
    if (pipe_flag) {
        cout << "Changing status for Pipe:" << endl << endl;
        cout << "Is the pipe being repaired? (1-Yes/0-No):  ";

        pipe.repair = input_validation(0, 1);
    }
    else {
        cout << "There is no Pipe to change." << endl;
    }
}


void edit_ORS(ORSCharacteristic& ors, bool ors_flag) //5
{
    if (ors_flag) {
        cout << "Changing workspaces in work for ORS:" << endl << endl;
        cout << "Enter a value less than or equal to " << ors.amount_of_workspaces << " :  ";

        ors.workspaces_in_work = input_validation(0, ors.amount_of_workspaces);
    }
    else {
        cout << "There is no ORS to change." << endl;
    }   
}


void save_pipe(const string& fname, const PipeCharacteristic& pipe) {
    ofstream fout;
    fout.open(fname);

    if (!fout.is_open()) {
        cout << "Open file error." << endl;
    }
    else {
        fout << "Pipe:" << endl;
        fout << pipe.name << endl;
        fout << pipe.length << endl;
        fout << pipe.diameter << endl;
        fout << pipe.repair << endl << endl;
    }
    fout.close();
}

void save_ors(const string& fname, const ORSCharacteristic& ors) {
    ofstream fout;
    fout.open(fname);

    if (!fout.is_open()) {
        cout << "Open file error." << endl;
    }
    else {
        fout << "ORS:" << endl;
        fout << ors.name << endl;
        fout << ors.amount_of_workspaces << endl;
        fout << ors.workspaces_in_work << endl;
        fout << ors.efficiency << endl << endl;
    }
    fout.close();
}

void save_all(const string& fname, const PipeCharacteristic& pipe, const ORSCharacteristic& ors) {
    ofstream fout;
    fout.open(fname);

    if (!fout.is_open()) {
        cout << "Open file error." << endl;
    }
    else {
        fout << "Pipe:" << endl;
        fout << pipe.name << endl;
        fout << pipe.length << endl;
        fout << pipe.diameter << endl;
        fout << pipe.repair << endl << endl;

        fout << "ORS:" << endl;
        fout << ors.name << endl;
        fout << ors.amount_of_workspaces << endl;
        fout << ors.workspaces_in_work << endl;
        fout << ors.efficiency << endl << endl;
    }
    fout.close();
}

void save(const string& fname, const PipeCharacteristic& pipe, const ORSCharacteristic& ors, bool pipe_flag, bool ors_flag) //6
{
    if (pipe_flag && ors_flag) {
        save_all(fname, pipe, ors);
    }
    else if (pipe_flag) {
        save_pipe(fname, pipe);
    }
    else if (ors_flag) {
        save_ors(fname, ors);
    }
    
    (ors_flag || pipe_flag) ? cout << "Objects saved." << endl << endl: cout << "There is no objects to save." << endl << endl;
}


void download(const string& fname, PipeCharacteristic& pipe, ORSCharacteristic& ors, bool& pipe_flag, bool& ors_flag) //7
{
    ifstream fin;
    fin.open(fname);
    string line;

    if (!fin.is_open()) {
        cout << "Open file error." << endl;
    }
    else {
        pipe_flag = ors_flag = false;
        cout << "Installed objects:" << endl << endl;
        while (getline(fin, line)) {
            if (line == "Pipe:") {
                pipe_flag = true;
                cout << "Pipe:" << endl;
                getline(fin, line);
                pipe.name = line;
                cout << pipe.name << endl;
                getline(fin, line);
                pipe.length = atoi(line.c_str());
                cout << pipe.length << endl;
                getline(fin, line);
                pipe.diameter = atoi(line.c_str());
                cout << pipe.diameter << endl;
                getline(fin, line);
                pipe.repair = atoi(line.c_str());
                cout << pipe.repair << endl << endl;
            }
            if (line == "ORS:") {
                ors_flag = true;
                cout << "ORS:" << endl;
                getline(fin, line);
                ors.name = line;
                cout << ors.name << endl;
                getline(fin, line);
                ors.amount_of_workspaces = atoi(line.c_str());
                cout << ors.amount_of_workspaces << endl;
                getline(fin, line);
                ors.workspaces_in_work = atoi(line.c_str());
                cout << ors.workspaces_in_work << endl;
                getline(fin, line);
                ors.efficiency = atoi(line.c_str());
                cout << ors.efficiency << endl << endl;
            }
        }
        if (!pipe_flag && !ors_flag) {
            cout << "There is no objects." << endl << endl;
        }
    }
}


void menu()
{
    cout << "Menu:" << endl;
    cout << "1 - Add a pipe" << endl;
    cout << "2 - Add a ORS(Oil Refinery Station)" << endl;
    cout << "3 - View all objects" << endl;
    cout << "4 - Edit pipe" << endl;
    cout << "5 - Edit ORS(Oil Refinery Station)" << endl;
    cout << "6 - Save" << endl;
    cout << "7 - Install" << endl;
    cout << "0 - Exit" << endl << endl;
}


int main() {
    int option;
    bool pipe_flag = false;
    bool ors_flag = false;

    string fname = "objects.txt";

    PipeCharacteristic pipe = { "", 0, 0, 0 };
    ORSCharacteristic ors = { "", 0, 0, 0 };

    while (1) {
        menu();
        cout << "Choose the option:  ";

        option = input_validation(0, 7);
        system("cls");

        switch (option) {
        case 0:
            cout << "App is closed" << endl;
            return 0;
        case 1:
            add_pipe(pipe);
            pipe_flag = true;
            break;
        case 2:
            add_ORS(ors);
            ors_flag = true;
            break;
        case 3:
            veiw_objects(pipe, ors, pipe_flag, ors_flag);
            break;
        case 4:
            edit_pipe(pipe, pipe_flag);
            break;
        case 5:
            edit_ORS(ors, ors_flag);
            break;
        case 6:
            save(fname, pipe, ors, pipe_flag, ors_flag);
            break;
        case 7:
            download(fname, pipe, ors, pipe_flag, ors_flag);
            break;
        }
        cout << endl;
        system("pause");
        system("cls");
    }
}
    

