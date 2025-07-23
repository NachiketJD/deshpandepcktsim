#include "parser.h"
#include <fstream>
#include <sstream>

using namespace std;

bool loadTopology(const string& filename, Graph& graph) {
    ifstream infile(filename);
    if (!infile.is_open()) {
        cerr << "Error: Cannot open " << filename << endl;
        return false;
    }

    string line;
    bool readingNodes = false, readingLinks = false;

    while (getline(infile, line)) {
        if (line.empty() || line[0] == '#') {
            if (line.find("# Nodes") != string::npos)
                readingNodes = true, readingLinks = false;
            else if (line.find("# Links") != string::npos)
                readingLinks = true, readingNodes = false;
            continue;
        }

        istringstream iss(line);

        if (readingNodes) {
            string name, protocol;
            iss >> name >> protocol;
            graph[name] = Node(name, protocol);
        } else if (readingLinks) {
            string n1, n2;
            int cost, bandwidth;
            iss >> n1 >> n2 >> cost >> bandwidth;

            if (graph.find(n1) != graph.end() && graph.find(n2) != graph.end()) {
                graph[n1].addNeighbor(n2, cost, bandwidth);
                graph[n2].addNeighbor(n1, cost, bandwidth); // bidirectional
            }
        }
    }

    infile.close();
    return true;
}
