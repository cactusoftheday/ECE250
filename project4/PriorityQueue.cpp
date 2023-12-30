//
// Created by kijij on 11/28/2023.
//

#include "PriorityQueue.h"
#include "Graph.h"

PriorityQueue::PriorityQueue() : capacity(MAX_VERTICES), size(0) {
    vertices = new int[capacity];
    distances = new double[capacity];
}
PriorityQueue::~PriorityQueue(){
    delete[] vertices;
    delete[] distances;
}

void PriorityQueue::push(int vertex, double distance) {
    vertices[size] = vertex;
    distances[size] = distance;
    heapifyUp(size);
    size++;
}

int PriorityQueue::pop() {
    if (empty()) {
        return -1; // Return an invalid index
    }

    int topVertex = vertices[0];
    vertices[0] = vertices[size - 1];
    distances[0] = distances[size - 1];
    size--;
    heapifyDown(0);

    return topVertex;
}

bool PriorityQueue::empty() {
    return size == 0;
}

void PriorityQueue::heapifyUp(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (distances[index] < distances[parent]) { //swap
            int tempVertex = vertices[index];
            double tempDistance = distances[index];
            vertices[index] = vertices[parent];
            distances[index] = distances[parent];
            vertices[parent] = tempVertex;
            distances[parent] = tempDistance;
            index = parent;
        } else {
            break;
        }
    }
}

void PriorityQueue::heapifyDown(int index) {
    while (true) {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int smallest = index;

        if (leftChild < size && distances[leftChild] < distances[smallest]) {
            smallest = leftChild;
        }

        if (rightChild < size && distances[rightChild] < distances[smallest]) {
            smallest = rightChild;
        }

        if (smallest != index) { //swap
            int tempVertex = vertices[index];
            double tempDistance = distances[index];
            vertices[index] = vertices[smallest];
            distances[index] = distances[smallest];
            vertices[smallest] = tempVertex;
            distances[smallest] = tempDistance;
            index = smallest;
        } else {
            break;
        }
    }
}