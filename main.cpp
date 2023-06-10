#include "engine.h"
#include "custom_string.h"

int main()
{
    Engine *engine = new Engine();

    engine->getMap();
    engine->getFlights();
    engine->findCities();
    engine->createAdjacencyMatrix();
    engine->printNeighbors();

    return 0;
}