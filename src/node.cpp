#include "node.h"
using namespace std;

// Constructor to initialize the node
Node::Node(string name, string protocol) : name(name), protocol(protocol) {}

// Add a neighbor with given cost and bandwidth
void Node::addNeighbor(const string& neighborName, int cost, int bandwidth) {
    neighbors.push_back({neighborName, cost, bandwidth});
}

// Print the routing table of this node
void Node::printRoutingTable() const {
    cout << "Routing Table for Node " << name << " (" << protocol << "):\n";
    for (const auto& entry : routingTable) {
        cout << "  Destination: " << entry.first << " -> Next Hop: " << entry.second << '\n';
    }
    cout << endl;
}
