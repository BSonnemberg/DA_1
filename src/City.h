#ifndef CITY_H
#define CITY_H

#include <string>

class City {
    int id;
    int demand;
    int population;
    std::string code;
    std::string name;
public:
    City(const int& id,
         const std::string& code,
         const std::string& name,
         const int& demand,
         const int& population);
    int getId() const;
    std::string getCode() const;
    std::string getName() const;
    int getDemand() const;
    int getPopulation() const;
};

#endif
