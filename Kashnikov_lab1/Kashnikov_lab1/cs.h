#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>


using namespace std;

class CS {
	static int MaxID;

	int id;

	string name;
	int amount_of_workspaces;
	int workspaces_in_work;
	int efficiency;

	vector<std::unordered_set<int>> links = { {}, {} };
public:
	CS();
	CS(ifstream& file);

	static int get_MaxID();
	int get_id() const;
	string get_name() const;
	int get_workload() const;

	static void set_MaxID(const int new_MaxID);
	void start_workspace();
	void stop_workspace();

	bool InUsing() const;
	vector<std::unordered_set<int>> get_links() const;
	void set_links(std::ifstream& file, const int& pos);
	bool addLink(const int& pos, const int& id);
	bool delLink(const int& pos, const int& id);

	void save(ofstream& file) const;

	friend ostream& operator << (ostream& out, const CS& cs);
	friend istream& operator >> (istream& in, CS& cs);
};

