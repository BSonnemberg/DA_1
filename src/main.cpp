#include "DataLoader.h"
#include "DataHandler.h"

int main() {
    Graph g;
    if (!DataLoader::loadToGraph(g, basePath+"./dataset-small")) {
        printf("Error loading dataset!");
        return 1;
    }
    printf("Dataset loaded!\n");
    return 0;
}