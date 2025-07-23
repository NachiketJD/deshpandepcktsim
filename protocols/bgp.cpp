#include "bgp.h"
#include <iostream>
#include <algorithm>

BGPNode::BGPNode(int id, int asn) : nodeId(id), asNumber(asn) {}

int BGPNode::getASN() const {
    return asNumber;
}

void BGPNode::advertiseRoute(const std::string& dest) {
    BGPRoute route;
    route.destination = dest;
    route.asPath.push_back(asNumber);
    route.nextHop = "self";
    routingTable[dest] = route;
}

void BGPNode::receiveRoute(const BGPRoute& route) {
    if (std::find(route.asPath.begin(), route.asPath.end(), asNumber) != route.asPath.end())
        return;

    auto it = routingTable.find(route.destination);
    if (it == routingTable.end() || route.asPath.size() + 1 < it->second.asPath.size()) {
        BGPRoute newRoute = route;
        newRoute.asPath.insert(newRoute.asPath.begin(), asNumber);
        newRoute.nextHop = "via ASN " + std::to_string(route.asPath.front());
        routingTable[route.destination] = newRoute;
    }
}

void BGPNode::withdrawRoute(const std::string& dest) {
    routingTable.erase(dest);
}

void BGPNode::displayRoutingTable() const {
    std::cout << "\nBGP Table [AS " << asNumber << "]:\n";
    for (const auto& [dest, route] : routingTable) {
        std::cout << "  " << dest << " via ";
        for (int as : route.asPath)
            std::cout << as << " ";
        std::cout << "| Next hop: " << route.nextHop << "\n";
    }
}

std::vector<BGPRoute> BGPNode::exportRoutes() const {
    std::vector<BGPRoute> exported;
    for (const auto& [_, route] : routingTable)
        exported.push_back(route);
    return exported;
}
