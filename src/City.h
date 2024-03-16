#ifndef CITY_H
#define CITY_H

#include "NodeInfo.h"

// a.k.a. delivery sites
class City : public NodeInfo {
    int demand;
    int population;
    std::string name;
public:
    City(const int& id,
         const std::string& code,
         const std::string& name,
         const int& demand,
         const int& population);
    std::string getName() const;
    int getDemand() const;
    int getPopulation() const;
};

#endif
