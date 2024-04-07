#ifndef MENU_H
#define MENU_H

#include "../DataHandler.h"
#include "utils/termutils.h"

class Menu {
public:
    static void openDatasetMenu();
    static void openMainMenu(Graph& g);
    static void openFlowMenu(Graph& g);
    static void openBalanceMenu(Graph& g);
    static void openPipeRemovalMenu(Graph& g, Edge* e);
    static void openNodeRemovalMenu(Graph& g, Vertex* v);
};

#endif
