#ifndef VERTEX_H
#define VERTEX_H

#include "Reservoir.h"
#include "Station.h"
#include "City.h"

class Edge;

class Vertex {
    NodeInfo* info;
    std::vector<Edge*> out;
    std::vector<Edge*> in;
    // keep track of copies of this Vertex to know
    // when to dealloc. memory for NodeInfo
    int* copies;
    Edge* path;
    int minFlow;
public:
    ~Vertex();
    Vertex(NodeInfo* info);
    Vertex(const Vertex* v);
    NodeInfo* getInfo() const;
    const std::vector<Edge*>& getOutEdges() const;
    const std::vector<Edge*>& getInEdges() const;
    // utility methods
    bool addOutEdge(Edge* e);
    Edge* addEdgeTo(Vertex* to, const int& weight);
    bool removeEdgeTo(const Vertex* v, const bool& freeMem = true);
    bool removeOutEdge(const Edge* e, const bool& freeMem = true);
    friend class DataHandler;
};

#endif
