#pragma once
#include <queue>
#include <unordered_map>
#include <unordered_set>


using namespace std;

template<typename T>
vector<T> Kan_by_Volkov(unordered_map<T, unordered_set<T>>& graph)
{
	unordered_map<T, int> inDegree;

	for (const auto& pair : graph) {
		const T& vertex = pair.first;
		inDegree[vertex] = 0;
	}

	for (const auto& pair : graph) {
		const T& vertex = pair.first;
		for (const T& neighbor : pair.second) {
			inDegree[neighbor]++;
		}
	}

	queue<T> zero;

	for (const auto& pair : inDegree) {
		if (pair.second == 0) {
			zero.push(pair.first);
		}
	}

	vector<T> sort;
	while (!zero.empty()) {
		T vertex = zero.front();
		zero.pop();
		sort.push_back(vertex);

		for (const T& neighbor : graph.at(vertex)) {
			inDegree[neighbor]--;
			if (inDegree[neighbor] == 0) {
				zero.push(neighbor);
			}
		}
	}

	if (sort.size() != inDegree.size()) {
		return {  };
	}
	else {
		return sort;
	}
}