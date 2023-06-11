#include "engine.h"
#include "custom_string.h"

int main()
{
    Engine *engine = new Engine();

    engine->getMap();
    engine->findCities();

//    engine->printCities();

    engine->createAdjacencyMatrix();
//    engine->printNeighbors();
    engine->getFlights();
    engine->getQueries();

    return 0;
}