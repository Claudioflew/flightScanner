#ifndef FLIGHTADJLIST_H
#define FLIGHTADJLIST_H

#include "APT.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <stack>

class FlightMap {
public:
    FlightMap(const std::string&);
    void loadCSV(const std::string&);

    void findCheapestByDijkstra(int, int) const;
    void findShortestByDijkstra(int, int) const;

private:
    std::vector<std::vector<std::pair<int, int>>> adjMatrix;
};


#endif
