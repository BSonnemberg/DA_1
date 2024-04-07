#include "DataLoader.h"
#include "DataHandler.h"

int main() {
    Graph g;
    if (!DataLoader::loadToGraph(g, BASE_PATH + "dataset-small/")) {
        printf("Error loading dataset!");
        return 1;
    }
    printf("Dataset loaded!\n");
    printf("Max flow > %d\n", DataHandler::edmondsKarp(g));
    DataHandler::printToFile(g);
    printf("Logs file created!");
    return 0;
}