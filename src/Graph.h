#ifndef GRAPH_H
#define GRAPH_H

#include "Edge.h"

class Graph {
    std::vector<Vertex*> nodes;
public:
    Graph();
    ~Graph();
    const std::vector<Vertex*>& getNodes() const;
    Vertex* addVertex(NodeInfo* info);
    bool removeVertex(const NodeInfo& info);
    Vertex* findVertex(const std::string& code) const;
    Vertex* findVertex(const NodeInfo& info) const;
    bool addEdge(const std::string& c1, const std::string& c2, const int& cap) const;
};

#endif
