//
// Created by kijij on 11/27/2023.
//

#ifndef PROJECT4_EDGE_H
#define PROJECT4_EDGE_H

#include <string>

class Edge {
public:
    Edge(int destination, double distance, double speedLimit, double adjustment);

    ~Edge();

    int getDestination() const;

    double getDistance() const;

    double getSpeedLimit() const;

    double getTraffic() const;

    void setDistance(double distance);

    void setSpeedLimit(double speedLimit);

    void setTraffic(double traffic);

    void setAdjustment(double adjustment);

    Edge* next; //might need or might not need
private:
    double traffic;

    int destination;
    double distance;
    double speedLimit;
    double adjustment;
};


#endif //PROJECT4_EDGE_H
