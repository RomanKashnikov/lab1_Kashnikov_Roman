#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>


using namespace std;


struct PipeCharacteristic {
    string name;
    int length;
    int diameter;
    int repair;
};

struct ORSCharacteristic {
    string name;
    int amount_of_workspaces;
    int workspaces_in_work;
    int efficiency;
};

/*
int clear_cin(int& variable) {
    while (cin.peek() != '\n') {
        cin.get();
        continue;
    }
    return variable;
}*/


string remove_spaces(string& word) {
    while (word[0] == ' ') {
        word.erase(0, 1);
    }
    while (word[word.length() - 1] == ' ') {
        word.erase(word.length() - 1, 1);
    }
    return word;
}


int input_number(string type, bool is_zero) {
    bool flag;
    int number;
    string number_str;
    cin.clear();
    getline(cin, number_str);

    if (type == "single") {
        while (1) {
            flag = false;
            if (number_str.length() != 1) {
                flag = true;
            }
            if (number_str[0] < '0' || number_str[0] > '9') {
                flag = true;
            }
            if (flag) {
                cout << "Try another value:  ";
                cin.clear();
                getline(cin, number_str);
                continue;
            }
            number = atoi(number_str.c_str());
            return number;
        }
    }

    if (type == "infinite") {
        while (1) {
            flag = false;
            for (int i = 0; i < number_str.length(); i++) {
                if (number_str[i] < '0' || number_str[i] > '9') {
                    flag = true;
                    break;
                }
            }
            
            if (is_zero) {
                if (number_str.length() == 0) {
                    flag = true;
                }
            }
            else {
                if (number_str.length() == 0 || number_str[0] == '0') {
                    flag = true;
                }
            }
            if (flag) {
                cout << "Try another value:  ";
                cin.clear();
                getline(cin, number_str);
                continue;
            }
            number = atoi(number_str.c_str());
            return number;
        }
    }
}


void add_pipe(PipeCharacteristic& pipe) //1
{
    cout << "Add a pipe:\n" << endl;

    cout << "Enter name:  ";
    getline(cin, pipe.name);
    while (pipe.name.length() == 0) {
        cout << "Input error, enter name:  ";
        getline(cin, pipe.name);
    }
    pipe.name = remove_spaces(pipe.name);

    cout << "Enter length:  ";       
    pipe.length = input_number("infinite", 0);

    cout << "Enter diameter:  ";
    pipe.diameter = input_number("infinite", 0);

    cout << "Is the pipe being repaired? (1-Yes/0-No):  ";
    pipe.repair = input_number("single", 0);
    while (pipe.repair != 0 && pipe.repair != 1) {
        cout << "Try another value:  ";
        pipe.repair = input_number("single", 0);
    }
};


void add_ORS(ORSCharacteristic& ors) //2
{
    cout << "Add a ORS:\n" << endl;

    cout << "Enter name:  ";
    getline(cin, ors.name);
    while (ors.name.length() == 0) {
        cout << "Input error, enter name:  ";
        getline(cin, ors.name);
    }
    ors.name = remove_spaces(ors.name);

    cout << "Enter amount of workspaces:  ";
    ors.amount_of_workspaces = input_number("infinite", 0);

    cout << "Workspaces in work:  ";
    ors.workspaces_in_work = input_number("infinite", 1);
    while (ors.workspaces_in_work > ors.amount_of_workspaces) {
        cout << "You have entered less workspaces.\nEnter another value:  ";
        ors.workspaces_in_work = input_number("infinite", 1);
    }

    cout << "Efficiency of ORS (0-100):  ";
    ors.efficiency = input_number("infinite", 1);
    while (ors.efficiency > 100) {
        cout << "Enter a value from 0 to 100:  ";
        ors.efficiency = input_number("infinite", 1);
    }
};


void all_objects(PipeCharacteristic& pipe, ORSCharacteristic& ors, const bool& pipe_flag, const bool& ors_flag) //3
{
    if (!(pipe_flag || pipe_flag)) {
        cout << "There is no objects." << endl;
    }
    if (pipe_flag) {
        cout << "Pipe" << endl;
        cout << "Name:  " << pipe.name << endl;
        cout << "Length:  " << pipe.length << endl;
        cout << "Diameter:  " << pipe.diameter << endl;
        if (pipe.repair == 0) { cout << "Is in repair:  No\n" << endl; }
        if (pipe.repair == 1) { cout << "Is in repair:  Yes\n" << endl; }
    }
    if (ors_flag) {
        cout << "ORS" << endl;
        cout << "Name:  " << ors.name << endl;
        cout << "Amount of workspaces:  " << ors.amount_of_workspaces << endl;
        cout << "Workspaces in work:  " << ors.workspaces_in_work << endl;
        cout << "Efficiency:  " << ors.efficiency << "%\n" << endl;
    }
    cout << "\n";
    system("pause");
}; 


