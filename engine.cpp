#include "engine.h"

Engine::Engine()
{
}

void Engine::getMap()
{
    // Getting map dimensions
    int height_, width_;
    std::cin >> width_ >> height_;

    // Setting engine properties
    this->height = height_;
    this->width = width_;

    // Char buffer
    char c;

    // Getting the map
    for (size_t y = 0; y < height_; y++)
    {
        CustomVector<Point *> row;
        for (size_t x = 0; x < width_; x++)
        {
            std::cin >> c;
            row.push_back(new Point(x, y, c));
        }

        this->map.push_back(row);
    }
}

void Engine::printMap()
{
    for (size_t y = 0; y < this->height; y++)
    {
        for (size_t x = 0; x < this->width; x++)
        {
            printf("%c", this->map[y][x]->c);
        }

        printf("\n");
    }
}

void Engine::findCities() {
    for (int y = 0; y < this->height; ++y) {
        int xBegin = -1;
        int xEnd = -1;

        bool nameFound = false;
        CustomString cityName;

        for (int x = 0; x < this->width; ++x) {
            Point *pt = this->map[y][x];

            if (pt->c >= 65 && pt->c <= 90) {
                // Start counting if not already
                if (!nameFound) {
                    xBegin = x;
                    cityName.append(pt->c);
                } else {
                    cityName.append(pt->c);
                }

                nameFound = true;
            } else {
                if (nameFound) {
                    xEnd = x;

                    // Find the city exit
                    Point *exit = findCityExit(xBegin, xEnd, y);
                    this->cities.push_back(new City(cityName, exit));

                    cityName.clear();
                    xBegin = -1;
                    xEnd = -1;
                }
                nameFound = false;

            }
        }
    }
}

Point* Engine::findCityExit(int xBegin, int xEnd, int y) {
    // Above the name
    for (int i = xBegin - 1; i < xEnd + 1; ++i) {
        Point *pt = new Point(i, y - 1, ' ');

        // Only proceed if the point is in bounds
        if (inBounds(pt)) {
            // Swap the character if in bounds
            pt = this->map[pt->y][pt->x];

            if (pt->c == '*') {
                return pt;
            }
        }
    }

    // On the level of the name
    Point *before = new Point(xBegin - 1, y, ' ');
    Point *after = new Point(xEnd + 1, y, ' ');

    if (inBounds(before)) {
        if (map[before->y][before->x]->c == '*') return map[before->y][before->x];
    }
    else if (inBounds(after)) {
        if (map[after->y][after->x]->c == '*') return map[after->y][after->x];
    }

    // Below the name
    for (int i = xBegin - 1; i < xEnd + 1; ++i) {
        Point *pt = new Point(i, y + 1, ' ');

        // Only proceed if the point is in bounds
        if (inBounds(pt)) {
            // Swap the character if in bounds
            pt = this->map[pt->y][pt->x];

            if (pt->c == '*') {
                return pt;
            }
        }
    }
}

bool Engine::inBounds(Point* pt) {
    return (pt->x >= 0 && pt->x < this->width && pt->y >= 0 && pt->y < this->height);
}

void Engine::printCities() {
    for (int i = 0; i < this->cities.getSize(); ++i) {
        City *city = this->cities[i];
        Point *exit = city->point;
        printf("City: %s at (%d, %d)!\n", city->name.c_str(), exit->x, exit->y);
    }
}

bool Engine::isTraversable(Point *pt) {
    return inBounds(pt) && (pt->c == '#' || pt->c == '*');
}



