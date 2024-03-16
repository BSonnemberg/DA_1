#ifndef VERTEX_H
#define VERTEX_H

#include "NodeInfo.h"
#include "Edge.h"
#include <vector>

class Edge;

class Vertex {
    NodeInfo info;
    std::vector<Edge> adj;
    //...
    bool removeEdgeTo(Vertex* v);
    friend class Graph;
public:
    explicit Vertex(NodeInfo info);
    const std::vector<Edge>& getAdj() const;
    NodeInfo getInfo() const;
};

#endif
