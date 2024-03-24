#ifndef GRAPH_H
#define GRAPH_H

#include "Edge.h"

class Graph {
    std::vector<Vertex*> nodes;
    friend class DataHandler;
public:
    ~Graph();
    Graph();
    Graph(const Graph& g);
    const std::vector<Vertex*>& getNodes() const;
    Vertex* addVertex(NodeInfo* info);
    bool removeVertex(const NodeInfo& info);
    // find vertex based on the code of its NodeInfo
    Vertex* findVertex(const std::string& code) const;
    Vertex* findVertex(const NodeInfo& info) const;
    bool addEdge(const std::string& c1, const std::string& c2, const int& cap);
};

#endif
