#include "Edge.h"

Edge::Edge(Vertex* orig, Vertex* dest, const int& cap, const int& flow) {
    this->orig = orig;
    this->dest = dest;
    this->capacity = cap;
    this->flow = flow;
}

Vertex* Edge::getOrigin() const {
    return this->orig;
}

Vertex* Edge::getDest() const {
    return this->dest;
}

int Edge::getCapacity() const {
    return this->capacity;
}

int Edge::getFlow() const {
    return this->flow;
}

Edge* Edge::getReverse() const {
    for (Edge* e : dest->getOutEdges()) {
        if (e->getDest() == orig) {
            return e;
        }
    }
    return nullptr;
}
