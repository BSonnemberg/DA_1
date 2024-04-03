#include "scannable.h"
#include <unistd.h>

#define REALLOC_THRESHOLD 0.7
int scannable::buffer_limit = 128;

/**
 * \note By default, the max size for a buffer is 128 chars,
 * the rest is discarded. to change this, use the limit() func.
 */
scannable& scannable::operator>>(input_data& in) {

    // read input from stdin
    in.buffer = (uint8_t*)malloc(buffer_limit);
    ssize_t bytes_read = read(STDIN_FILENO, in.buffer, buffer_limit);

    if (bytes_read <= 0) {
        perror("Error reading user input from stdin");
        return *this;
    }

    in.keyboard_state = request_kbstate();
    in.buffer_size = bytes_read;

    if (bytes_read < REALLOC_THRESHOLD*buffer_limit) {
        // shrink dynamic mem. allocated
        auto* trimmed = (uint8_t*)realloc(in.buffer,bytes_read);
        if (trimmed != nullptr) in.buffer = trimmed;
    }

    if (bytes_read > buffer_limit) {
        // similar to std::cin.ignore()
        scanf("%*s");
    }
    return *this;
}

scannable &scannable::operator>>(std::string& str) {
    input_data in;
    (*this) >> in;
    str = in.to_string();
    return *this;
}

scannable &scannable::operator>>(uint8_t& ch) {
    read(STDIN_FILENO, &ch, 1);
    return *this;
}

scannable &scannable::operator>>(char& ch) {
    read(STDIN_FILENO, &ch, 1);
    return *this;
}

scannable &scannable::operator>>(int &ch) {
    read(STDIN_FILENO, &ch, 1);
    return *this;
}

// set new limit for the max buffer size
void scannable::limit(int n) { buffer_limit = n; }
