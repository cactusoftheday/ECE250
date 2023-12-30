cmake_minimum_required(VERSION 3.22)
project(project4)

set(CMAKE_CXX_STANDARD 11)

add_executable(project4 main.cpp
        Graph.cpp
        Graph.h
        Edge.cpp
        Edge.h
        illegal_exception.h
        illegal_exception.cpp
        PriorityQueue.cpp
        PriorityQueue.h
        PriorityQueue.h
        PriorityQueue.cpp)
