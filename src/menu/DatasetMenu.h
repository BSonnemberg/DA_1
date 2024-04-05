#ifndef DATASETMENU_H
#define DATASETMENU_H

#include "Menu.h"

class DatasetMenu : public Menu {
    int selectedItem = 0;
    textbox small = textbox(4, 6, 20, "Load small dataset", "> Load small dataset");
    textbox large = textbox(4, 8, 20, "Load large dataset", "> Load large dataset");
    textbox other = textbox(4, 10, 25, "Load alernative dataset", "> Load alernative dataset");
public:
    int open() override;
};

#endif
