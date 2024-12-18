#pragma once
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <cmath>

#include "GTNetwork.h"

using namespace std;

template<typename T>
vector<T> GTNetwork::metodDeikstra(T StartNode, T EndNode) {
    unordered_map<T, int> dist;
    unordered_map<T, T> prev;
    unordered_set<T> visited;


    for (const auto& pair : this->graph) {
        dist[pair.first] = fabs(this->INF);
    }
    dist[StartNode] = 0;

    priority_queue<pair<int, T>, vector<pair<int, T>>, greater<pair<int, T>>> pq;
    pq.push({ 0, StartNode });

    while (!pq.empty()) {
        T u = pq.top().second;
        pq.pop();

        if (u == EndNode) { break; }

        visited.insert(u);

        for (const auto& v : this->graph.at(u)) {
            if (visited.find(v) == visited.end()) {
                int weight = fabs(this->getDistance(u, v));
                if (weight != this->INF && dist[u] != this->INF && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    prev[v] = u;
                    pq.push({ dist[v], v });
                }
            }
        }
    }

    vector<T> path;
    T current_node = EndNode;
    while (current_node != StartNode) {
        path.push_back(current_node);
        if (prev.find(current_node) != prev.end()) {
            current_node = prev[current_node];
        }
        else {
            return vector<T>();
        }
    }

    path.push_back(StartNode);
    reverse(path.begin(), path.end());
    return path;
}
