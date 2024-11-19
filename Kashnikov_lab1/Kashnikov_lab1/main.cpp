#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <chrono>
#include <format>

#include "pipe.h"
#include "cs.h"
#include "utils.h"
#include "filter.h"
#include "all_menus.h"
#include "logger.h"


using namespace std;
using namespace chrono;



void pause() {
    cout << endl;
    system("pause");
    system("cls");
}

int main() {
    int option;

    string fname = "objects.txt";

    unordered_map<int, Pipe> AllPipe;
    unordered_map<int, CS> AllCS;

    unordered_set<int> FilteredPipe;
    unordered_set<int> FilteredCS;

    redirect_output_wrapper cerr_out(cerr);
    string time = format("{:%d_%m_%Y %H_%M_%OS}", system_clock::now());
    ofstream logfile("logger/log_" + time);
    if (logfile)
        cerr_out.redirect(logfile);
    //Logger logger("story.txt");

    while (1) {
        menu();

        option = input_validation<int>("Choose the option:  ", 0, 7);
        system("cls");

        switch (option) {
        case 0:
            cout << "App is closed" << endl;
            return 0;
        case 1:            
            do {
                pipe_menu();

                option = input_validation<int>("Choose the option:  ", 0, 5);
                system("cls");

                switch (option) {
                case 1:
                    add_object(AllPipe);
                    break;
                case 2:
                    if (!FilteredPipe.empty()) {
                        FilteredPipe = filter_by_id(FilteredPipe);
                    }
                    else {
                        cout << "No filtered pipes" << endl << endl;
                    }
                    break;
                case 3:
                    package_edit_pipe(AllPipe, FilteredPipe);
                    break;
                case 4:
                    delete_by_filter(AllPipe, FilteredPipe);
                    break;
                case 5:
                    veiw_all("------------------------------\n          All Pipes\n------------------------------", AllPipe);
                    veiw_filtered("------------------------------\n        Filtered Pipes\n------------------------------", AllPipe, FilteredPipe);
                    break;
                }
                if (option) {
                    pause();
                }
            } while (option);
            break;
        case 2:
            do {
                cs_menu();

                option = input_validation<int>("Choose the option:  ", 0, 5);
                system("cls");

                switch (option) {
                case 1:
                    add_object(AllCS);
                    break;
                case 2:
                    if (!FilteredCS.empty()) {
                        FilteredCS = filter_by_id(FilteredCS);
                    }
                    else {
                        cout << "No filtered CS" << endl << endl;
                    }
                    break;
                case 3:
                    package_edit_cs(AllCS, FilteredCS);
                    break;
                case 4:
                    delete_by_filter(AllCS, FilteredCS);
                    break;
                case 5:
                    veiw_all("------------------------------\n   All Compressor Stations\n------------------------------", AllCS);
                    veiw_filtered("------------------------------\n Filtered Compressor Stations\n------------------------------", AllCS, FilteredCS);
                    break;
                }
                if (option) {
                    pause();
                }
            } while (option);
            break;
        case 3:
            do {
                filter_pipes();

                option = input_validation<int>("Choose the option:  ", 0, 5);
                system("cls");

                switch (option) {
                case 1:
                    select_all(AllPipe, FilteredPipe);
                    break;
                case 2:
                    FilteredPipe = filter_by_id(AllPipe);
                    break;
                case 3:
                    filter_by_name(AllPipe, FilteredPipe);
                    break;
                case 4:
                    filter_by_status_of_repair(AllPipe, FilteredPipe);
                    break;
                case 5:
                    DELETE_OBJECTS(FilteredPipe);
                    break;
                }
                if (option) {
                    pause();
                }
                
            } while (option);
            break;
        case 4:
            do {
                filter_cs();

                option = input_validation<int>("Choose the option:  ", 0, 5);
                system("cls");

                switch (option) {
                case 1:
                    select_all(AllCS, FilteredCS);
                    break;
                case 2:
                    FilteredCS = filter_by_id(AllCS);
                    break;
                case 3:
                    filter_by_name(AllCS, FilteredCS);
                    break;
                case 4:
                    filter_by_percent_in_work(AllCS, FilteredCS);
                    break;
                case 5:
                    DELETE_OBJECTS(FilteredCS);
                    break;
                }
                if (option) {
                    pause();
                }
            } while (option);
            break;
        case 5:
            do {
                veiw_menu();

                option = input_validation<int>("Choose the option:  ", 0, 2);
                system("cls");

                switch (option) {
                case 1:
                    veiw_all("------------------------------\n          All Pipes\n------------------------------", AllPipe);
                    veiw_all("------------------------------\n   All Compressor Stations\n------------------------------", AllCS);
                    break;
                case 2:
                    veiw_filtered("------------------------------\n        Filtered Pipes\n------------------------------", AllPipe, FilteredPipe);
                    veiw_filtered("------------------------------\n Filtered Compressor Stations\n------------------------------", AllCS, FilteredCS);
                    break;
                }
                if (option) {
                    pause();
                }
            } while (option);
            break;
        
        case 6:
            save_objects(AllPipe, AllCS);
            pause();
            break;

        case 7:
            download_objects(AllPipe, AllCS, FilteredPipe, FilteredCS);
            pause();
            break;
        }
    }
}