#include "DataLoader.h"

int main() {
    Graph g;
    if (!DataLoader::loadToGraph(g, "../dataset-large/")) {
        printf("Error loading dataset!");
        return 1;
    }
    printf("Loaded dataset!");
    return 0;
}