#include "City.h"

City::City(const int& id, const std::string& code, const std::string& name, const int& demand, const int& pop) : NodeInfo(id, code, DELIVERY_SITE) {
    this->name = name;
    this->demand = demand;
    this->population = pop;
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