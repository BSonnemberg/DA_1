#ifndef VERTEX_H
#define VERTEX_H

#include "NodeInfo.h"
#include "Edge.h"
#include <vector>

class Edge;

class Vertex {
    NodeInfo info;
    // outgoing edges
    std::vector<Edge> adj;
    //...
public:
    explicit Vertex(NodeInfo info);
    const std::vector<Edge>& getAdj() const;
};

#endif
