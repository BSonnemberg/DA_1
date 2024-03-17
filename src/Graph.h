#ifndef GRAPH_H
#define GRAPH_H

#include "Vertex.h"

class Graph {
    std::vector<Vertex*> nodes;
public:
    ~Graph();
    Graph() = default;
    Graph(const Graph& g);
    bool addVertex(const NodeInfo& info);
    bool removeVertex(const NodeInfo& info);
    // find vertex based on the code of its NodeInfo
    Vertex* findVertex(const std::string& code) const;
    bool addEdge(const std::string& c1, const std::string& c2, float cap);
};

#endif
