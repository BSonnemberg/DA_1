#include "DataLoader.h"
#include "DataHandler.h"

#include "menu/Menu.h"

int main() {
    Graph g;
    std::string dataset;
    Menu::openDatasetMenu(g, dataset);


    if (!DataLoader::loadToGraph(g, "../"+dataset+"/")) {
        printf("Error loading dataset!");
        return 1;
    }

    Menu::openMainMenu(g);

    return 0;
}