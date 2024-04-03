#pragma once
#include <iostream>

/**
 * \brief printable class enables output using <<
   and supports all types that std::cout does
 */
class printable {
public:
    // must be implemented inside the header
    // file to avoid template errors
    template <typename T>
    printable& operator<<(const T& out) {
        std::cout << out;
        return *this;
    }
};
