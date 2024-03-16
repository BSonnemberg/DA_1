#include "Station.h"

Station::Station(int id, std::string code) {
    this->id = id;
    this->code = code;
}

int Station::getId() {
    return this->id;
}

std::string Station::getCode() {
    return this->code;
}
