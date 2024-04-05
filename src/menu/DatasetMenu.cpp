#include "DatasetMenu.h"

int DatasetMenu::open() {

    clear();
    set_cursor(0,0);
    empty_line(2);

    print << "   ";
    // todo: check utf8 windows terminal compatibility
    print << "🌊";

    print << GRAY;
    print << " Welcome to " << BOLD << "water supply analysis";
    print << RESET << GRAY "!" << newl;
    print << "   Which dataset would you like to load?" << newl << newl;

    if (selectedItem == 0) {
        small.resize(22);
        small.show_text(small.text_b, false);
    } else {
        small.resize(20);
        small.show_text(small.text_a, false);
    }
    large.show_text(large.text_a, false);
    other.show_text(other.text_a, false);

    empty_line(3);

    return 0;
}
