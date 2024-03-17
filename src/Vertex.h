#ifndef VERTEX_H
#define VERTEX_H

#include <vector>
#include "Edge.h"

#include "Station.h"
#include "Reservoir.h"
#include "City.h"

class Edge;

class Vertex {
    NodeInfo info;
    std::vector<Edge> adj;
    bool visited = false;
    //...
    void addEdgeTo(Vertex* v, float cap);
    bool removeEdgeTo(Vertex* v);
    friend class Graph;
    friend class DataHandler;
public:
    explicit Vertex(NodeInfo info);
    const std::vector<Edge>& getAdj() const;
    NodeInfo getInfo() const;
};

#endif
