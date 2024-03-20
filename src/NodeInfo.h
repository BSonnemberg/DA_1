#ifndef NODEINFO_H
#define NODEINFO_H

#include <memory>
#include <string>

enum NodeType {
    WATER_RESERVOIR,
    PUMPING_STATION,
    DELIVERY_SITE
};

class NodeInfo {
    // the id is not unique to the node, but
    // rather unique to the underlying subclass
    int id;
    std::string code;
public:
    NodeInfo(const int& id, const std::string& code);
    int getId() const;
    NodeType getType() const;
    std::string getCode() const;
    bool operator==(const NodeInfo& i) const;
};

#endif
