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
    Reservoir(int id, std::string code, std::string name, std::string municipality, int maxDelivery);
    std::string getCode();
    std::string getName();
    int getId();
};

#endif
