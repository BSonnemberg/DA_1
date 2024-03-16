#ifndef STATION_H
#define STATION_H

#include <string>

class Station {
    int id;
    std::string code;
public:
    Station(int id, std::string code);
    int getId();
    std::string getCode();
};

#endif
