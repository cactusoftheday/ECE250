#include <iostream>
#include "illegal_exception.h"
#include "Graph.h"

int main() {
    std::string cmd;
    Graph* graph = new Graph();
    while(std::cin >> cmd){
        if(cmd == "INSERT"){
            int a,b;
            double d,s;
            std::cin >> a;
            std::cin >> b;
            std::cin >> d;
            std::cin >> s;
            try {
                std::cout << graph->insert(a,b,d,s) << std::endl;
            } catch (const illegal_exception& e) {
                std::cout << e.what() << std::endl;
                continue;
            }
        }
        if(cmd == "LOAD"){
            std::string filename;
            std::cin >> filename;
            try {
                std::cout << graph->load(filename) << std::endl;
            } catch (const illegal_exception& e) {
                std::cout << e.what() << std::endl;
                continue;
            }
        }
        if(cmd == "PRINT"){
            int a;
            std::cin >> a;
            try {
                std::cout << graph->print(a)<< std::endl;
            } catch (const illegal_exception& e) {
                std::cout << e.what() << std::endl;
                continue;
            }
        }
        if(cmd == "DELETE"){
            int a;
            std::cin >> a;
            try {
                std::cout << graph->deleteVertex(a)<< std::endl;
            } catch (const illegal_exception& e) {
                std::cout << e.what() << std::endl;
                continue;
            }
        }
        if(cmd == "PATH"){
            int a,b;
            std::cin >> a;
            std::cin >> b;
            try {
                std::cout << graph->path(a,b,true)<< std::endl;
            } catch (const illegal_exception& e) {
                std::cout << e.what() << std::endl;
                continue;
            }
        }
        if(cmd == "LOWEST"){
            int a,b;
            std::cin >> a;
            std::cin >> b;
            try {
                std::cout << graph->path(a,b,false) << std::endl;
            } catch (const illegal_exception& e) {
                std::cout << e.what() << std::endl;
                continue;
            }
        }
        if(cmd == "TRAFFIC"){
            int a,b;
            double factor;
            std::cin >> a;
            std::cin >> b;
            std::cin >> factor;
            try {
                std::cout << (graph->traffic(a,b,factor) ? "success" : "failure") << std::endl;
            } catch (const illegal_exception& e) {
                std::cout << e.what() << std::endl;
                continue;
            }
        }
        if(cmd == "UPDATE"){
            std::string filename;
            std::cin >> filename;
            try {
                std::cout << graph->update(filename) << std::endl;
            } catch (const illegal_exception& e) {
                std::cout << e.what() << std::endl;
                continue;
            }
        }
        if(cmd == "END"){
            break;
        }
    }
    delete graph;
    return 0;
}
