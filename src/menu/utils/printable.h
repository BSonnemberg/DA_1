#ifndef PRINTABLE_H
#define PRINTABLE_H

#include <iostream>

class printable {
public:
    template <typename T>
    printable& operator<<(const T& out) {
        std::cout << out;
        fflush(stdout);
        return *this;
    }
};

// used for print <<
extern printable print;
extern const char newl;

#endif
