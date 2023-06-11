#include "engine.h"
#include "custom_string.h"

int main()
{
    Engine *engine = new Engine();

    engine->getMap();
    engine->findCities();
    engine->printCities();
    engine->createAdjacencyMatrix();
    engine->getFlights();
    engine->getQueries();
    engine->printNeighbors();

    printf("HASHES!\n");
    int hash_ABO = JakDojadeString{"AAQ"}.toHash();
    int hash_AC0 = JakDojadeString{"AB0"}.toHash();

    printf("%d - %d\n", hash_ABO, hash_AC0);

    return 0;
}