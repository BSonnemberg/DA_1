#ifndef STATION_H
#define STATION_H

#include "NodeInfo.h"

class Station : public NodeInfo {
public:
    Station(const int& id, const std::string& code) : NodeInfo(id, code) {}
};

#endif
