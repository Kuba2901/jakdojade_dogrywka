#pragma once
#include "point.h"

struct BFSPoint {
    Point *point;
    int distance;
    bool visited;

    BFSPoint(Point *point_, int distance_, bool visited_): point(point_), distance(distance_), visited(visited_) {

    }
};