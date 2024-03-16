#ifndef STATION_H
#define STATION_H

#include <string>

class Station {
    int id;
    std::string code;
public:
    Station(const int& id, const std::string& code);
    int getId() const;
    std::string getCode() const;
};

#endif
