#include "DataLoader.h"
#include "DataHandler.h"

int main() {
    Graph g;
    if (!DataLoader::loadToGraph(g, "../dataset-small/")) {
        printf("Error loading dataset!");
        return 1;
    }
    printf("Loaded dataset!\n");
    printf("Achieved max flow of > %d\n", DataHandler::edmondsKarp(g));
    return 0;
}
