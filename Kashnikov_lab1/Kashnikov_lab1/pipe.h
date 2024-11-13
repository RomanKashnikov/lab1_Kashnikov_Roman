#pragma once
#include <iostream>
#include <string>

#include "unordered_map"
#include "unordered_set"

using namespace std;

class Pipe {
	int id;
	string name;
	double lenght;
	int diameter;
	bool repair;
	static int MaxID;

public:
	Pipe();
	Pipe(ifstream& file);

	static int get_MaxID();
	int get_id() const;
	string get_name() const;
	//double get_lenght() const;
	//int get_diameter() const;
	bool get_repair() const;

	static void set_MaxID(const int new_MaxID);
	void set_repair(const bool new_repair);
	void save(ofstream& file) const;

	friend ostream& operator << (ostream& out, const Pipe& pipe);
	friend istream& operator >> (istream& in, Pipe& pipe);
};

void package_edit_pipe(unordered_map<int, Pipe>& AllPipe, unordered_set<int>& FilteredPipe);