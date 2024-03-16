#include "City.h"

City::City(const int& id, const std::string& code, const std::string& name, const int& demand, const int& population) {
    this->id = id;
    this->code = code;
    this->name = name;
    this->demand = demand;
    this->population = population;
}

int City::getId() const {
    return this->id;
}

std::string City::getCode() const {
    return this->code;
}

std::string City::getName() const {
    return this->name;
}

int City::getDemand() const {
    return this->demand;
}

int City::getPopulation() const {
    return this->population;
}