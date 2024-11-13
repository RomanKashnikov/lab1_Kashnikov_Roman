#include <unordered_map>
#include <unordered_set>

#include "filter.h"
#include "utils.h"
#include "pipe.h"
#include "cs.h"


using namespace std;


bool check_status_of_repair(const Pipe& pipe, const bool is_repair) {
    return pipe.get_repair() == is_repair;
}


void filter_by_status_of_repair(const unordered_map<int, Pipe>& pipes, unordered_set<int>& selected_pipes) {
    cout << "Filter by repair status" << endl << endl;

    int work_status = input_validation<bool>("Repair status (1-Yes/0-No):  ", 0, 1);

    find_by_filter<Pipe, bool>(pipes, selected_pipes, check_status_of_repair, work_status);
}


bool check_percent_in_work(const CS& cs, const int percent) {
    return cs.get_workload() == percent;
}


void filter_by_percent_in_work(const unordered_map<int, CS>& cs, unordered_set<int>& selected_cs) {
    cout << "Filter by percent of workspaces in work" << endl << endl;

    int percent = input_validation<int>("Enter percent (0-100):  ", 0, 100);

    find_by_filter<CS, int>(cs, selected_cs, check_percent_in_work, percent);
}