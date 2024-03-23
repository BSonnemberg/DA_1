#ifndef VERTEX_H
#define VERTEX_H

#include "Reservoir.h"
#include "Station.h"
#include "City.h"

class Edge;

class Vertex {
    std::pair<NodeInfo*, int*> info;
    std::vector<Edge*> out;
    std::vector<Edge*> in;
    Edge* path;
    int minFlow;
    // utility methods
    void addEdgeTo(Vertex* v, const int& cap, const int& flow=0);
    bool removeEdgeTo(Vertex* v);
    friend class Graph;
    friend class DataHandler;
public:
    ~Vertex();
    explicit Vertex(const Vertex* v);
    explicit Vertex(NodeInfo* info);
    NodeInfo* getInfo() const;
    const std::vector<Edge*>& getOutEdges() const;
    const std::vector<Edge*>& getInEdges() const;
};

#endif
