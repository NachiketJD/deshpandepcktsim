#pragma once
#include "../src/node.h"
#include <unordered_map>

using Graph = std::unordered_map<std::string, Node>;

void runRIP(Graph& network, const std::string& sourceNodeName);
