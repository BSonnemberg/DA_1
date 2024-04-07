#include "termutils.h"
#include <cstdio>

void clear() {
#ifdef WIN32
    empty_line(100);
#else
    printf("\x1B[2J");
#endif
}

void hide_cursor() {
#ifndef WIN32
    printf("\x1B[?25l");
#endif
}

void show_cursor() {
#ifndef WIN32
    printf("\x1B[?25h");
#endif
}

void set_cursor(const int &x, const int &y) {
#ifndef WIN32
    printf("\x1B[%d;%df", y, x);
#endif
}

void empty_line(const int &n) {
    for (int i=0; i<n; i++) {
        printf("\n");
    }
}
