#ifndef EDGE_H
#define EDGE_H

class Vertex;

// Edges represent pipelines
class Edge {
    Vertex* dest;
    float capacity;
    float flow;
public:
    Edge(Vertex* dest, const float& cap);
    Vertex* getDest() const;
    float getCapacity() const;
    bool isAtCapacity() const;
};

#endif
