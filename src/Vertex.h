#ifndef VERTEX_H
#define VERTEX_H

#include <vector>
#include "Edge.h"

#include "Station.h"
#include "Reservoir.h"
#include "City.h"

class Edge;

class Vertex {
    NodeInfo* info;
    std::vector<Edge> adj;
    Edge* path = nullptr;
    int bottleneck;
    //...
    void addEdgeTo(Vertex* v, const int& cap);
    bool removeEdgeTo(const Vertex* v);
    friend class Graph;
    friend class DataLoader;
    friend class DataHandler;
public:
    ~Vertex();
    explicit Vertex(const NodeInfo& info);
    const std::vector<Edge>& getAdj() const;
    NodeInfo* getInfo() const;
};

#endif
