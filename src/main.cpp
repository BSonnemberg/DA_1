#include "DataLoader.h"
#include "DataHandler.h"
#include "menu/DatasetMenu.h"

int main() {

    DatasetMenu menu;
    menu.open();

    Graph g;
    if (!DataLoader::loadToGraph(g, "../dataset-large/")) {
        printf("Error loading dataset!");
        return 1;
    }
    return 0;
}