void edit_pipe(PipeCharacteristic& pipe, const bool& pipe_flag) //4
{
    if (pipe_flag) {
        cout << "Changing status for Pipe:\n" << endl;
        cout << "Is the pipe being repaired? (1-Yes/0-No):  ";
        pipe.repair = input_number("single", 0);
        while (pipe.repair != 0 && pipe.repair != 1) {
            cout << "Try another value:  ";
            pipe.repair = input_number("single", 0);
        }
    }
    else {
        cout << "There is no Pipe to change.\n" << endl;
        system("pause");
    }
};


void edit_ORS(ORSCharacteristic& ors, const bool& ors_flag) //5
{
    if (ors_flag) {
        cout << "Changing workspaces in work for ORS:\n" << endl;
        cout << "Enter a value less than or equal to " << ors.amount_of_workspaces << " :  ";
        ors.workspaces_in_work = input_number("infinite", 1);
        while (ors.workspaces_in_work > ors.amount_of_workspaces) {
            cout << "You entered a value greater than the number of workspaces.\nEnter a value less than or equal to " << ors.amount_of_workspaces << " :  ";
            ors.workspaces_in_work = input_number("infinite", 1);
        }
    }
    else {
        cout << "There is no ORS to change.\n" << endl;
        system("pause");
    }
    
};


void save(string& fname, PipeCharacteristic& pipe, ORSCharacteristic& ors, const bool& pipe_flag, const bool& ors_flag) //6
{
    ofstream fout;
    fout.open(fname);

    if (!fout.is_open()) {
        cout << "Open file error." << endl;
    }
    else {
        if (pipe_flag && ors_flag) {
            fout << "Pipe:" << endl;
            fout << pipe.name << endl;
            fout << pipe.length << endl;
            fout << pipe.diameter << endl;
            fout << pipe.repair << endl;

            fout << "\n";

            fout << "ORS:" << endl;
            fout << ors.name << endl;
            fout << ors.amount_of_workspaces << endl;
            fout << ors.workspaces_in_work << endl;
            fout << ors.efficiency << endl;

            fout.close();
            cout << "Objects saved.\n" << endl;
            system("pause");
        }
        else if (pipe_flag) {
            fout << "Pipe:" << endl;
            fout << pipe.name << endl;
            fout << pipe.length << endl;
            fout << pipe.diameter << endl;
            fout << pipe.repair << endl;

            fout << "\n";

            fout.close();
            cout << "Objects saved.\n" << endl;
            system("pause");
        }
        else if (ors_flag) {
            fout << "ORS:" << endl;
            fout << ors.name << endl;
            fout << ors.amount_of_workspaces << endl;
            fout << ors.workspaces_in_work << endl;
            fout << ors.efficiency << endl;

            fout.close();
            cout << "Objects saved.\n" << endl;
            system("pause");
        }
        else {
            fout.close();
            cout << "There is no objects to save.\n" << endl;
            system("pause");
        }
    }
};


void install(string& fname, PipeCharacteristic& pipe, ORSCharacteristic& ors, bool& pipe_flag, bool& ors_flag) //7
{
    ifstream fin;
    fin.open(fname, ofstream::app);
    string line;
    bool flag = true;

    if (!fin.is_open()) {
        cout << "Open file error." << endl;
    }
    else {
        cout << "Installed objects:\n" << endl;
        while (getline(fin, line)) {
            flag = false;
            if (line == "Pipe:") {
                pipe_flag = true;
                cout << "Pipe" << endl;
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
                cout << pipe.repair << endl;
                cout << "\n";
            }
            if (line == "ORS:") {
                ors_flag = true;
                cout << "ORS" << endl;
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
                cout << ors.efficiency << endl;
                cout << "\n";
            }
        }
        if (flag) {
            cout << "There is no objects.\n" << endl;
        }
    }
    cout << "\n";
    system("pause");
};


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
    cout << "0 - Exit\n" << endl;
}


int main() {
    int option;
    bool pipe_flag = false;
    bool ors_flag = false;

    string fname = "objects.txt";

    PipeCharacteristic pipe = { "", 0, 0, 0 };
    ORSCharacteristic ors = { "", 0, 0, 0 };

    menu();
    while (1) {
        cout << "Choose the option:  ";
        option = input_number("single", 0);
        while (option > 7) {
            cout << "Try another value:  ";
            option = input_number("single", 0);
        }


        system("cls");
        switch (option) {
        case 0:
            system("cls");
            cout << "App is closed" << endl;
            return 0;
        case 1:
            add_pipe(pipe);
            pipe_flag = true;
            system("cls");
            menu();
            break;
        case 2:
            add_ORS(ors);
            ors_flag = true;
            system("cls");
            menu();
            break;
        case 3:
            all_objects(pipe, ors, pipe_flag, ors_flag);
            system("cls");
            menu();
            break;
        case 4:
            edit_pipe(pipe, pipe_flag);
            system("cls");
            menu();
            break;
        case 5:
            edit_ORS(ors, ors_flag);
            system("cls");
            menu();
            break;
        case 6:
            save(fname, pipe, ors, pipe_flag, ors_flag);
            system("cls");
            menu();
            break;
        case 7:
            install(fname, pipe, ors, pipe_flag, ors_flag);
            system("cls");
            menu();
            break;
        default:
            cout << "There is no such value in the list, select an option from menu.\n" << endl;
        }
    }
}
    

