#ifndef MENU_H
#define MENU_H

#include "utils/textbox.h"

class Menu {
public:
    virtual ~Menu() = default;
    virtual int open() { return 0; }
};

#endif
