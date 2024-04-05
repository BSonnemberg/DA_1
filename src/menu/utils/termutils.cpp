#include "termutils.h"

#include <cstdio>
#include <unistd.h>
#include <termios.h>

void raw() {
    termios tio{};
    tcgetattr(STDIN_FILENO, &tio);
    tio.c_lflag &= (~ICANON & ~ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &tio);
}

void cooked() {
    termios tio{};
    tcgetattr(STDIN_FILENO, &tio);
    tio.c_lflag &= (ICANON & ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &tio);
}

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
