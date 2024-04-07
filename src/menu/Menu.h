#ifndef MENU_H
#define MENU_H

#include "../DataHandler.h"
#include "utils/termutils.h"

class Menu {
public:
    static int openDatasetMenu();
    static int openFlowMenu(Graph& g);
    static int openBalanceMenu(Graph& g);
    static int openPipeRemovalMenu(Graph& g, Edge* e);
    static int openNodeRemovalMenu(Graph& g, Vertex* v);
};

#endif
