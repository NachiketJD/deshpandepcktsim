#include "rip.h"

void runRIP(Graph& network, const std::string& sourceNodeName) {
    Node& srcNode = network[sourceNodeName];

    // Initially, each node only knows itself
    for (auto& [name, _] : network) {
        srcNode.routingTable[name] = (name == sourceNodeName) ? "-" : "";
    }

    // Simulate simple distance vector exchange (one round)
    for (const Link& link : srcNode.neighbors) {
        const std::string& neighborName = link.neighbor;
        Node& neighbor = network[neighborName];

        // Learn neighbor's routing table
        for (const auto& [dest, nextHop] : neighbor.routingTable) {
            if (dest == sourceNodeName) continue;

            // If we don't know dest or we find a shorter path
            if (srcNode.routingTable[dest].empty()) {
                srcNode.routingTable[dest] = neighborName;
            }
        }

        // Also add direct neighbor
        if (srcNode.routingTable[neighborName].empty()) {
            srcNode.routingTable[neighborName] = neighborName;
        }
    }
}
