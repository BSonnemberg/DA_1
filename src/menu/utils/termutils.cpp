#include "termutils.h"
#include <cstdio>

void clear() {
    printf("\x1B[2J");
}

void hide_cursor() {
    printf("\x1B[?25l");
}

void show_cursor() {
    printf("\x1B[?25h");
}

void set_cursor(const int &x, const int &y) {
    printf("\x1B[%d;%df", y, x);
}

void empty_line(const int &n) {
    for (int i=0; i<n; i++) {
        printf("\n");
    }
}
