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
    void addEdgeTo(Vertex* v, const int& cap, const int& flow);
    bool removeEdgeTo(Vertex* v);
public:
    ~Vertex();
    explicit Vertex(const Vertex* v);
    explicit Vertex(NodeInfo* info);
    NodeInfo* getInfo() const;
    const std::vector<Edge*>& getOutEdges() const;
    const std::vector<Edge*>& getInEdges() const;
};

#endif
