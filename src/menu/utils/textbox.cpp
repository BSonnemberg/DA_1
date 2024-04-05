#include "textbox.h"

textbox::textbox(const int& x, const int& y, const int& size, const std::string& text_a, const std::string& text_b, const std::string& color) {
    this->x = x;
    this->y = y;
    this->size = size;
    this->text_a = text_a;
    this->text_b = text_b;
    this->color = color;
}

/**
 * Let the text box take over and redirect
 * user input to it; returns when finished
 */
result textbox::take_over() {

    this->show_text(text_b);
    result res{};
    char c;

    while (c != '\x1B' && c != '\n') {
        scan >> c;
        switch (c) {
            case '\b':
            case 127:
                // backspace
                if (!input.empty()) {
                    input.pop_back();
                }
                break;
            case '\n':
                // pressed ENTER
                if (!input.empty()) {
                    res = {true, input};
                    break;
                }
            case '\x1B':
                // pressed ESC
                res = {false, ""};
                break;
            default:
                if (c != ' ' && c != '\t') {
                    input += c;
                }
        }
        this->show();
    }
    input.clear();
    this->show();
    return res;
}

void textbox::clear() const {
    set_cursor(x, y);
    print << RESET << std::string(size, ' ');
}

void textbox::show() const {
    if (input.empty()) {
        this->show_text(text_a);
    }
    else {
        this->show_input();
    }
}

void textbox::show_input() const {

    this->clear();
    print << color;

    show_cursor();
    set_cursor(x, y);

    // fill box using space
    print << " > ";
    print << std::string(size-6, ' ');
    print << " < ";

    set_cursor(x+4, y);
    const int n = (int)input.length();
    const int p = size - n - 6;

    if (p >= 0) {
        print << input;
    }
    else {
        print << input.substr(-p, n+p);
    }
    print << RESET;
}

void textbox::show_text(const std::string& txt, const bool& center) const {

    this->clear();
    hide_cursor();
    set_cursor(x, y);

    // fill box with spaces
    print << color;
    print << std::string(size, ' ');

    const int n = (int)txt.length();
    const int p = size - n - 2;

    // now add the text
    if (p < 0) {
        set_cursor(x+1, y);
        print << txt.substr(0, n+p);
    }
    else {
        if (center) {
            // center text
            double mid = (x + x + size) / 2.0;
            set_cursor(mid - n/2, y);
        }
        else {
            set_cursor(x+1, y);
        }
        print << txt;
    }
    print << RESET;
}

void textbox::resize(const int &newSize) {
    this->size = newSize;
}
