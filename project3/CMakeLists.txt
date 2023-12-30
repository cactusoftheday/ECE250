cmake_minimum_required(VERSION 3.0)
project(project3)

set(CMAKE_CXX_STANDARD 11)

add_executable(project3 main.cpp
        Quadtree.cpp
        Quadtree.h
        Point.cpp
        Point.h
        illegal_exception.cpp
        illegal_exception.h
)
