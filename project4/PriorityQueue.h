//
// Created by kijij on 11/28/2023.
//

#ifndef PROJECT4_PRIORITYQUEUE_H
#define PROJECT4_PRIORITYQUEUE_H


class PriorityQueue {
public:
    PriorityQueue();
    ~PriorityQueue();
    void push(int vertex, double distance);
    int pop();
    bool empty();

private:
    int* vertices;
    double* distances;
    int capacity;
    int size;

    void heapifyUp(int index);
    void heapifyDown(int index);
};

#endif //PROJECT4_PRIORITYQUEUE_H
