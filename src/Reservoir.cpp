#include "Reservoir.h"

Reservoir::Reservoir(const int& id, const std::string& code, const std::string& name, const std::string& municipality, const int& maxDelivery) {
    this->id = id;
    this->code = code;
    this->name = name;
    this->municipality = municipality;
    this->maxDelivery = maxDelivery;
}

int Reservoir::getId() const {
    return this->id;
}

std::string Reservoir::getCode() const {
    return this->code
}

std::string Reservoir::getName() const {
    return this->name;
}

std::string Reservoir::getMunicipality() const {
    return this->municipality;
}

int Reservoir::getMaxDelivery() const {
    return this->maxDelivery;
}
