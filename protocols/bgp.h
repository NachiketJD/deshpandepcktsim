#ifndef BGP_H
#define BGP_H

#include <string>
#include <vector>
#include <map>

struct BGPRoute {
    std::string destination;
    std::vector<int> asPath;
    std::string nextHop;
};

class BGPNode {
public:
    BGPNode(int id, int asn);
    void advertiseRoute(const std::string& dest);
    void receiveRoute(const BGPRoute& route);
    void withdrawRoute(const std::string& dest);
    void displayRoutingTable() const;
    std::vector<BGPRoute> exportRoutes() const;
    int getASN() const;

private:
    int nodeId;
    int asNumber;
    std::map<std::string, BGPRoute> routingTable;
};

#endif
