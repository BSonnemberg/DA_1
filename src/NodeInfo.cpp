#include "NodeInfo.h"

NodeInfo::NodeInfo(const int &id, const std::string &code, const NodeType& type) {
    this->id = id;
    this->code = code;
    this->type = type;
}

int NodeInfo::getId() const {
    return this->id;
}

std::string NodeInfo::getCode() const {
    return this->code;
}

NodeType NodeInfo::getType() const {
    return this->type;
}