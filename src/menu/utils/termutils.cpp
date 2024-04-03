#include "termutils.h"

#include <unistd.h>
#include <termios.h>

void raw() {
    termios tio{};
    tcgetattr(STDIN_FILENO, &tio);
    tio.c_lflag &= (~ICANON & ~ECHO); // enable raw mode
    tcsetattr(STDIN_FILENO, TCSANOW, &tio);
}

void cooked() {
    termios tio{};
    tcgetattr(STDIN_FILENO, &tio);
    tio.c_lflag &= (ICANON & ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &tio);
}

// "clear" screen
void clear() {
    printf("\x1B[2J");
}

void hideCursor() {
    printf("\x1B[?25l");
}

void showCursor() {
    printf("\x1B[?25h");
}

void setCursor(const int &x, const int &y) {
    printf("\x1B[%d;%df", x, y);
}

