#include "scannable.h"
#include <unistd.h>

scannable scan;

const scannable& scannable::operator>>(uint8_t& ch) const {
    read(STDOUT_FILENO, &ch, 1);
    return *this;
}

const scannable& scannable::operator>>(char& ch) const {
    read(STDOUT_FILENO, &ch, 1);
    return *this;
}

const scannable& scannable::operator>>(int& ch) const {
    read(STDIN_FILENO, &ch, 1);
    return *this;
}
