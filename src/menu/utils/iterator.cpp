#include "inputdata.h"

input_data::iterator::iterator(uint8_t* ptr) { this->ptr = ptr; }

// dereference operator
input_data::reference input_data::iterator::operator*() {
    if (current.size() == 0) {
        // not yet cached
        current = utf8_ch::get_char(ptr);
    }
    return current;
}

// member access/ arrow operator
input_data::pointer input_data::iterator::operator->() {
    if (current.size() == 0) current = utf8_ch::get_char(ptr);
    return &current;
}

// prefix increment operator
input_data::iterator& input_data::iterator::operator++() {
    size_t size = current.size();
    if (size == 0) {
        // hadn't yet been referenced
        size = utf8_ch::get_char(ptr).size();
    }
    ptr += size;
    current = utf8_ch();
    return *this;
}

// postfix increment operator
input_data::iterator input_data::iterator::operator++(int) {
    iterator oldState = *this;
    ++(*this);
    return oldState;
}

bool input_data::iterator::operator==(const iterator &other) const {
    return ptr == other.ptr;
}

bool input_data::iterator::operator!=(const iterator &other) const {
    return ptr != other.ptr;
}
