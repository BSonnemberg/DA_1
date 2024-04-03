#pragma once

#include "scannable.h"
#include "printable.h"
#include "color.h"

// used for print <<
printable print;
char newl = '\n';

// used for scan >>
scannable scan;

/** manipulate terminal */

void raw();
void cooked();

/** manipulate screen */

void clear();

/** manipulate mouse */

void hideCursor();
void showCursor();
void setCursor(const int& x, const int& y);
