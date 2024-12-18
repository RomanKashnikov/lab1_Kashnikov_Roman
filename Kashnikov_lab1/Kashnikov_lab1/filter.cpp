#include <iostream>
#include "filter.h"

using namespace std;


bool GTNetwork::check_status_of_repair(const Pipe& pipe, const bool& is_repair) {
    return pipe.get_repair() == is_repair;
}


bool GTNetwork::find_by_status_in_repair() {
    cout << "working status(0 - no / 1 - yes): ";
    bool work_status = input_validation<bool>("Repair status (1-Yes/0-No):  ", 0, 1);

    this->find_by_filter<Pipe, bool>(AllPipe, FilteredPipe, &GTNetwork::check_status_of_repair, work_status);
    return 1;
}


bool GTNetwork::check_percent_in_work(const CS& cs, const int& percent) {
    return cs.get_workload() == percent;
}


bool GTNetwork::find_by_percent_in_work() {
    cout << "Filter by percent of workspaces in work" << endl << endl;

    int percent = input_validation<int>("Enter percent (0-100):  ", 0, 100);

    this->find_by_filter<CS, int>(AllCS, FilteredCS, &GTNetwork::check_percent_in_work, percent);
    return 1;
}


bool GTNetwork::check_by_diameter(const Pipe& pipe, const int& diameter) {
    return pipe.get_diameter() == diameter;
}


bool GTNetwork::check_by_lenght(const Pipe& pipe, const int& length) {
    if (length == this->INF) {
        return 1;
    }
    return pipe.get_length() == length;
}


int GTNetwork::find_by_diameter(const int& diameter, const int& length) {
    for (const auto& [id, pipe] : this->AllPipe) {
        if (!pipe.InUsing() && this->check_by_diameter(pipe, diameter) && this->check_by_lenght(pipe, length))
            return pipe.get_id();
    }

    Pipe pipe(diameter, length);
    this->AllPipe.emplace(pipe.get_id(), pipe);

    return pipe.get_id();
}