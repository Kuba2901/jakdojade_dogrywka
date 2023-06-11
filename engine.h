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
#include <cstring>

const int INF = std::numeric_limits<int>::max();

class Engine
{
    // Map related
    JakDojadeVector<JakDojadeVector<Point *>> map;
    int height, width;

    // Cities' locations
    JakDojadeVector<City *> cities;

    // BFS map
    JakDojadeVector<JakDojadeVector<BFSPoint *>> visitedFields;

    // Adjacency list
    JakDojadeHashMap adjacencyList;

    // Cities' vector indexes
    JakDojadeHashMap citiesIndexes;

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
    virtual JakDojadeVector<BFSPoint *> getNeighbors(BFSPoint* point);
    virtual City* findCity(Point *point);
    virtual void resetVisited();
    virtual void printNeighbors();
    virtual void getFlights();
    virtual KVPair<int, KVPair<int, JakDojadeVector<int>>> dijkstra(JakDojadeString start, JakDojadeString dest, int type);
    virtual void printPath(KVPair<int, KVPair<int, JakDojadeVector<int>>> result);
    virtual void getQueries();
};