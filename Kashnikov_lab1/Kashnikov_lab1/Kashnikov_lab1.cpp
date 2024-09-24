#include <iostream>
#include <string>
#include <stdlib.h>

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


int clear_cin(int& variable) {
    while (cin.peek() != '\n') {
        cin.get();
        continue;
    }
    return variable;
}


string remove_spaces(string& word) {
    while (word[0] == ' ') {
        word.erase(0, 1);
    }
    while (word[word.length() - 1] == ' ') {
        word.erase(word.length() - 1, 1);
    }
    return word;
}


int input_number(string type) {
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
            if (number_str.length() == 0 || number_str[0] == '0') {
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
    pipe.length = input_number("infinite");

    cout << "Enter diameter:  ";
    pipe.diameter = input_number("infinite");

    cout << "Is the pipe being repaired? (1-Yes/0-No):  ";
    pipe.repair = input_number("single");
    while (pipe.repair != 0 && pipe.repair != 1) {
        cout << "Try another value:  ";
        pipe.repair = input_number("single");
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
    ors.amount_of_workspaces = input_number("infinite");

    cout << "Workspaces in work:  ";
    ors.workspaces_in_work = input_number("infinite");
    if (ors.workspaces_in_work > ors.amount_of_workspaces) {
        cout << "You have entered less workspaces.\nEnter another value:  ";
        ors.workspaces_in_work = input_number("infinite");
    }

    cout << "Efficiency of ORS (1-100):  ";
    ors.efficiency = input_number("infinite");
    if (ors.efficiency > 100) {
        cout << "Enter a value from 1 to 100:  ";
        ors.efficiency = input_number("infinite");
    }
};


void all_objects() //3
{
    cout << "3" << endl;
};


void edit_pipe() //4
{
    cout << "4" << endl;
};


void edit_ORS() //5
{
    cout << "5" << endl;
};


void save() //6
{
    cout << "6" << endl;
};


void install() //7
{
    cout << "7" << endl;
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


    menu();
    int option;
    while (1) {
        cout << "Choose the option:  ";
        option = input_number("single");
        while (option > 7) {
            cout << "Try another value:  ";
            option = input_number("single");
        }

        PipeCharacteristic pipe = { "", 0, 0, 0 };
        ORSCharacteristic ors = { "", 0, 0, 0 };

        system("cls");
        switch (option) {
        case 0:
            system("cls");
            cout << "App is closed" << endl;
            return 0;
        case 1:
            add_pipe(pipe);
            system("cls");
            menu();
            break;
        case 2:
            add_ORS(ors);
            system("cls");
            menu();
            break;
        case 3:
            all_objects();
            system("cls");
            menu();
            break;
        case 4:
            edit_pipe();
            system("cls");
            menu();
            break;
        case 5:
            edit_ORS();
            system("cls");
            menu();
            break;
        case 6:
            save();
            system("cls");
            menu();
            break;
        case 7:
            install();
            system("cls");
            menu();
            break;
        default:
            cout << "There is no such value in the list, select an option from menu.\n" << endl;
        }
    }
}
    

