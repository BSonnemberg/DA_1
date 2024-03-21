#include "DataLoader.h"
#include "DataHandler.h"

int main() {
    Graph g;
    if (!DataLoader::loadToGraph(g, "../dataset-large/")) {
        printf("Error loading dataset!");
        return 1;
    }
    printf("Loaded dataset!\n");
    printf("Max flow > %d\n\n", DataHandler::edmondsKarp(g));
    for (City* c : DataHandler::undersuppliedCities(g)) {
        printf("> %s is undersupplied!\n", c->getName().c_str());
    }
    return 0;
}
