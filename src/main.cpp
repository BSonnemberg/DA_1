#include "DataLoader.h"
#include "DataHandler.h"

#include "menu/Menu.h"

int main() {
    Graph g;

    // Menu::openDatasetMenu();


    if (!DataLoader::loadToGraph(g, "../dataset-large/")) {
        printf("Error loading dataset!");
        return 1;
    }

    // Menu::openMainMenu(g);

    Vertex* v1 = g.findVertex("R_18");
    // Vertex* v2 = g.findVertex("PS_6");
    // Edge* e = nullptr;
    //
    // for (Edge* e_ : v1->getOutEdges()) {
    //     if (e_->getDest() == v2) {
    //         e = e_;
    //         break;
    //     }
    // }
    //
    // menu.openPipeRemovalMenu(g, e);

Menu::openNodeRemovalMenu(g, v1);


    // pritf("Dataset loaded!\n");
    // printf("Max flow > %d\n", DataHandler::edmondsKarp(g));
    return 0;
}