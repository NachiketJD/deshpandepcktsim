#pragma once
#include <bits/stdc++.h>
#include "node.h"

using Graph = std::unordered_map<std::string, Node>;

bool loadTopology(const std::string& filename, Graph& graph);
