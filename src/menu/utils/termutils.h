#ifndef TERMUTILS_H
#define TERMUTILS_H

#include "scannable.h"
#include "printable.h"
#include "color.h"

/**
 * Enable terminal raw mode, where characters
 * are processed one at a time as they're typed
 */
void raw();

/**
 * Enable terminal cooked mode, where the buffer
 * is processed only when a '\n' char is typed
 */
void cooked();

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

#endif
