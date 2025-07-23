// protocols/eigrp.cpp

#include "eigrp.h"
#include <queue>
#include <limits>

using namespace std;

void runEIGRP(Graph& network, const string& sourceNodeName) {
    unordered_map<string, int> dist;
    unordered_map<string, string> prev;

    for (const auto& [name, _] : network) {
        dist[name] = INT_MAX;
    }

    dist[sourceNodeName] = 0;
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<>> pq;
    pq.push({0, sourceNodeName});

    while (!pq.empty()) {
        auto [currDist, currNode] = pq.top();
        pq.pop();

        if (currDist > dist[currNode]) continue;

        for (const Link& link : network[currNode].neighbors) {
            const string& neighbor = link.neighbor;
            int weight = link.cost;

            if (dist[currNode] + weight < dist[neighbor]) {
                dist[neighbor] = dist[currNode] + weight;
                prev[neighbor] = currNode;
                pq.push({dist[neighbor], neighbor});
            }
        }
    }

    for (const auto& [dest, _] : network) {
        if (dest == sourceNodeName) continue;

        string current = dest;
        stack<string> path;
        while (current != sourceNodeName && prev.find(current) != prev.end()) {
            path.push(current);
            current = prev[current];
        }

        if (current == sourceNodeName && !path.empty()) {
            network[sourceNodeName].routingTable[dest] = path.top();
        }
    }
}
