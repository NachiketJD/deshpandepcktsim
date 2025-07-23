#pragma once
#include <bits/stdc++.h>
#include "node.h"  // ✅ Needed for Node class

struct NodeInfo {
    std::string protocol;
};

struct LinkInfo {
    std::string node1;
    std::string node2;
    int cost;
    int bandwidth;
};

class Topology {
public:
    std::map<std::string, NodeInfo> nodes;
    std::vector<LinkInfo> links;

    void loadFromFile(const std::string& filename);
    Graph buildGraph() const;  // ✅ Add this function declaration
};

// ✅ Define Graph type after Topology class
using Graph = std::unordered_map<std::string, Node >;
