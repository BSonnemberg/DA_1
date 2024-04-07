#ifndef MENU_H
#define MENU_H

#include "../DataHandler.h"
#include "utils/termutils.h"

class Menu {
public:
    int open();
    int open2(Graph& g);
    int open3(Graph& g);
    int open4(Graph& g, Edge* e);
};

#endif
