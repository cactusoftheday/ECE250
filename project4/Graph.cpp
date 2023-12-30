//
// Created by kijij on 11/27/2023.
//

#include "Graph.h"
#include "illegal_exception.h"
#include "PriorityQueue.h"
#include <limits>

Graph::~Graph(){
    for(int i = 0; i < MAX_VERTICES; i++){
        Edge* current = adjacencyList[i];
        while(current != nullptr){
            Edge* p_old = current;
            current = current->next;
            delete p_old;
        }
    }
}

std::string Graph::load(const std::string& filename) { //written by ChatGPT
    // Implement loading from the dataset file
    // Update the graph accordingly
    std::ifstream file(filename);
    int a, b;
    double d, s;
    while (file >> a >> b >> d >> s) {
        insert(a, b, d, s); // Assume A = 1 while inserting
    }
    return "success";
}
void Graph::insertOrUpdateEdge(int a, int b, double d, double s){
    if(a < 1 || a > 500000 || b < 1 || b > 500000 || d < 0 || s < 0){
        throw illegal_exception();
    }
    Edge* newEdge = new Edge(b,d,s,1.0);
    if(adjacencyList[a] == nullptr){ //inserting new edge
        adjacencyList[a] = newEdge;
    }
    else{ //updating an old edge, used for updating traffic value and overwriting inserts
        Edge* current = adjacencyList[a];
        Edge* prev = nullptr;
        //can't insert to front because we need to check through the entire linked list for duplicate old edges
        while(current != nullptr && current->getDestination() < newEdge->getDestination()){
            prev = current;
            current = current->next;
        }
        //sort the linked list
        if(current == nullptr){
            //inserting new edge
            if(prev != nullptr){
                prev->next = newEdge;
            }
            else{
                adjacencyList[a] = newEdge;
            }
        }
        else if(current->getDestination() == b){
            //replacing old edge
            current->setDistance(newEdge->getDistance());
            current->setSpeedLimit(newEdge->getSpeedLimit());
            //apparently you don't set a new adjustment factor here...
            delete newEdge;
        }
        else{
            newEdge->next = current;
            if(prev == nullptr){
                adjacencyList[a] = newEdge; //insert at head
            }
            else{
                prev->next = newEdge;
            }
        }
    }
}
std::string Graph::insert(int a, int b, double d, double s){
    insertOrUpdateEdge(a, b, d, s);
    insertOrUpdateEdge(b, a, d, s);
    return "success";
}
std::string Graph::print(int a){
    if(a < 1 || a > 500000){
        throw illegal_exception();
    }
    if(adjacencyList[a] == nullptr){
        return "failure";
    }
    std::string list = "";
    Edge* current = adjacencyList[a];
    while(current != nullptr){
        list += std::to_string(current->getDestination()) + " ";
        current = current->next;
    }
    return list;
}

std::string Graph::deleteVertex(int a) {
    if(a < 1 || a > 500000){
        throw illegal_exception();
    }
    if(adjacencyList[a] != nullptr){
        Edge* current = adjacencyList[a];
        while(current != nullptr){
            int currentConnected = current->getDestination();
            Edge* temp = adjacencyList[currentConnected];
            Edge* prev = nullptr;
            while(temp != nullptr){
                if(temp->getDestination() == a){
                    if (prev == nullptr){
                        adjacencyList[currentConnected] = temp->next;
                    }
                    else{
                        prev->next = temp->next;
                    }
                    delete temp; //remove other node's connection to a
                    break;
                }
                prev = temp;
                temp = temp->next;
            }
            Edge* p_old = current;
            current = current->next;
            delete p_old; //delete head
        }
        adjacencyList[a] = nullptr;
        return "success";
    }
    else{
        return "failure";
    }
}

std::string Graph::path(int a, int b, bool toggle){//if true, return path, otherwise return weight
    if(a < 1 || a > 500000 || b < 1 || b > 500000){
        throw illegal_exception();
    }
    double traffic[MAX_VERTICES];
    bool visited[MAX_VERTICES];
    int previous[MAX_VERTICES];

    for(int i = 0; i < MAX_VERTICES; i++){
        //initialize all vertex distances to inf
        traffic[i] = std::numeric_limits<double>::infinity();
        visited[i] = false;
        previous[i] = -1;
    }
    traffic[a] = 0.0; //initialize starting node to 0 traffic

    PriorityQueue PQ; //created a priority queue class in the end...
    PQ.push(a, 0.0);

    while(!PQ.empty()){
        int current = PQ.pop();
        if (visited[current]) {
            continue;
        }
        visited[current] = true;
        Edge* edge = adjacencyList[current];
        while (edge != nullptr) {
            int neighbor = edge->getDestination();
            double newDist = traffic[current] + edge->getTraffic();

            if (newDist < traffic[neighbor]) {
                traffic[neighbor] = newDist;
                previous[neighbor] = current;
                PQ.push(neighbor, newDist);
            }
            edge = edge->next;
        }
    }

    if (traffic[b] == std::numeric_limits<double>::infinity()) {
        return "failure";
    }
    if(toggle){ //if true print path
        std::string pathString = std::to_string(b);
        int currentVertex = b;
        while (previous[currentVertex] != -1) {
            pathString = std::to_string(previous[currentVertex]) + " " + pathString;
            currentVertex = previous[currentVertex]; //recount our path
        }

        return pathString;
    }
    else{
        return "lowest is " + std::to_string(traffic[b]);
    }
}

bool Graph::traffic(int a, int b, double factor){
    return trafficHelper(a,b,factor) | trafficHelper(b,a,factor);
    //dodge short circuit boolean evaluation by using the bitwise OR
}

bool Graph::trafficHelper(int a, int b, double factor){
    if(a < 1 || a > 500000 || b < 1 || b > 500000 || factor < 0){
        throw illegal_exception();
    }// case for illegal argument
    if(adjacencyList[a] == nullptr || adjacencyList[b] == nullptr || factor > 1){
        return false;
    }
    Edge* current = adjacencyList[a];
    while(current != nullptr){
        if(current->getDestination() == b){
            current->setAdjustment(factor); //this sets a new factor and recalculates traffic
            return true; //successfully sets
        }
        current = current->next;
    }
    return false; //edge did not exist
}

std::string Graph::update(const std::string& filename) {
    // Implement loading from the dataset file
    // Update the graph accordingly
    std::ifstream file(filename);
    int a, b;
    double factor;
    bool returnValue = false;
    while (file >> a >> b >> factor) {
        returnValue = returnValue || traffic(a, b, factor);
    }
    return (returnValue ? "success" : "failure");
}