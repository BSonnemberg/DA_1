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
    if (code[0] == 'R') return WATER_RESERVOIR;
    if (code[0] == 'C') return DELIVERY_SITE;
    return PUMPING_STATION;
}

bool NodeInfo::operator==(const NodeInfo &i) const {
    return this->code == i.code;
}
