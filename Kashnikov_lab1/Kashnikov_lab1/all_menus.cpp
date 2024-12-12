#include <iostream>

#include "all_menus.h"

using namespace std;

void menu()
{
    cout << "Menu:" << endl;
    cout << "1 - Edit list of Pipes" << endl;
    cout << "2 - Edit list of CS" << endl;
    cout << "3 - Edit GTNetwork" << endl;
    cout << "4 - Filter Pipes" << endl;
    cout << "5 - Filter CS" << endl;
    cout << "6 - View objects" << endl;
    cout << "7 - Save objects" << endl;
    cout << "8 - Download objects" << endl;
    cout << "0 - Exit" << endl << endl;
}

void pipe_menu() {
    cout << "Editing list of Pipes" << endl << endl;
    cout << "1 - Add a pipe" << endl;
    cout << "2 - Choose pipes' ids from filter" << endl;
    cout << "3 - Edit pipes by filter" << endl;
    cout << "4 - Delete pipes by filter" << endl;
    cout << "5 - Veiw pipes" << endl;
    cout << "0 - Back" << endl << endl;
}

void cs_menu() {
    cout << "Editing list of Compressor Stations" << endl << endl;
    cout << "1 - Add a CS" << endl;
    cout << "2 - Choose CS' ids from filter" << endl;
    cout << "3 - Edit package of CS by filter" << endl;
    cout << "4 - Delete CS by filter" << endl;
    cout << "5 - Veiw CS" << endl;
    cout << "0 - Back" << endl << endl;
}

void veiw_menu() {
    cout << "Veiw objects" << endl << endl;
    cout << "1 - Veiw all objects" << endl;
    cout << "2 - Veiw filtred objects" << endl;
    cout << "0 - Back" << endl << endl;
}

void filter_pipes() {
    cout << "Filter Pipes" << endl << endl;
    cout << "1 - Choose all" << endl;
    cout << "2 - By id" << endl;
    cout << "3 - By name" << endl;
    cout << "4 - By status in repair" << endl;
    cout << "0 - Back" << endl << endl;
}

void filter_cs() {
    cout << "Filter CS" << endl << endl;
    cout << "1 - Choose all" << endl;
    cout << "2 - By id" << endl;
    cout << "3 - By name" << endl;
    cout << "4 - By percentage of workspaces in work" << endl;
    cout << "5 - Clear filter" << endl << endl;
    cout << "0 - Back" << endl << endl;
}

void gtn_menu() {
    cout << "GTNetwork menu" << endl << endl;
    cout << "1 - Create graph" << endl;
    cout << "2 - Add node" << endl;
    cout << "3 - Delete pipes" << endl;
    cout << "4 - Delete CSs" << endl;
    cout << "5 - Clear graph" << endl;
    cout << "6 - Make TS" << endl;
    cout << "7 - Print graph" << endl;
    cout << "0 - Back" << endl << endl;
}