void Engine::createAdjacencyMatrix() {
    // Keep track of visited fields
    for (int y = 0; y < this->height; ++y) {
        CustomVector<BFSPoint *> row;

        for (int x = 0; x < this->width; ++x) {
            row.push_back(new BFSPoint(this->map[y][x], 0, false));
        }

        visitedFields.push_back(row);
    }

    CustomQueue<BFSPoint*> queue;

    // Get neighbors of each city
    for (int cityNum = 0; cityNum < this->cities.getSize(); ++cityNum) {
        resetVisited();

        // begin with the first city and mark it as visited
        City *firstCity = cities.getData()[cityNum];

        CityLinkedList *cityNeighbors = new CityLinkedList();

        // Push the first city with weight 0
        cityNeighbors->append(new CityNode(firstCity->name, 0));

        visitedFields[firstCity->point->y][firstCity->point->x]->visited = true;

        // Push the first city to the queue
        queue.push(visitedFields[firstCity->point->y][firstCity->point->x]);

        while (!queue.empty()) {
            // Check whether a city was encountered in the current move
            bool cityEncountered = false;

            // Dequeue a vertex from queue and print it
            BFSPoint *front = queue.front();
            queue.pop();

            if (front->point->c == '*' && (front->point->x != firstCity->point->x && front->point->y != firstCity->point->y)) {
                City* city = findCity(front->point);
                cityEncountered = true;
                cityNeighbors->append(new CityNode(city->name, front->distance));
            }

            if (!cityEncountered) {
                // Get current point's neighbors
                CustomVector<BFSPoint *> neighbors = getNeighbors(front);

                for (int i = 0; i < neighbors.getSize(); ++i) {
                    // Get all adjacent vertices of the dequeued
                    if (!neighbors[i]->visited) {
                        neighbors[i]->visited = true;
                        queue.push(neighbors[i]);
                    }
                }
            }

        }

        adjacencyList.insertList(cityNeighbors);
    }
}

CustomVector<BFSPoint *> Engine::getNeighbors(BFSPoint* origin) {
    CustomVector<BFSPoint *> neighbors;

    const int dx[] = {0, 0, -1, 1};
    const int dy[] = {-1, 1, 0, 0};

    // 4 because 4 directions
    for (int i = 0; i < 4; ++i) {
        int currX = origin->point->x + dx[i];
        int currY = origin->point->y + dy[i];

        Point *testPoint = new Point(currX, currY, ' ');

        if (inBounds(testPoint) && isTraversable(this->map[currY][currX]) && !this->visitedFields[currY][currX]->visited) {
            BFSPoint *pt = this->visitedFields[currY][currX];
            pt->distance = origin->distance + 1;
//            printf("FOUND NEIGHBOR: (%d, %d, %c)\n", pt->point->x, pt->point->y, pt->point->c);
            neighbors.push_back(pt);
        }

        delete testPoint;
    }

    return neighbors;
}

City* Engine::findCity(Point *point) {
    for (int i = 0; i < this->cities.getSize(); ++i) {
        if (cities[i]->point->x == point->x && cities[i]->point->y == point->y) {
            return cities[i];
        }
    }

    return nullptr;
}

void Engine::resetVisited() {
    for (int y = 0; y < this->height; ++y) {
        for (int x = 0; x < this->width; ++x) {
            this->visitedFields[y][x]->visited = false;
            this->visitedFields[y][x]->distance = 0;
        }
    }
}

void Engine::printNeighbors() {
    printf("\nPRINTING NEIGHBORS!\n");
    for (int i = 0; i < adjacencyList.bucketCount; ++i) {
        if (adjacencyList.buckets[i].filled) {
            CityLinkedList cll = adjacencyList.buckets[i].cityLinkedList;
            cll.print();
        }
    }
}

void Engine::getAtKey(CustomString key) {
    CityLinkedList *foundIndex = adjacencyList[key];
    printf("FOUND CITY: %s\n", foundIndex->head->name.c_str());
}

void Engine::getFlights() {
    int flightsNum;
    std::cin >> flightsNum;

    for (int i = 0; i < flightsNum; ++i) {
        CustomString start;
        CustomString dest;
        int time;

        std::cin >> start >> dest >> time;

        // Push to the adjacency list
        adjacencyList[start]->append(new CityNode(dest, time));
    }

//    printf("NUMBER OF FLiGHTS: %d\n", flightsNum);
}


void Engine::dijkstra(CustomString start, CustomString dest, int type) {
    // Initialize empty vector of visited nodes
    CustomUnorderedMap visitedNodes;

    // Sort nodes




}

void Engine::sortNodes() {
    for (int i = 0; i < adjacencyList.bucketCount; ++i) {
        if (adjacencyList.buckets[i].filled) {

        }
    }
}

