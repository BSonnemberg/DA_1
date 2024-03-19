#include "NodeInfo.h"

NodeInfo::NodeInfo(const int &id, const std::string &code) {
    this->id = id;
    this->code = code;
}

int NodeInfo::getId() const {
    return this->id;
}

std::string NodeInfo::getCode() const {
    return this->code;
}

NodeType NodeInfo::getType() const {
    if (code[0] == 'S') return PUMPING_STATION;
    if (code[0] == 'R') return WATER_RESERVOIR;
    return DELIVERY_SITE;
}

bool NodeInfo::operator==(const NodeInfo &i) const {
    return this->code == i.code;
}
