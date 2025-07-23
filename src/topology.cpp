#include "topology.h"

void Topology::loadFromFile(const std::string& filename) {
    std::ifstream in(filename);
    std::string line;

    while (std::getline(in, line)) {
        if (line.empty() || line[0] == '#') continue;

        std::istringstream iss(line);
        if (line.find("R") == 0) {
            // Format: R1 OSPF
            std::string name, proto;
            iss >> name >> proto;
            nodes[name] = {proto};
        } else {
            // Format: R1 R2 10 100
            std::string n1, n2;
            int cost, bw;
            iss >> n1 >> n2 >> cost >> bw;
            links.push_back({n1, n2, cost, bw});
        }
    }
}

Graph Topology::buildGraph() const {
    Graph g;

    for (const auto& [name, info] : nodes) {
        g[name] = Node(name, info.protocol);
    }

    for (const auto& link : links) {
        g[link.node1].addNeighbor(link.node2, link.cost, link.bandwidth);
        g[link.node2].addNeighbor(link.node1, link.cost, link.bandwidth);
    }

    return g;
}
