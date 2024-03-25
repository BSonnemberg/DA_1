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
    friend class DataHandler;
public:
    ~Vertex();
    explicit Vertex(const Vertex* v);
    explicit Vertex(NodeInfo* info);
    NodeInfo* getInfo() const;
    const std::vector<Edge*>& getOutEdges() const;
    const std::vector<Edge*>& getInEdges() const;
    // utility methods
    Edge* addEdgeTo(Vertex* dest, const int& cap);
    bool removeEdgeTo(Vertex* v);
    bool removeOutEdge(const Edge* e);
};

#endif
