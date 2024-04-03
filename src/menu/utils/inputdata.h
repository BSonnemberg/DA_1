#pragma once
#include "utf8_ch.h"
#include <string>

/**
 * \brief Houses input data after scanning from stdin,
 * along with some extra keyboard metadata
 */
class input_data {
    uint8_t* buffer;
    int buffer_size;
    friend class scannable;
public:
    using value_type = utf8_ch;
    using reference = const value_type&;
    using pointer = value_type*;
    /**
     * \brief An iterator implementation
     * for the input_data class
     */
    class iterator {
        utf8_ch current; // current element
        uint8_t* ptr; // next element
    public:
        iterator(uint8_t* ptr);
        reference operator*();
        pointer operator->();
        iterator& operator++();
        iterator operator++(int);
        bool operator==(const iterator& other) const;
        bool operator!=(const iterator& other) const;
    };
    iterator begin() const;
    iterator end() const;
public:
    input_data();
    ~input_data();
    std::string to_string() const;
};
