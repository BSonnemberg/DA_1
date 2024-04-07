#include "DataLoader.h"
#include "DataHandler.h"

#include "menu/Menu.h"

int main() {
    Graph g;

    Menu menu;
    // int a = menu.open();

    if (!DataLoader::loadToGraph(g, "../dataset-large/")) {
        printf("Error loading dataset!");
        return 1;
    }

    // DataHandler::edmondsKarp(g);

    Vertex* v1 = g.findVertex("R_MASTER");
    Vertex* v2 = g.findVertex("R_17");
    Edge* e = nullptr;

    for (Edge* e_ : v1->getOutEdges()) {
        if (e_->getDest() == v2) {
            e = e_;
            break;
        }
    }
    //
    menu.open4(g,e);
    // pritf("Dataset loaded!\n");
    // printf("Max flow > %d\n", DataHandler::edmondsKarp(g));
    return 0;
}