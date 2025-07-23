// src/node.h

#pragma once
#include <bits/stdc++.h>

struct Link {
    std::string neighbor;
    int cost;
    int bandwidth;
};

class Node {
public:
    std::string name;
    std::string protocol; // RIP, OSPF, EIGRP
    std::vector<Link> neighbors;
    std::map<std::string, std::string> routingTable; // dest -> next hop

    Node(std::string name, std::string protocol);

    void addNeighbor(const std::string& neighborName, int cost, int bandwidth);
    void printRoutingTable() const;
};
