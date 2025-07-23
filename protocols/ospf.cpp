#include "ospf.h"
#include <queue>
#include <limits>
#include <stack>

using namespace std;

// Implements Dijkstra's algorithm to build the routing table
void runOSPF(Graph& network, const string& sourceNodeName) {
    // Distance to each node from source
    unordered_map<string, int> dist;

    // Store previous hop to reconstruct shortest path
    unordered_map<string, string> prev;

    // Min-priority queue: (cost, node name)
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<>> pq;

    // Initialize distances to infinity
    for (const auto& [nodeName, _] : network) {
        dist[nodeName] = INT_MAX;
    }

    dist[sourceNodeName] = 0;
    pq.push({0, sourceNodeName});

    while (!pq.empty()) {
        auto [currDist, currNode] = pq.top();
        pq.pop();

        if (currDist > dist[currNode]) continue; // Already visited with shorter path

        for (const Link& link : network[currNode].neighbors) {
            const string& neighbor = link.neighbor;
            int cost = link.cost;

            // Relaxation step
            if (dist[currNode] + cost < dist[neighbor]) {
                dist[neighbor] = dist[currNode] + cost;
                prev[neighbor] = currNode;
                pq.push({dist[neighbor], neighbor});
            }
        }
    }

    // Update the routing table for the source node
    for (const auto& [dest, _] : network) {
        if (dest == sourceNodeName) continue;

        // Reconstruct path from source to dest
        string current = dest;
        stack<string> path;

        while (current != sourceNodeName && prev.find(current) != prev.end()) {
            path.push(current);
            current = prev[current];
        }

        if (current == sourceNodeName && !path.empty()) {
            // Next hop is the first node after source
            network[sourceNodeName].routingTable[dest] = path.top();
        }
    }
}
