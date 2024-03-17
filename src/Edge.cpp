#include "Edge.h"

Edge::Edge(Vertex *dest, const float& cap) {
    this->dest = dest;
    this->capacity = cap;
}

Vertex *Edge::getDest() const {
    return this->dest;
}

float Edge::getCapacity() const {
    return this->capacity;
}
