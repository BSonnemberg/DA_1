#include "DataLoader.h"

int main() {
    Graph g;
    DataLoader::loadToGraph(g, "../dataset-large/");
    return 0;
}