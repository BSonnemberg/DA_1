#ifndef VERTEX_H
#define VERTEX_H

#include <vector>

#include "Reservoir.h"
#include "Station.h"
#include "City.h"
#include "Edge.h"

class Edge;

class Vertex {
    NodeInfo* info;
    std::vector<Edge*> adj;
    Edge* path = nullptr;
    int bneck;
    //...
    void addEdgeTo(Vertex* v, const int& cap, const int& flow=0);
    bool removeEdgeTo(const Vertex* v);
    friend class Graph;
    friend class DataLoader;
    friend class DataHandler;
public:
    ~Vertex();
    explicit Vertex(NodeInfo* info);
    const std::vector<Edge*>& getAdj() const;
    NodeInfo* getInfo() const;
};

#endif
