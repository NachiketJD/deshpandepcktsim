#include <bits/stdc++.h>
#include "topology.h"
#include "node.h"
#include "../protocols/ospf.h"
#include "../protocols/rip.h"
#include "../protocols/eigrp.h"


using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <topology_file>\n";
        return 1;
    }

    string filename = argv[1];
    Topology topology;
    topology.loadFromFile(filename);

    // Step 1: Build nodes
    unordered_map<string, Node> graph;
    for (const auto& [nodeName, nodeInfo] : topology.nodes) {
        graph[nodeName] = Node(nodeName, nodeInfo.protocol);
    }

    // Step 2: Add neighbors from links
    for (const auto& link : topology.links) {
        graph[link.node1].addNeighbor(link.node2, link.cost, link.bandwidth);
        graph[link.node2].addNeighbor(link.node1, link.cost, link.bandwidth);
    }

    // Step 3: Run protocols
    // Run OSPF or RIP or EIGRP based on the protocol of each node 
   for (auto& [nodeName, node] : graph) {
    if (node.protocol == "OSPF") {
        runOSPF(graph, nodeName);
    } else if (node.protocol == "RIP") {
        runRIP(graph, nodeName);
    }
}




    // Step 4: Display Routing Tables
    for (const auto& [nodeName, node] : graph) {
        node.printRoutingTable();
    }

    return 0;
}
