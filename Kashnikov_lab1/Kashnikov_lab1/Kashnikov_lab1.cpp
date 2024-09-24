#include <iostream>
#include <string>

using namespace std;


struct PipeCharacteristic {
    string name;
    int lenght;
    int diameter;
    bool repair;
};

struct ORSCharacteristic {
    string name;
    int amount_of_workspaces;
    int workspaces_in_work;
    int efficiency;
};


void add_pipe(PipeCharacteristic& pipe) //1
{
    cout << "1" << endl;
};


void add_ORS() //2
{
    cout << "2" << endl;
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


int proverka(int& option) {
    while (cin.fail() || cin.peek() != '\n') {
        cout << "There is no such value in the list, select an option from menu.\n" << endl;
        cin.clear();
        while (cin.peek() != '\n') {
            cin.get();
            continue;
        }
        cin >> option;
    }
    return option;
}


int main(int option)
{
    menu();
    while (1) {
        cin >> option;
        proverka(option);
        //cout << option;
        PipeCharacteristic pipe = { "", 0, 0, 0 };

        switch (option) {
        case 0:
            //system("cls");
            cout << "App is closed" << endl;
            return 0;
        case 1:
            add_pipe(pipe);
            //system("cls");
            menu();
            break;
        case 2:
            add_ORS();
            //system("cls");
            menu();
            break;
        case 3:
            all_objects();
            //system("cls");
            menu();
            break;
        case 4:
            edit_pipe();
            system("cls");
            menu();
            break;
        case 5:
            edit_ORS();
            //system("cls");
            menu();
            break;
        case 6:
            save();
            //system("cls");
            menu();
            break;
        case 7:
            install();
            //system("cls");
            menu();
            break;
        default:
            cout << "There is no such value in the list, select an option from menu.\n" << endl;
        }
    }
}
    

