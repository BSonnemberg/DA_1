#include "DataLoader.h"
#include "DataHandler.h"

int main() {
    Graph g;
    if (!DataLoader::loadToGraph(g, "../dataset-small/")) {
        printf("Error loading dataset!");
        return 1;
    }
    printf("Loaded dataset!");

    City* m = new City(0, "abc", " ", 0, 0);
    City* m2 = new City(0, "def", " ", 0, 0);
    g.addVertex(m);
    g.addVertex(m2);
    for (auto v: g.getNodes()) {
        if(v->getInfo()->getType() == WATER_RESERVOIR) {
            g.addEdge(m->getCode(),v->getInfo()->getCode(), INT_MAX);
        }
        if(v->getInfo()->getType() == DELIVERY_SITE) {
            g.addEdge(v->getInfo()->getCode(),m2->getCode(), INT_MAX);
        }
    }
    DataHandler::findAugmPath(g, g.findVertex(m->getCode()), g.findVertex(m2->getCode()));
    return 0;
}
