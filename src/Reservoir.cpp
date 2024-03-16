#include "Reservoir.h"

Reservoir::Reservoir(const int& id, const std::string& code, const std::string& name, const std::string& municipality, const int& maxDelivery)
: NodeInfo(id, code, WATER_RESERVOIR) {
    this->name = name;
    this->municipality = municipality;
    this->maxDelivery = maxDelivery;
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
