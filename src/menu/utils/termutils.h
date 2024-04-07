#ifndef TERMUTILS_H
#define TERMUTILS_H

#include "scannable.h"
#include "printable.h"
#include "color.h"

/**
 * "Clear" the terminal screen
 * (more of a fake clear)
 */
void clear();

/**
 * Hide the cursor from the terminal
 */
void hide_cursor();

/**
 * Show the cursor inside the terminal
 */
void show_cursor();

/**
 * Set cursor position on the terminal
 * @param x x coordinate
 * @param y y coordinate
 */
void set_cursor(const int &x, const int &y);

/**
 * Print n empty lines
 * @param n number of lines
 */
void empty_line(const int& n);

#endif
