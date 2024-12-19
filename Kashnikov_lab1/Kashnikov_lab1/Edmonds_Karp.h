#pragma once
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#include <algorithm>
#include "GTNetwork.h"

using namespace std;


template<typename T>
bool GTNetwork::bfs(T s, T t, unordered_map<T, T>& parent, unordered_map<T, unordered_map<T, int>>& capacity) {
    unordered_set<T> visited;
    queue<T> q;
    q.push(s);
    visited.insert(s);

    while (!q.empty()) {
        auto& u = q.front();
        q.pop();

        for (auto& v : this->graph.at(u)) {
            if (visited.find(v) == visited.end() && capacity[u][v] > 0) {
                visited.insert(v);
                parent[v] = u; // Сохраняем родителя
                if (v == t) {
                    return true;
                }
                q.push(v);
            }
        }
    }
    return false;
}

template<typename T>
int GTNetwork::edmondsKarp(const T& source, const T& sink) {

    unordered_map<T, unordered_map<T, int>> capacity;

    for (const auto& pair : graph) {
        for (auto& v : pair.second) {
            capacity[pair.first][v] = this->getCapacity(pair.first, v);
        }
    }

    unordered_map<T, T> parent; // Изменение: используем unordered_map для хранения родительских узлов
    int maxFlow = 0;

    while (this->bfs(source, sink, parent, capacity)) {
        int pathFlow = this->INF;
        for (auto v = sink; v != source; v = parent[v]) { // Изменение: используем unordered_map для поиска
            auto u = parent[v];
            pathFlow = min(pathFlow, capacity[u][v]);
        }

        for (auto v = sink; v != source; v = parent[v]) { // Изменение: используем unordered_map для поиска
            auto u = parent[v];
            capacity[u][v] -= pathFlow;
            capacity[v][u] += pathFlow;
        }

        maxFlow += pathFlow;
    }

    this->maxFlow_path = this->getMAXFlowPath(source, sink, parent);
    return maxFlow;
}

template<typename T>
vector<T> GTNetwork::getMAXFlowPath(const T& source, const T& sink, const unordered_map<T, T>& parent) { // Изменение: принимаем unordered_map
    vector<T> path;
    for (auto v = sink; v != source; v = parent.at(v)) { // Изменение: используем unordered_map для поиска
        path.push_back(v);
    }
    path.push_back(source);
    reverse(path.begin(), path.end());
    return path;
}
