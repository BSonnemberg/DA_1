#pragma once

#include "termutils.h"
#include <string>

struct result {
    bool success;
    std::string input;
};

class textbox {
    int x;
    int y;
    int size;
    std::string color;
    std::string input;
    void show_input() const;
public:
    textbox(const int& x,
            const int& y,
            const int& size,
            const std::string& text_a,
            const std::string& text_b,
            const std::string& color = FGROUND(238) + BGROUND(248));
    std::string text_a;
    std::string text_b;
    result take_over();
    void resize(const int& newSize);
    void clear() const;
    void show() const;
    /**
     * Display text inside the text box
     * @param txt text to be displayed
     * @param center whether to center text
     */
    void show_text(const std::string& txt, const bool& center = true) const;
};
