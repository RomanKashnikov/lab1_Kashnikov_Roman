#include <iostream>
#include <typeinfo>


using namespace std;


void add_pipe(int& x) //1
{
    cout << "ovjnjlenrve";
}


void add_ORS(int& x) //2
{
    cout << "ovjnjlenrve";
}


void all_objects(int& x) //3
{
    cout << "ovjnjlenrve";
}


void edit_pipe(int& x) //4
{
    cout << "ovjnjlenrve";
}


void edit_ORS(int& x) //5
{
    cout << "ovjnjlenrve";
}


void save(int& x) //6
{
    cout << "ovjnjlenrve";
}


void install(int& x) //7
{
    cout << "ovjnjlenrve";
}


int main()
{
    while (1) {
        cout << "Menu:" << endl;
        cout << "1 - Add a pipe" << endl;
        cout << "2 - Add a ORS(Oil Refinery Station)" << endl;
        cout << "3 - View all objects" << endl;
        cout << "4 - Edit pipe" << endl;
        cout << "5 - Edit ORS(Oil Refinery Station)" << endl;
        cout << "6 - Save" << endl;
        cout << "7 - Install" << endl;
        cout << "0 - Exit\n" << endl;

        int x;
        cin >> x;

        switch (x) {
        case 0:
            cout << "App is closed" << endl;
            return 0;
        case 1:
            add_pipe(x);
            break;
        case 2:
            add_ORS(x);
            break;
        case 3:
            all_objects(x);
            break;
        case 4:
            edit_pipe(x);
            break;
        case 5:
            edit_ORS(x);
            break;
        case 6:
            save(x);
            break;
        case 7:
            install(x);
            break;
        default:
            cout << "There is no such value in the list, select an option from menu:\n" << endl;
            main();
            break;
        }
    }
}
    

