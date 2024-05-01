#include "FlightMap.h"

using namespace std;

FlightMap::FlightMap(const string& filePath) { loadCSV(filePath); }

void FlightMap::loadCSV(const string& filePath) {
/* Loads data from a csv file to an adjacency matrix.
 * Receives: const string& filePath: a csv file path to read
 * Returns: void
 */
    adjMatrix = vector<vector<pair<int, int>>>(APT::NUM_OF_APT, vector<pair<int, int>>(APT::NUM_OF_APT, {0, 0}));
    /* adjMatrix looks like
     *          0 |       1 |       2
     * 0|   {0, 0}|{120, 75}|   {0, 0}
     * 1|{200, 95}|   {0, 0}|{175, 45}
     * 2|   {0, 0}|{120, 60}|   {0, 0}
     *
     * From Apt 0 to Apt 1: Cost is 120 and Duration is 75
     * From Apt 1 to Apt 2: Not connected
     */


    fstream inputFile(filePath, ios::in); // Open file with read mode

    string line;
    // Stores each line into string variable line, this looks like "0,1,500,120"
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
/* Finds and displays the cheapest route, using Dijkstra's Algorithm
 * Receives: int from: Origin Apt by number, int to: Destination Apt by number
 * Returns: void
 */
    vector<vector<int>> costs; // costs = {AptIndex: {Cost, PrevApt}, AptIndex: {Cost, PrevApt}, ... }
    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> minHeap;
    // minHeap = {{Cost, AptIndex}, {Cost, AptIndex}, ... }
    // Cost should come first because cost should be compared for minHeap

    // Initializes all airport with infinity cost and null previous airport except source airport
    for (int i = 0; i < APT::NUM_OF_APT; i++) {
        if (i == from) costs.push_back({0, -1});
        else costs.push_back({INT_MAX, -1});
    }

    minHeap.push({costs[from][0], from});

    while (!minHeap.empty()) {
        auto current = minHeap.top(); // {Cost, AptIndex}
        int cost = current[0];
        int currApt = current[1];
        minHeap.pop();

        for (int nextApt = 0; nextApt < APT::NUM_OF_APT; nextApt++) {
            if (adjMatrix[currApt][nextApt].first != 0) { // If connected (Not 0 means connected)
                int flightCost = adjMatrix[currApt][nextApt].first; // adjMatrix[currApt][nextApt] = {Cost, Duration}
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
    int curr = to; // We are now at the destination Apt, and go back to the origin
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
/* Finds and displays the fastest route, using Dijkstra's Algorithm
 * Receives: int from: Origin Apt by number, int to: Destination Apt by number
 * Returns: void
 */
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
        auto current = minHeap.top(); // {Duration, AptIndex}
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