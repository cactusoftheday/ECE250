//
// Created by kijij on 11/1/2023.
//

#ifndef PROJECT3_QUADTREE_H
#define PROJECT3_QUADTREE_H

#include "string"
#include "Point.h"
#include <stdexcept>



class Quadtree {
    public:
        Quadtree(int m, float x0, float y0, float x1, float y1);
        Quadtree(float x0, float y0, float x1, float y1);
        ~Quadtree();

        bool insert(float x, float y);
        bool search(float x, float y, float d);
        Point* nearest(float x, float y);
        std::string range(float xr0, float yr0, float xr1, float yr1);
        int num();

        static int getNumPoints();

        Point *getBottomLeft() const;

        Point *getTopRight() const;

private:
        Point* bottomLeft;
        Point* topRight;
        static int maxSize;
        int currentSize;
        Point** array;
        bool isLeaf; //determines whether algo should look through this node
        static int numPoints;

        Quadtree *topleftTree;
        Quadtree *toprightTree;
        Quadtree *bottomleftTree;
        Quadtree *bottomrightTree;
};



#endif //PROJECT3_QUADTREE_H
