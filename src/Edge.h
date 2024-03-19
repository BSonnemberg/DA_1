#ifndef EDGE_H
#define EDGE_H

#include "Vertex.h"
class Vertex;

// Edges represent pipelines
class Edge {
    Vertex* orig;
    Vertex* dest;
    int capacity;
    int flow = 0;
    friend class DataHandler;
public:
    Edge(Vertex* orig, Vertex* dest, const int& cap);
    Vertex* getOrigin() const;
    Vertex* getDest() const;
    int getCapacity() const;
    Edge* getReverse() const;
};

#endif
