#ifndef EDGE_H
#define EDGE_H

#include "Vertex.h"

// Edges represent pipelines
class Edge {
    Vertex* orig;
    Vertex* dest;
    int capacity;
    int flow = 0;
    Edge* residual = nullptr;
public:
    ~Edge();
    Edge(Vertex* orig, Vertex* dest, const int& cap);
    Vertex* getOrigin() const;
    Vertex* getDest() const;
    int getCapacity() const;
    int getFlow() const;
    void setFlow(const int& flow);
    // handle residual counterpart
    Edge* getReverse() const;
    Edge* createResidual();
    void destroyResidual();
};

#endif
