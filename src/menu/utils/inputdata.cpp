#include "inputdata.h"

input_data::input_data() {
    buffer = nullptr;
    buffer_size = 0;
}

input_data::~input_data() {
    // dealloc mem
    free(buffer);
}

// convert buffer to string
std::string input_data::to_string() const {
    return {buffer, buffer+buffer_size};
}

input_data::iterator input_data::begin() const {
    return iterator(buffer);
}

input_data::iterator input_data::end() const {
    return iterator(buffer+buffer_size);
}
