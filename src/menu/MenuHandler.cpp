#include <queue>
#include "DatasetMenu.h"

constexpr int size = 1;
const Menu menus[size] = {
    //...
};

void open(const int& menuId) {
    if (menuId < 0 || menuId > size-1) {
        throw std::invalid_argument("invalid menu id");
    }
    int nextId = menuId;
    while (nextId != -1) {
        clear();
        Menu next = menus[nextId];
        nextId = next.open();
    }
}