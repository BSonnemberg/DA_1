#include "Edge.h"

Edge::Edge(Vertex* orig, Vertex *dest, const int& cap) {
    this->orig = orig;
    this->dest = dest;
    this->capacity = cap;
}

Vertex *Edge::getOrigin() const {
    return this->orig;
}

Vertex *Edge::getDest() const {
    return this->dest;
}

int Edge::getCapacity() const {
    return this->capacity;
}

Edge* Edge::getReverse() const {
    for (Edge e : dest->getAdj()) {
        if (e.getDest() == orig) return &e;
    }
    return nullptr;
}

