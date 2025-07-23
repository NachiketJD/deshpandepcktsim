// src/ospf.h

#pragma once
#include "../src/node.h"
#include <unordered_map>

// Alias for the entire network
using Graph = std::unordered_map<std::string, Node>;

// Run OSPF (Dijkstra's algorithm) for a given source node
void runOSPF(Graph& network, const std::string& sourceNodeName);
