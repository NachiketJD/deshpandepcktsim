#include <bits/stdc++.h>
#include "topology.h"
#include "node.h"
#include "../protocols/ospf.h"
#include "../protocols/rip.h"
#include "../protocols/eigrp.h"
#include "../protocols/bgp.h"  // ✅ BGP header

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
    unordered_map<string, BGPNode> bgpNodes;

    // Example ASN mapping (update if needed)
    unordered_map<string, int> bgpASN = {
        {"R1", 65001}, {"R2", 65002}, {"R3", 65003}
    };

    for (const auto& [nodeName, nodeInfo] : topology.nodes) {
        if (nodeInfo.protocol == "BGP") {
            if (bgpASN.find(nodeName) == bgpASN.end()) {
                cerr << "ASN not defined for BGP node: " << nodeName << "\n";
                continue;
            }
            int nodeId = nodeName[1] - '0';  // e.g., "R1" -> 1
            int asn = bgpASN[nodeName];
            bgpNodes[nodeName] = BGPNode(nodeId, asn);
        } else {
            graph[nodeName] = Node(nodeName, nodeInfo.protocol);
        }
    }

    // Step 2: Add neighbors (for non-BGP)
    for (const auto& link : topology.links) {
        if (graph.count(link.node1) && graph.count(link.node2)) {
            graph[link.node1].addNeighbor(link.node2, link.cost, link.bandwidth);
            graph[link.node2].addNeighbor(link.node1, link.cost, link.bandwidth);
        }
        // BGP links can be handled separately if required
    }

    // Step 3: Run protocols
    for (auto& [nodeName, node] : graph) {
        if (node.protocol == "OSPF") {
            runOSPF(graph, nodeName);
        } else if (node.protocol == "RIP") {
            runRIP(graph, nodeName);
        } else if (node.protocol == "EIGRP") {
            runEIGRP(graph, nodeName);
        }
    }

    // Step 4: Simulate BGP
    if (!bgpNodes.empty()) {
        // R1 advertises a prefix
        bgpNodes["R1"].advertiseRoute("10.1.0.0/16");

        // R2 receives from R1
        for (auto route : bgpNodes["R1"].exportRoutes()) {
            bgpNodes["R2"].receiveRoute(route);
        }

        // R3 receives from R2
        for (auto route : bgpNodes["R2"].exportRoutes()) {
            bgpNodes["R3"].receiveRoute(route);
        }
    }

    // Step 5: Print all routing tables
    for (const auto& [nodeName, node] : graph) {
        node.printRoutingTable();
    }

    for (const auto& [nodeName, bgpNode] : bgpNodes) {
        bgpNode.displayRoutingTable();
    }

    return 0;
}
