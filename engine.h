#pragma once
#include <iostream>
#include "custom_vector.h"
#include "point.h"
#include "city.h"
#include "custom_queue.h"
#include "custom_priority_queue.h"
#include "bfs_point.h"
#include "linked_list.h"
#include "custom_unordered_map.h"
#include <limits>

const int INF = std::numeric_limits<int>::max();

class Engine
{
    // Map related
    CustomVector<CustomVector<Point *>> map;
    int height, width;

    // Cities' locations
    CustomVector<City *> cities;

    // BFS map
    CustomVector<CustomVector<BFSPoint *>> visitedFields;

    // Adjacency list
    CustomUnorderedMap adjacencyList;

    // Cities' vector indexes
    CustomUnorderedMap citiesIndexes;

public:
    Engine();
    virtual void getMap();
    virtual void printMap();
    virtual void findCities();
    virtual Point* findCityExit(int xBegin, int xEnd, int y);
    virtual bool inBounds(Point* pt);
    virtual void printCities();
    virtual bool isTraversable(Point *pt);
    virtual void createAdjacencyMatrix();
    virtual CustomVector<BFSPoint *> getNeighbors(BFSPoint* point);
    virtual City* findCity(Point *point);
    virtual void resetVisited();
    virtual void printNeighbors();
    virtual void getAtKey(CustomString key);
    virtual void getFlights();
    virtual KVPair<int, KVPair<int, CustomVector<int>>> dijkstra(CustomString start, CustomString dest, int type);
    virtual void sortNodes();
    virtual void printPath(KVPair<int, KVPair<int, CustomVector<int>>> result);
    virtual void getQueries();
};