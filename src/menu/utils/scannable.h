#pragma once
#include "inputdata.h"

class scannable {
    static int buffer_limit;
public:
    static void limit(const int& n);
    scannable& operator>>(input_data& in);
    scannable& operator>>(std::string& str);
    scannable& operator>>(uint8_t& ch);
    scannable& operator>>(char& ch);
    scannable& operator>>(int& ch);
};
