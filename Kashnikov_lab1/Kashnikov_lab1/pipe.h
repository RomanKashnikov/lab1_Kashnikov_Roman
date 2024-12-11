#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>


using namespace std;

class Pipe {
	static int MaxID;

	int id;

	string name;
	double lenght;
	int diameter;
	bool repair;
	
	vector<int> links = { 0, 0 };
public:
	Pipe();
	Pipe(const int dmtr);
	Pipe(ifstream& file);

	static int get_MaxID();
	int get_id() const;
	string get_name() const;
	int get_diameter() const;
	bool get_repair() const;

	bool InUsing() const;
	vector<int> get_links() const;
	bool set_links(const int& out, const int& in);

	static void set_MaxID(const int new_MaxID);
	void set_repair(const bool new_repair);
	void save(ofstream& file) const;

	friend ostream& operator << (ostream& out, const Pipe& pipe);
	friend istream& operator >> (istream& in, Pipe& pipe);
};