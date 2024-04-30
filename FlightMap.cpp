#include "FlightMap.h"

using namespace std;

FlightMap::FlightMap(const std::string& filePath) { loadCSV(filePath); }

void FlightMap::loadCSV(const std::string& filePath) {
    adjMatrix = vector<vector<pair<int, int>>>(APT::NUM_OF_APT, vector<pair<int, int>>(APT::NUM_OF_APT, {0, 0}));
    fstream inputFile(filePath, ios::in); // Open file with read mode

    string line;
    // Store each line into string variable line, this looks like "0, 1, 500, 120"
    while (getline(inputFile, line)) {
        // We want to convert string to sstream to use getline to separate data by comma
        std::istringstream iss(line);
        int from, to, cost, duration;
        char comma;
        iss >> from >> comma >> to >> comma >> cost >> comma >> duration;
        adjMatrix[from][to] = {cost, duration};
    }
    inputFile.close();
}

void FlightMap::findCheapestByDijkstra(int from, int to) const {
    vector<vector<int>> costs; // costs = {AptIndex: {Cost, PrevApt}, AptIndex: {Cost, PrevApt}, ... }
    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> minHeap;
    // minHeap = {{Cost, AptIndex}, {Cost, AptIndex}, ... }

    // Initialize all airport with infinity cost and null previous airport except source airport
    for (int i = 0; i < APT::NUM_OF_APT; i++) {
        if (i == from) costs.push_back({0, -1});
        else costs.push_back({INT_MAX, -1});
    }

    minHeap.push({costs[from][0], from});

    while (!minHeap.empty()) {
        auto current = minHeap.top(); // {Cost, AptIndex, PrevApt}
        int cost = current[0];
        int currApt = current[1];
        minHeap.pop();

        for (int nextApt = 0; nextApt < APT::NUM_OF_APT; nextApt++) {
            if (adjMatrix[currApt][nextApt].first != 0) { // If connected
                int flightCost = adjMatrix[currApt][nextApt].first;
                if (cost + flightCost < costs[nextApt][0]) {
                    costs[nextApt][0] = cost + flightCost; // Update destination cost
                    costs[nextApt][1] = currApt; // Update previous apt
                    minHeap.push({costs[nextApt][0], nextApt});
                }
            }
        }
    }

    cout << "\nThe cheapest flight cost from " << APT::APT_DICT.at(from) << " to "
         << APT::APT_DICT.at(to) << ": $" << costs[to][0] << endl;

    stack<string> route;
    int curr = to;
    while (curr != from) {
        route.push(APT::APT_DICT.at(curr));
        curr = costs[curr][1]; // Want to go back to the origin airport from the destination
    }

    cout << "The route: " << APT::APT_DICT.at(from);
    while (!route.empty()) {
        cout << " -> " << route.top();
        route.pop();
    }
    cout << endl;
}

void FlightMap::findShortestByDijkstra(int from, int to) const {
    vector<vector<int>> durations; // costs = {AptIndex: {Duration, PrevApt}, AptIndex: {Duration, PrevApt}, ... }
    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> minHeap;
    // minHeap = {{Duration, AptIndex}, {Duration, AptIndex}, ... }

    // Initialize all airport with infinity cost and null previous airport except source airport
    for (int i = 0; i < APT::NUM_OF_APT; i++) {
        if (i == from) durations.push_back({0, -1});
        else durations.push_back({INT_MAX, -1});
    }

    minHeap.push({durations[from][0], from});

    while (!minHeap.empty()) {
        auto current = minHeap.top(); // {Cost, AptIndex, PrevApt}
        int cost = current[0];
        int currApt = current[1];
        minHeap.pop();

        for (int nextApt = 0; nextApt < APT::NUM_OF_APT; nextApt++) {
            if (adjMatrix[currApt][nextApt].second != 0) { // If connected
                int flightCost = adjMatrix[currApt][nextApt].second;
                if (cost + flightCost < durations[nextApt][0]) {
                    durations[nextApt][0] = cost + flightCost; // Update destination duration
                    durations[nextApt][1] = currApt; // Update previous apt
                    minHeap.push({durations[nextApt][0], nextApt});
                }
            }
        }
    }
    cout << "\nThe shortest flight time from " << APT::APT_DICT.at(from) << " to "
         << APT::APT_DICT.at(to) << ": " << durations[to][0] << " mins" << endl;

    stack<string> route;
    int curr = to;
    while (curr != from) {
        route.push(APT::APT_DICT.at(curr));
        curr = durations[curr][1]; // Want to go back to the origin airport from the destination
    }

    cout << "The route: " << APT::APT_DICT.at(from);
    while (!route.empty()) {
        cout << " -> " << route.top();
        route.pop();
    }
    cout << endl;
    cout << endl;
}