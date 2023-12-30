//
// Created by kijij on 11/1/2023.
//

#include "Quadtree.h"
#include "cmath"
#include "Point.h"
#include "illegal_exception.h"

int Quadtree::numPoints = 0;
int Quadtree::maxSize = -1;

Quadtree::Quadtree(int m, float x0, float y0, float x1,  float y1){
    if(x0 > x1 || y0 > y1){
        throw illegal_exception();
    }
    bottomLeft = new Point(x0, y0);
    topRight = new Point(x1, y1);

    maxSize = m;
    currentSize = 0;
    array = new Point*[m];
    for(int i = 0; i < maxSize; i++){
        array[i] = nullptr;
    }
    isLeaf = true;
    topleftTree = nullptr;
    toprightTree = nullptr;
    bottomleftTree = nullptr;
    bottomrightTree = nullptr;
    //number of points start off at 0
}
Quadtree::Quadtree(float x0, float y0, float x1, float y1){
    bottomLeft = new Point(x0, y0);
    topRight = new Point(x1, y1);

    currentSize = 0;
    array = new Point*[maxSize];
    for(int i = 0; i < maxSize; i++){
        array[i] = nullptr;
    }
    isLeaf = true;
    topleftTree = nullptr;
    toprightTree = nullptr;
    bottomleftTree = nullptr;
    bottomrightTree = nullptr;
    //number of points start off at 0
}

Point *Quadtree::getBottomLeft() const {
    return bottomLeft;
}

Point *Quadtree::getTopRight() const {
    return topRight;
}

Quadtree::~Quadtree(){
    if(isLeaf){
        for(int i = 0 ; i < currentSize; i++){
            delete array[i];
        }
        delete[] array; //delete array of points
        delete bottomLeft;
        delete topRight;
    }
    else{
        delete bottomLeft;
        delete topRight;
        for(int i = 0 ; i < currentSize; i++){
            delete array[i];
        }
        delete[] array; //delete array of points
        //delete child trees
        delete toprightTree;
        delete topleftTree;
        delete bottomrightTree;
        delete bottomleftTree;
    }
}

int Quadtree::getNumPoints() {
    return numPoints;
}

bool Quadtree::insert(float x, float y)   {
    if(x < bottomLeft->x || x > topRight->x || y < bottomLeft->y || y > topRight->y){
        return false;
    }
    float xHalf = (topRight->x - bottomLeft->x) / 2 + bottomLeft->x;
    float yHalf = (topRight->y - bottomLeft->y) / 2 + bottomLeft->y;
    if(isLeaf){
        //we use bottom left and top right such as (0,0) and (10,10)
        //Point* newPoint = new Point(x, y);
        if(currentSize >= maxSize){
            //split up the original grid into its 4 quadtrees
            bottomleftTree = new Quadtree(bottomLeft->x, bottomLeft->y, xHalf, yHalf);
            bottomrightTree = new Quadtree(xHalf, bottomLeft->y, topRight->x, yHalf);
            topleftTree = new Quadtree(bottomLeft->x, yHalf, xHalf, topRight->y);
            toprightTree = new Quadtree(xHalf, yHalf, topRight->x, topRight->y);

            for (int i = 0; i < maxSize; ++i) { //iterate through current subtree
                Point* currentPoint = array[i];
                if(currentPoint->y >= yHalf){
                    //inserts into top node even if on boundary
                    if(currentPoint->x <= xHalf){
                        //inserts into left node if on boundary
                        topleftTree->insert(currentPoint->x, currentPoint->y);
                    }
                    else{
                        toprightTree->insert(currentPoint->x, currentPoint->y);
                    }
                }
                else{
                    if(currentPoint->x <= xHalf){
                        //inserts into left node if on boundary
                        bottomleftTree->insert(currentPoint->x, currentPoint->y);
                    }
                    else{
                        bottomrightTree->insert(currentPoint->x, currentPoint->y);
                    }
                }
            }

            //finally we must insert the new point
            isLeaf = false; //we can no longer use this current tree to insert
            numPoints = numPoints - maxSize; //we've shifted the points to other quadtrees
            //when we insert the new points we need to make sure we aren't duplicating the number of points
            if(y >= yHalf){
                //inserts into top node even if on boundary
                if(x <= xHalf){
                    //inserts into left node if on boundary
                    return topleftTree->insert(x, y);
                }
                else{
                    return toprightTree->insert(x, y);
                }
            }
            else{
                if(x <= xHalf){
                    //inserts into left node if on boundary
                    return bottomleftTree->insert(x, y);
                }
                else{
                    return bottomrightTree->insert(x, y);
                }
            }
        }
        else{ //base case
            //we are not creating new subtrees
            //perhaps we need to check if this new point is on the boundaries. It may exist in other quadtrees already.
            for(int i = 0; i < currentSize;i++){
                if(x == array[i]->x && y == array[i]->y){
                    return false;
                }
            }
            array[currentSize] = new Point(x,y);
            currentSize++; //increment size
            numPoints++; //increment number of total points
            return true;
        }
    }
    else{ //search farther down the line
        if(y >= yHalf){
            //inserts into top node even if on boundary
            if(x <= xHalf){
                //inserts into left node if on boundary
                return topleftTree->insert(x, y);
            }
            else{
                return toprightTree->insert(x, y);
            }
        }
        else{
            if(x <= xHalf){
                //inserts into left node if on boundary
                return bottomleftTree->insert(x, y);
            }
            else{
                return bottomrightTree->insert(x, y);
            }
        }
        //check if on boundary and adjust return statements accordingly
    }
}

