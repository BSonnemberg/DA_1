#ifndef RESERVOIR_H
#define RESERVOIR_H

#include "NodeInfo.h"

class Reservoir : public NodeInfo {
    std::string name;
    std::string municipality;
    int maxDelivery; // m^3 / sec
public:
    Reservoir(const int& id,
              const std::string& code,
              const std::string& name,
              const std::string& municipality,
              const int& maxDelivery);
    std::string getName() const;
    std::string getMunicipality() const;
    int getMaxDelivery() const;
};

#endif
