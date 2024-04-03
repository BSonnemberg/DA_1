#include "utf8_ch.h"

/**
 * \brief Get pth byte of a utf8 code
 * <p> valid range for p: [0; 3]
 */
uint8_t utf8_ch::operator[](const int& p) const {
    if (p<0 || p>3) return UINT8_MAX;
    return bytes[p];
}

bool utf8_ch::is_ascii() const {
    return (bytes[0] >> 7) != 0b1;
}

utf8_ch::operator uint8_t() const { return bytes[0]; }
utf8_ch::operator char() const { return (char)bytes[0]; }

/**
 * \brief Get the first utf8 character found
 * in the internal pointer of the iterator
 */
utf8_ch utf8_ch::get_char(uint8_t* ptr) {

    utf8_ch result;
    uint8_t* copyPtr = ptr;
    uint8_t& ch = *copyPtr;

    // get first byte
    result.bytes[0] = ch;
    copyPtr++;

    if ((ch >> 7) == 0b1) {
        // non-ascii, multibyte
        for (int i=0; i<3; i++) {
            ch = *copyPtr;
            if ((ch >> 6) == 0b10) {
                result.bytes[i+1] = ch;
                copyPtr++;
            } else break;
        }
    }
    return result;
}

std::ostream& operator<<(std::ostream& os, const utf8_ch& ch) {
    for (int i=0; i<ch.size(); i++) std::cout << ch.bytes[i];
    return os;
}

bool utf8_ch::operator==(const utf8_ch &other) const {
    for (int i=0; i<4; i++) {
        if (bytes[i] != other.bytes[i]) return false;
    }
    return true;
}

// get size (no. of bytes) of a utf8_ch
size_t utf8_ch::size() const {
    size_t result = 0;
    for (uint8_t byte : bytes) {
        if (byte==0) break;
        result++;
    }
    return result;
}
