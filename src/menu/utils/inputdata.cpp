#include "inputdata.h"

input_data::input_data() {
    buffer = nullptr;
    buffer_size = 0;
    keyboard_state = 0b0;
}

input_data::~input_data() {
    // dealloc mem
    free(buffer);
}

/**
 * \brief Check if a keyboard modifier was
 * being pressed down when input was captured
 *
 * \param mod modifier to check for
 * \return whether it was pressed
 */
bool input_data::has_modifier(const uint8_t &mod) const {
    return (keyboard_state & mod) != 0;
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
