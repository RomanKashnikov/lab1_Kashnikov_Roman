#pragma once
#include <iostream>
#include <string>

#include "unordered_map"
#include "unordered_set"

using namespace std;

class CS {
	static int MaxID;
	int id;
	string name;
	int amount_of_workspaces;
	int workspaces_in_work;
	int efficiency;

public:
	CS();
	CS(ifstream& file);

	static int get_MaxID();
	int get_id() const;
	string get_name() const;
	//int get_amount_of_workspaces() const;
	//int get_workspaces_in_work() const;
	//int get_efficiency() const;
	int get_workload() const;

	//void set_workspaces_in_work(int new_workspaces_in_work);
	static void set_MaxID(const int new_MaxID);
	void start_workspace();
	void stop_workspace();
	void save(ofstream& file) const;

	friend ostream& operator << (ostream& out, const CS& cs);
	friend istream& operator >> (istream& in, CS& cs);
};

void package_edit_cs(unordered_map<int, CS>& AllCS, unordered_set<int>& FilteredCS);

