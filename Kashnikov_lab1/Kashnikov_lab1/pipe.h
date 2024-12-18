#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>


using namespace std;

class Pipe {
	static int MaxID;

	int MAXperfomance;

	unordered_map<int, int> dictPerfomances = {
		{500, 5},
		{700, 12},
		{1000, 30},
		{1400, 95}
	};

	int id;

	string name;
	double lenght;
	int diameter;
	bool repair;

	
	vector<int> links = { 0, 0 };
public:
	Pipe();
	Pipe(const int& dmtr, const int& lenght);
	Pipe(ifstream& file);

	static int get_MaxID();
	int get_id() const;
	string get_name() const;
	int get_diameter() const;
	int get_length() const;
	bool get_repair() const;
	int get_MAXperfomance() const;


	bool InUsing() const;
	vector<int> get_links() const;
	bool set_links(const int& out, const int& in);

	static void set_MaxID(const int new_MaxID);
	void set_repair(const bool new_repair);
	void save(ofstream& file) const;

	friend ostream& operator << (ostream& out, const Pipe& pipe);
	friend istream& operator >> (istream& in, Pipe& pipe);
};