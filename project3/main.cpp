#include <iostream>
#include "Quadtree.h"
#include "Point.h"
#include "illegal_exception.h"

int main() {
    Quadtree* quadtree;
    std::string cmd;
    while(std::cin >> cmd){
        //std::cout << "MAX SIZE: " << quadtree->getMaxSize() << std::endl;
        if(cmd == "INIT"){
            int size;
            float x0,y0,x1,y1;
            std::cin >> size;
            std::cin >> x0;
            std::cin >> y0;
            std::cin >> x1;
            std::cin >> y1;
            try {
                quadtree = new Quadtree(size,x0,y0,x1,y1);
            } catch (const illegal_exception& e) {
                std::cout << e.what() << std::endl;
                continue;
            }
            std::cout << "success" << std::endl;
        }
        if(cmd == "INSERT"){
            float x,y;
            std::cin >> x;
            std::cin >> y;
            std::cout << (quadtree->insert(x,y) ? "success" : "failure") << std::endl;
        }
        if(cmd == "SEARCH"){
            float x,y,d;
            std::cin >> x;
            std::cin >> y;
            std::cin >> d;
            std::cout << (quadtree->search(x,y,d) ? "point exists" : "no point exists") << std::endl;
        }
        if(cmd == "NEAREST"){
            float x,y;
            std::cin >> x;
            std::cin >> y;
            Point* point = quadtree->nearest(x,y);
            if(point == nullptr){
                std::cout << "no point exists" << std::endl;
                continue;
            }
            std::cout << point->x << " " << point->y << std::endl;
        }
        if(cmd == "RANGE"){
            float x0,y0,x1,y1;
            std::cin >> x0;
            std::cin >> y0;
            std::cin >> x1;
            std::cin >> y1;
            std::string points;
            try {
                if(x0 < quadtree->getBottomLeft()->x || y0 < quadtree->getBottomLeft()->y || x1 > quadtree->getTopRight()->x || y1 > quadtree->getTopRight()->y){
                    throw illegal_exception();
                }
                points = quadtree->range(x0,y0,x1,y1);
            }
            catch (const illegal_exception& e){
                std::cout << e.what() << std::endl;
                continue;
            }
            if(points == ""){
                std::cout << "no points within range" << std::endl;
            }
            else{
                std::cout << points << std::endl;
            }
        }
        if(cmd == "NUM"){
            std::cout << quadtree->num() << std::endl;
        }
        if(cmd == "EXIT"){
            delete quadtree;
            return 0;
        }
    }
    delete quadtree;
    return 0;
}
