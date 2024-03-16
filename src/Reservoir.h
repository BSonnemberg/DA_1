#ifndef RESERVOIR_H
#define RESERVOIR_H

#include <string>

class Reservoir {
    int id;
    std::string code;
    std::string name;
    std::string municipality;
    int maxDelivery; // m^3 / sec
public:
    Reservoir(const int& id,
              const std::string& code,
              const std::string& name,
              const std::string& municipality,
              const int& maxDelivery);
    std::string getCode() const;
    std::string getName() const;
    std::string getMunicipality() const;
    int getMaxDelivery() const;
    int getId() const;
};

#endif
