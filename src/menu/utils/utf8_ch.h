#pragma once
#include <iostream>

// represents a single ascii char
typedef unsigned char uint8_t;

/**
 * \brief Represents a utf-8 character
 * <p> A utf8 char can take up to 4 bytes
 */
class utf8_ch {
    uint8_t bytes[4] = {0};
    static utf8_ch get_char(uint8_t *ptr);
    friend class input_data;
    friend class scannable;
public:
    size_t size() const;
    bool is_ascii() const;
    operator char() const;
    operator uint8_t() const;
public:
    const uint8_t& operator[](int p) const;
    bool operator==(const utf8_ch& other) const;
    friend std::ostream& operator<<(std::ostream& os, const utf8_ch& ch);
};