#include "Reservoir.h"

Reservoir::Reservoir(const int& id, const std::string& code, const std::string& name, const std::string& munic, const int& maxDelivery) : NodeInfo(id, code) {
    this->name = name;
    this->municipality = munic;
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
