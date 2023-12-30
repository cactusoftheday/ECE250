//
// Created by kijij on 11/27/2023.
//

#ifndef PROJECT4_GRAPH_H
#define PROJECT4_GRAPH_H

#include <fstream>
#include <limits>
#include "Edge.h"

const int MAX_VERTICES = 500001; //only 500k vertices allowed

class Graph {
private:
    Edge* adjacencyList[MAX_VERTICES] = {nullptr}; //i guess index 0 will remain empty forever lol
public:
    ~Graph();
    std::string load(const std::string& filename);
    void insertOrUpdateEdge(int a, int b, double d, double s);
    std::string insert(int a, int b, double d, double s);
    std::string print(int a);
    std::string deleteVertex(int a);
    std::string path(int a, int b, bool toggle);
    bool traffic(int a, int b, double factor);
    bool trafficHelper(int a, int b, double factor);
    std::string update(const std::string& filename);
};


#endif //PROJECT4_GRAPH_H
