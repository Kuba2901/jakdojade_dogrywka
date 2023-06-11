#include "engine.h"
#include "custom_string.h"

int main()
{
    Engine *engine = new Engine();

    engine->getMap();
    engine->findCities();
    engine->createAdjacencyMatrix();
    engine->getFlights();
//    engine->printNeighbors();
    engine->getQueries();
    engine->printNeighbors();

    return 0;
}