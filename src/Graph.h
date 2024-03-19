#ifndef GRAPH_H
#define GRAPH_H

#include "Vertex.h"

class Graph {
    std::vector<Vertex*> nodes;
    friend class DataHandler;
public:
    ~Graph();
    Graph() = default;
    Graph(const Graph& g);
    const std::vector<Vertex*>& getNodes() const;
    Vertex* addVertex(const NodeInfo& info);
    bool removeVertex(const NodeInfo& info);
    // find vertex based on the code of its NodeInfo
    Vertex* findVertex(const std::string& code) const;
    Vertex* findVertex(const NodeInfo& info) const;
    bool addEdge(const NodeInfo& i1, const NodeInfo& i2, const int& cap);
};

#endif
