#include "Edge.h"

Edge::Edge(Vertex *dest, const float& cap) {
    this->dest = dest;
    this->capacity = cap;
    this->flow = 0;
}

Vertex *Edge::getDest() const {
    return this->dest;
}

float Edge::getCapacity() const {
    return this->capacity;
}

bool Edge::isAtCapacity() const {
    return this->flow == this->capacity;
}
