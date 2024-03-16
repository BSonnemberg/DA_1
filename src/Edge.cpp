#include "Edge.h"

Edge::Edge(Vertex *dest, const float& weight) {
    this->dest = dest;
    this->weight = weight;
}

Vertex *Edge::getDest() const {
    return this->dest;
}

float Edge::getWeight() const {
    return this->weight;
}
