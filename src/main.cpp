#include "DataLoader.h"
#include "DataHandler.h"

int main() {
    Graph g;
    if (!DataLoader::loadToGraph(g, "../dataset-large/")) {
        printf("Error loading dataset!");
        return 1;
    }
    printf("Loaded dataset!\n");
    printf("Original max flow > %d\n", DataHandler::edmondsKarp(g));

    Graph g2(g);
    g.removeVertex(NodeInfo(6, "R_6"));

    printf("Max flow after removal > %d\n", DataHandler::edmondsKarp(g));
    printf("Max flow after removal of copy > %d\n", 24163-DataHandler::removeNodeCascade(g2, g2.findVertex("R_6")));
    printf("Max flow after removal > %d\n", DataHandler::edmondsKarp(g2, false));
    return 0;
}
