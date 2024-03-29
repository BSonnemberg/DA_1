#include "DataLoader.h"
#include "DataHandler.h"

int main() {
    Graph g;
    if (!DataLoader::loadToGraph(g, "../dataset-large/")) {
        printf("Error loading dataset!");
        return 1;
    }
    printf("Loaded dataset!\n");
    printf("Max flow > %d\n", DataHandler::edmondsKarp(g));
    return 0;
}
