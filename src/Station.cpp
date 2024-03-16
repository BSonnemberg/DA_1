#include "Station.h"

Station::Station(const int& id, const std::string& code) {
    this->id = id;
    this->code = code;
}

int Station::getId() const {
    return this->id;
}

std::string Station::getCode() const {
    return this->code;
}
