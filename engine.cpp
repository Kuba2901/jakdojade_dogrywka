#include "engine.h"

Engine::Engine()
{
}

void Engine::getMap()
{
    // Getting map dimensions
    int height_, width_;
    scanf("%d %d", &width_, &height_);
//    std::cin >> width_ >> height_;

    // Setting engine properties
    this->height = height_;
    this->width = width_;

    // Char buffer
    char c;

    // Getting the map
    for (size_t y = 0; y < height_; y++)
    {
        JakDojadeVector<Point *> row;
        for (size_t x = 0; x < width_; x++)
        {
            std::cin >> c;
            row.pushToVector(new Point(x, y, c));
        }

        this->map.pushToVector(row);
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
        JakDojadeString cityName;

        for (int x = 0; x < this->width; ++x) {
            Point *pt = this->map[y][x];

            // TODO: DOESNT ACCEPT NEXT TO RIGHT BORDER
            if (pt->c >= 65 && pt->c <= 90) {
                // Start counting if not already
                if (!nameFound) {
                    xBegin = x;
                    cityName.append(pt->c);
                } else {
                    cityName.append(pt->c);
                }

                nameFound = true;

                if (x + 1 == width) {
                    xEnd = x;

                    // Find the city exit
                    Point *exit = findCityExit(xBegin, xEnd, y);
                    this->cities.pushToVector(new City(cityName, exit));

                    cityName.clear();
                    xBegin = -1;
                    xEnd = -1;

                    nameFound = false;
                }
            } else {
                if (nameFound) {
                    xEnd = x;

                    // Find the city exit
                    Point *exit = findCityExit(xBegin, xEnd, y);
                    this->cities.pushToVector(new City(cityName, exit));

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
    for (int i = xBegin - 1; i <= xEnd; ++i) {
        Point *pt = new Point(i, y - 1, ' ');
        int ptX = pt->x;
        int ptY = pt->y;

        // Only proceed if the point is in bounds
        if (inBounds(pt)) {
            // Delete the test point
            delete pt;

            if (this->map[ptY][ptX]->c == '*') {
                return this->map[ptY][ptX];
            }
        }
    }

    // On the level of the name
    Point *before = new Point(xBegin - 1, y, ' ');
    Point *after = new Point(xEnd, y, ' ');

    if (inBounds(before)) {
        if (map[before->y][before->x]->c == '*') {
            int beforeY = before->y;
            int beforeX = before->x  ;

            // Deallocate memory
            delete before;

            // Return the right pt
            return map[beforeY][beforeX];
        }
    }
    if (inBounds(after)) {
        if (map[after->y][after->x]->c == '*') {
            int afterY = after->y;
            int afterX = after->x  ;

            // Deallocate memory
            delete after;

            // return found point
            return map[afterY][afterX];
        }
    }

    // Below the name
    for (int i = xBegin - 1; i <= xEnd; ++i) {
        Point *pt = new Point(i, y + 1, ' ');
        int ptX = pt->x;
        int ptY = pt->y;

        // Only proceed if the point is in bounds
        if (inBounds(pt)) {
            // Delete the test point
            delete pt;

            if (this->map[ptY][ptX]->c == '*') {
                return this->map[ptY][ptX];
            }
        }
    }

    return nullptr;
}

bool Engine::inBounds(Point* pt) {
    return (pt->x >= 0 && pt->x < this->width && pt->y >= 0 && pt->y < this->height);
}

void Engine::printCities() {
    for (int i = 0; i < this->cities.getSize(); ++i) {
        City *city = this->cities[i];
        Point *exit = city->point;
        printf("City: %s at (%d, %d)!\n", city->name.CStyle(), exit->x, exit->y);
    }
}

bool Engine::isTraversable(Point *pt) {
    return inBounds(pt) && (pt->c == '#' || pt->c == '*');
}



void Engine::createAdjacencyMatrix() {
    // Keep track of visited fields
    for (int y = 0; y < this->height; ++y) {
        JakDojadeVector<BFSPoint *> row;

        for (int x = 0; x < this->width; ++x) {
            row.pushToVector(new BFSPoint(this->map[y][x], 0, false));
        }

        visitedFields.pushToVector(row);
    }

    JakDojadeQueue<BFSPoint*> queue;

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
        queue.pushToQueue(visitedFields[firstCity->point->y][firstCity->point->x]);

        while (!queue.queueEmpty()) {
            // Check whether a city was encountered in the current move
            bool cityEncountered = false;

            // Dequeue a vertex from queue and print it
            BFSPoint *front = queue.getFront();
            queue.popFromTheQueue();

            if (front->point->c == '*' && !(front->point->x == firstCity->point->x && front->point->y == firstCity->point->y)) {
                City* city = findCity(front->point);

                if (city != nullptr) {
                    cityEncountered = true;
                    cityNeighbors->append(new CityNode(city->name, front->distance));
                }
            }

            if (!cityEncountered) {
                // Get current point's neighbors
                JakDojadeVector<BFSPoint *> neighbors = getNeighbors(front);

                for (int i = 0; i < neighbors.getSize(); ++i) {
                    // Get all adjacent vertices of the dequeued
                    if (!neighbors[i]->visited) {
                        neighbors[i]->visited = true;
                        queue.pushToQueue(neighbors[i]);
                    }
                }
            }

        }

        adjacencyList.insertList(cityNeighbors);
    }

    // Deallocate visited fields board
    for (int y = 0; y < this->height; ++y) {
        for (int x = 0; x < this->width; ++x) {
            delete visitedFields[y][x];
        }
    }
}

JakDojadeVector<BFSPoint *> Engine::getNeighbors(BFSPoint* origin) {
    JakDojadeVector<BFSPoint *> neighbors;

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
            neighbors.pushToVector(pt);
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


void Engine::getFlights() {
    int flightsNum;
    std::cin >> flightsNum;

    for (int i = 0; i < flightsNum; ++i) {
        JakDojadeString start, dest;
        int time;

        std::cin >> start >> dest >> time;

        // Push to the adjacency list
        adjacencyList[JakDojadeString{start}]->append(new CityNode(JakDojadeString{dest}, time));
    }

//    printf("NUMBER OF FLiGHTS: %d\n", flightsNum);
}


KVPair<int, KVPair<int, JakDojadeVector<int>>> Engine::dijkstra(JakDojadeString start, JakDojadeString dest, int type) {
    CustomPriorityQueue pq;
    JakDojadeVector<int> distances;
    JakDojadeVector<int> path;

    int bufferSize = this->adjacencyList.bucketCount;

    const int MAX = 10000000;

    int startIndex = start.toHash() % bufferSize;
    int destIndex = dest.toHash() % bufferSize;

//    printf("STARTING WITH: %d and ending at: %d\n", startIndex, destIndex);

    distances.resizeVector(this->adjacencyList.bucketCount);
    path.resizeVector(this->adjacencyList.bucketCount);

    for (int i = 0; i < bufferSize; ++i) {
        distances[i] = MAX;
        path.pushToVector(-1);
    }

    distances[startIndex] = 0;

    CustomPriorityQueue queue;
    queue.push(KVPair<int, int>{0, startIndex});

    while (!queue.empty()) {
        KVPair<int, int> temp = queue.top();

        // Get the index of current pair
        int tempIndex = temp.second;

        queue.pop();

        // Check whether the destination was reached
        if (tempIndex == destIndex) {
//            printf("DESTINATION REACHED\n");
            // Return the distance to the destination and the path nodes indexes
            return KVPair<int, KVPair<int, JakDojadeVector<int>>> {distances[tempIndex], KVPair<int, JakDojadeVector<int>> {tempIndex, path}};
        }

        if (distances[tempIndex] < temp.first) continue;

        // Get the current cities neighbors
        CityLinkedList *cll = &adjacencyList.buckets[tempIndex].cityLinkedList;

        // Pass the head (current city)
        CityNode *currentNode = cll->head->next;
//        printf("City Node: %s\n", currentNode->name.CStyle());

        // Search for neighbors
        while (currentNode != nullptr) {
            int neighborNodeIndex = currentNode->name.toHash() % this->adjacencyList.bucketCount;
            int neighborWeight = currentNode->weight;

            if (distances[tempIndex] != INF && distances[neighborNodeIndex] > distances[tempIndex] + neighborWeight) {
                distances[neighborNodeIndex] = distances[tempIndex]  + neighborWeight;
                path[neighborNodeIndex] = tempIndex;
//                printf("PUSHING CITY WITH INDEX: %d TO THE QUEUE!\n", neighborNodeIndex);
                queue.push(KVPair<int, int>{distances[neighborNodeIndex], neighborNodeIndex});
            }

            currentNode = currentNode->next;
        }
    }

    return KVPair<int, KVPair<int, JakDojadeVector<int>>>();

}


void Engine::printPath(KVPair<int, KVPair<int, JakDojadeVector<int>>> result) {
    JakDojadeVector<int> path = result.second.second;
    int counter = result.second.first;
    JakDojadeVector<JakDojadeString> newPath;
    while (counter != 0) {
        if (counter != result.second.first) {
            newPath.pushToVector(this->adjacencyList[counter]->head->name);
        }
        counter = result.second.second[counter];
    }
    for (int i = newPath.getSize() - 2; i >= 0; i--) {
        printf("%s ", newPath[i].CStyle());
    }
}

void Engine::getQueries() {
    int queriesCount;
    std::cin >> queriesCount;

    for (int i = 0; i < queriesCount; ++i) {
        JakDojadeString start, dest;
        int type;

        std::cin >> start >> dest >> type;

        KVPair<int, KVPair<int, JakDojadeVector<int>>> result = dijkstra(start, dest, type);

        printf("%d ", result.first);

        if (type == 1) printPath(result);

        printf("\n");
    }

}