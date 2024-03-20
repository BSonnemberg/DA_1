#ifndef EDGE_H
#define EDGE_H

#include "Vertex.h"
class Vertex;

// Edges represent pipelines
class Edge {
    Vertex* orig;
    Vertex* dest;
    int flow, capacity;
    // get reverse edge, if present
    Edge* getReverse() const;
    friend class DataHandler;
public:
    Edge(Vertex* orig, Vertex* dest, const int& cap, const int& flow=0);
    Vertex* getOrigin() const;
    Vertex* getDest() const;
    int getCapacity() const;
};

#endif
