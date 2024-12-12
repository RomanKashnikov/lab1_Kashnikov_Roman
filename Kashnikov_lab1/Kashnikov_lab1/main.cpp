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
#include "GTNetwork.h"


using namespace std;
using namespace chrono;



void pause() {
    cout << endl;
    system("pause");
    system("cls");
}

int main() {
    int option;
    GTNetwork gtn;

    redirect_output_wrapper cerr_out(cerr);
    string time = format("{:%d_%m_%Y %H_%M_%OS}", system_clock::now());
    ofstream logfile("logger/log_" + time);
    if (logfile)
        cerr_out.redirect(logfile);

    while (1) {
        menu();

        option = input_validation<int>("Choose the option:  ", 0, 8);
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
                    gtn.add_Pipe();
                    break;
                case 2:
                    gtn.set_pipes_by_id(1);
                    break;
                case 3:
                    gtn.change_status_of_repair();
                    break;
                case 4:
                    gtn.delete_selected_pipes();
                    break;
                case 5:
                    gtn.print_filtered_pipes();
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
                    gtn.add_CS();
                    break;
                case 2:
                    gtn.set_cs_by_id(1);
                    break;
                case 3:
                    gtn.change_workload();
                    break;
                case 4:
                    gtn.delete_selected_cs();
                    break;
                case 5:
                    gtn.print_filtered_CS();
                    break;
                }
                if (option) {
                    pause();
                }
            } while (option);
            break;
        case 3:
            do {
                gtn_menu();

                option = input_validation<int>("Choose the option:  ", 0, 7);
                system("cls");

                switch (option) {
                case 1:
                    gtn.create_graph();
                    break;
                case 2:
                    gtn.add_node();
                    break;
                case 3:
                    gtn.delPipeFromGraph();
                    break;
                case 4:
                    gtn.delCSFromGraph();
                    break;
                case 5:
                    gtn.clear_graph();
                    break;
                case 6:
                    gtn.make_TS();
                    break;
                case 7:
                    gtn.print_graph();
                    break;
                }
                if (option) {
                    pause();
                }

            } while (option);
            break;
        case 4:
            do {
                filter_pipes();

                option = input_validation<int>("Choose the option:  ", 0, 4);
                system("cls");

                switch (option) {
                case 1:
                    gtn.select_all_pipes();
                    break;
                case 2:
                    gtn.set_pipes_by_id(0);
                    break;
                case 3:
                    gtn.find_pipes_by_name();
                    break;
                case 4:
                    gtn.find_by_status_in_repair();
                    break;
                }
                if (option) {
                    pause();
                }
                
            } while (option);
            break;
        case 5:
            do {
                filter_cs();

                option = input_validation<int>("Choose the option:  ", 0, 4);
                system("cls");

                switch (option) {
                case 1:
                    gtn.select_all_pipes();
                    break;
                case 2:
                    gtn.set_cs_by_id(0);
                    break;
                case 3:
                    gtn.find_cs_by_name();
                    break;
                case 4:
                    gtn.find_by_percent_in_work();
                    break;
                }
                if (option) {
                    pause();
                }
            } while (option);
            break;
        case 6:
            cout << gtn;
            /*do {
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
            } while (option);*/
            break;
        
        case 7:
            gtn.save_objects();
            pause();
            break;

        case 8:
            gtn.download_objects();
            pause();
            break;
        }
    }
}