float calcDistance(Point* originPoint, Point* givenPoint){
    if(givenPoint == nullptr){
        return INTMAX_MAX; //returns int max if given point is nullptr
        //guarantees any comparison with nullptr will not set nullptr as nearest point
    }
    return sqrt(std::pow(((originPoint->x) - (givenPoint->x)),2) + std::pow(((originPoint->y) - (givenPoint->y)), 2));
}

bool Quadtree::search(float x, float y, float d) {
    if(isLeaf){ //base case
        //search this leaf
        Point* originPoint = new Point(x,y);
        float distance;
        for(int i = 0; i < currentSize; i++){
            Point* currentPoint = array[i];
            distance = calcDistance(originPoint, currentPoint);
            if(distance < d){
                delete originPoint;
                return true;
            }
        }
        delete originPoint;
        return false;
    }
    else{
        return (topleftTree->search(x,y,d) ||
        toprightTree->search(x,y,d) ||
        bottomleftTree->search(x,y,d) ||
        bottomrightTree->search(x,y,d));
        //search subtrees and OR their return values, so we know at least if one point exists
    }
}

bool fallsWithin(float xr0, float yr0, float xr1, float yr1, Point* point){
    return (point->x > xr0 && point->x < xr1 && point->y < yr1 && point->y > yr0);
}

std::string Quadtree::range(float xr0, float yr0, float xr1, float yr1){
    //idea: recursively go down the tree and search each quadtree for if something is in that range
    if(xr0 > xr1 || yr0 > yr1){
        throw illegal_exception();
    }
    if(isLeaf){ //base case
        std::string returnString = "";
        for(int i = 0; i < currentSize; i++){
            Point* currentPoint = array[i];
            bool withinRect = fallsWithin(xr0,yr0,xr1,yr1,currentPoint);
            if(withinRect){
                returnString = returnString + std::to_string(currentPoint->x) + " " + std::to_string(currentPoint->y) + " ";
            }
        }
        return returnString;
    }
    else{
        //we must look farther down the quadtree
        //this should account for some trees having 0 points in them
        return topleftTree->range(xr0,yr0,xr1,yr1) + toprightTree->range(xr0,yr0,xr1,yr1) + bottomleftTree->range(xr0,yr0,xr1,yr1) + bottomrightTree->range(xr0,yr0,xr1,yr1);
    }
}

