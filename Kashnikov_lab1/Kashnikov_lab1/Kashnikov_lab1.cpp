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

struct CSCharacteristic {
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


void add_CS(CSCharacteristic& cs) //2
{
    cout << "Add a CS:" << endl << endl;

    name_validation(cs.name);

    cout << "Enter amount of workspaces:  ";
    cs.amount_of_workspaces = input_validation(1, 2147483647);

    cout << "Workspaces in work:  ";
    cs.workspaces_in_work = input_validation(0, cs.amount_of_workspaces);

    cout << "Efficiency of CS (0-100):  ";
    cs.efficiency = input_validation(0, 100);
}


void veiw_pipe(const PipeCharacteristic& pipe) {
    cout << "Pipe" << endl;
    cout << "Name:  " << pipe.name << endl;
    cout << "Length:  " << pipe.length << endl;
    cout << "Diameter:  " << pipe.diameter << endl;
    cout << "Is in repair:  " << ((pipe.repair) ? "Yes" : "No") << endl << endl;
}

void veiw_cs(const CSCharacteristic& cs) {
    cout << "CS" << endl;
    cout << "Name:  " << cs.name << endl;
    cout << "Amount of workspaces:  " << cs.amount_of_workspaces << endl;
    cout << "Workspaces in work:  " << cs.workspaces_in_work << endl;
    cout << "Efficiency:  " << cs.efficiency << "%" << endl << endl;
}

void veiw_objects(const PipeCharacteristic& pipe, const CSCharacteristic& cs, bool pipe_flag, bool cs_flag) //3
{
    if (!(pipe_flag || pipe_flag)) {
        cout << "There is no objects." << endl;
    }
    else {
        if (pipe_flag) {
            veiw_pipe(pipe);
        }
        if (cs_flag) {
            veiw_cs(cs);
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


void edit_CS(CSCharacteristic& cs, bool cs_flag) //5
{
    if (cs_flag) {
        cout << "Changing workspaces in work for CS:" << endl << endl;
        cout << "Enter a value less than or equal to " << cs.amount_of_workspaces << " :  ";

        cs.workspaces_in_work = input_validation(0, cs.amount_of_workspaces);
    }
    else {
        cout << "There is no CS to change." << endl;
    }   
}


void save_pipe(ofstream& fout, const PipeCharacteristic& pipe) {
    fout << "Pipe:" << endl;
    fout << pipe.name << endl;
    fout << pipe.length << endl;
    fout << pipe.diameter << endl;
    fout << pipe.repair << endl << endl;
}

void save_cs(ofstream& fout, const CSCharacteristic& cs) {
    fout << "CS:" << endl;
    fout << cs.name << endl;
    fout << cs.amount_of_workspaces << endl;
    fout << cs.workspaces_in_work << endl;
    fout << cs.efficiency << endl << endl;
}


void save(const string& fname, const PipeCharacteristic& pipe, const CSCharacteristic& cs, bool pipe_flag, bool cs_flag) //6
{
    ofstream fout;
    fout.open(fname);

    if (!fout.is_open()) {
        cout << "Open file error." << endl;
    }
    else {
        if (pipe_flag) {
            save_pipe(fout, pipe);
        }
        if (cs_flag) {
            save_cs(fout, cs);
        }
    }
    fout.close();
    
    (cs_flag || pipe_flag) ? cout << "Objects saved." << endl << endl: cout << "There is no objects to save." << endl << endl;
}


bool download_pipe(ifstream& fin, string& line, PipeCharacteristic& pipe) {
    getline(fin, line);
    pipe.name = line;
    fin >> pipe.length;
    fin >> pipe.diameter;
    fin >> pipe.repair;

    return fin.good();
}

bool download_cs(ifstream& fin, string& line, CSCharacteristic& cs) {
    getline(fin, line);
    cs.name = line;
    fin >> cs.amount_of_workspaces;
    fin >> cs.workspaces_in_work;
    fin >> cs.efficiency;

    return fin.good();
}

void download(const string& fname, PipeCharacteristic& pipe, CSCharacteristic& cs, bool& pipe_flag, bool& cs_flag) //7
{
    ifstream fin;
    fin.open(fname);
    string line;

    if (!fin.is_open()) {
        cout << "Open file error." << endl;
    }
    else {
        pipe_flag = cs_flag = false;
        //cout << "Installed objects:" << endl << endl;
        while (getline(fin, line)) {
            if (line == "Pipe:") {
                pipe_flag = true;
                download_pipe(fin, line,  pipe);

            }
            if (line == "cs:") {
                cs_flag = true;
                download_cs(fin, line, cs);
            }
        }
        if (!pipe_flag && !cs_flag) {
            cout << "There is no objects." << endl << endl;
        }
    }
}


void menu()
{
    cout << "Menu:" << endl;
    cout << "1 - Add a pipe" << endl;
    cout << "2 - Add a CS" << endl;
    cout << "3 - View all objects" << endl;
    cout << "4 - Edit pipe" << endl;
    cout << "5 - Edit CS" << endl;
    cout << "6 - Save" << endl;
    cout << "7 - Install" << endl;
    cout << "0 - Exit" << endl << endl;
}


int main() {
    int option;
    bool pipe_flag = false;
    bool cs_flag = false;

    string fname = "objects.txt";

    PipeCharacteristic pipe = { "", 0, 0, 0 };
    CSCharacteristic cs = { "", 0, 0, 0 };

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
            add_CS(cs);
            cs_flag = true;
            break;
        case 3:
            veiw_objects(pipe, cs, pipe_flag, cs_flag);
            break;
        case 4:
            edit_pipe(pipe, pipe_flag);
            break;
        case 5:
            edit_CS(cs, cs_flag);
            break;
        case 6:
            save(fname, pipe, cs, pipe_flag, cs_flag);
            break;
        case 7:
            download(fname, pipe, cs, pipe_flag, cs_flag);
            break;
        }
        cout << endl;
        system("pause");
        system("cls");
    }
}
    

