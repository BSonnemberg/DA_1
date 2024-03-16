#ifndef GRAPH_H
#define GRAPH_H

#include "Vertex.h"

class Graph {
    std::vector<Vertex*> nodes;
public:
    ~Graph();
    Vertex* findVertex(const NodeInfo& info) const;
    bool addVertex(const NodeInfo& info);
    bool removeVertex(const NodeInfo& info);
};

#endif