Point* Quadtree::nearest(float x, float y){
    //idea: recursively go down tree. At each leaf node, we should find the nearest node
    Point* originPoint = new Point(x,y); //needs to be deleted later
    if(isLeaf){
        Point* nearestPoint = array[0];
        if(nearestPoint == nullptr){
            delete originPoint;
            return nullptr;
        }
        for(int i = 1; i < currentSize; i++){
            Point* currentPoint = array[i];
            if(calcDistance(originPoint, currentPoint) <= calcDistance(originPoint, nearestPoint)){
                //if nearer than current nearest point
                if(calcDistance(originPoint, currentPoint) == calcDistance(originPoint, nearestPoint)){
                    if(currentPoint->x < nearestPoint->x){ //compare x and y values
                        continue;
                    }
                    else if (currentPoint->x == nearestPoint->x){
                        if(currentPoint->y < nearestPoint->y){
                            continue;
                        }
                        nearestPoint = currentPoint;
                    }
                    else{
                        nearestPoint = currentPoint;
                    }
                }
                else{
                    nearestPoint = currentPoint;
                }
            }
        }
        delete originPoint;
        return nearestPoint; //return nearestPoint to be calculated
    }
    else{
        //need to compare the 4 quadtrees and see which subtree's point was closest
        Point* nearestPoint = topleftTree->nearest(x,y);
        Point* compPoint = toprightTree->nearest(x,y);
        if(calcDistance(originPoint, nearestPoint) >= calcDistance(originPoint, compPoint)){
            //top right tree nearest point is closer to origin point
            if(calcDistance(originPoint, nearestPoint) == calcDistance(originPoint, compPoint) && calcDistance(originPoint, compPoint) != INTMAX_MAX){
                if(compPoint->x > nearestPoint->x){
                    nearestPoint = compPoint;
                }
                else if(compPoint->x == nearestPoint->x){
                    if(compPoint->y > nearestPoint->y){
                        nearestPoint = compPoint;
                    }
                }
                else{
                    nearestPoint = compPoint;
                }
            }
            else{
                nearestPoint = compPoint;
            }
        }
        compPoint = bottomleftTree->nearest(x,y);
        if(calcDistance(originPoint, nearestPoint) > calcDistance(originPoint, compPoint)){
            //bottom left tree nearest point is closer to origin point
            if(calcDistance(originPoint, nearestPoint) == calcDistance(originPoint, compPoint) && calcDistance(originPoint, compPoint) != INTMAX_MAX){
                if(compPoint->x > nearestPoint->x){
                    nearestPoint = compPoint;
                }
                else if(compPoint->x == nearestPoint->x){
                    if(compPoint->y > nearestPoint->y){
                        nearestPoint = compPoint;
                    }
                }
                else{
                    nearestPoint = compPoint;
                }
            }
            else{
                nearestPoint = compPoint;
            }
        }
        compPoint = bottomrightTree->nearest(x,y);
        if(calcDistance(originPoint, nearestPoint) > calcDistance(originPoint, compPoint)){
            //bottom left tree nearest point is closer to origin point
            if(calcDistance(originPoint, nearestPoint) == calcDistance(originPoint, compPoint) && calcDistance(originPoint, compPoint) != INTMAX_MAX){
                if(compPoint->x > nearestPoint->x){
                    nearestPoint = compPoint;
                }
                else if(compPoint->x == nearestPoint->x){
                    if(compPoint->y > nearestPoint->y){
                        nearestPoint = compPoint;
                    }
                }
                else{
                    nearestPoint = compPoint;
                }
            }
            else{
                nearestPoint = compPoint;
            }
        }
        delete originPoint;
        return nearestPoint;
    }
    //will need to convert point to proper coordinates later
}

int Quadtree::num() {
    return getNumPoints();
}
