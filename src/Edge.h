#ifndef EDGE_H
#define EDGE_H

class Vertex;

class Edge {
    Vertex* dest;
    float weight;
public:
    Edge(Vertex* dest, const float& weight);
    Vertex* getDest() const;
    float getWeight() const;
};

#endif
