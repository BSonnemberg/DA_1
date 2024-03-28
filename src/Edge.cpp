#include "Edge.h"

Edge::Edge(Vertex* orig, Vertex* dest, const int& cap) {
    this->orig = orig;
    this->dest = dest;
    this->capacity = cap;
}

Edge::~Edge() {
    this->destroyResidual();
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
    return this->residual;
}

void Edge::setFlow(const int& flow) {
    this->flow = flow;
    // residual edge is also updated
    if (this->residual != nullptr) {
        this->residual->flow = -flow;
    }
}

void Edge::createResidual() {
    if (this->residual == nullptr) {
        residual = dest->addEdgeTo(orig, 0);
        residual->residual = this;
        residual->flow = -flow;
    }
}

void Edge::destroyResidual() {
    if (this->capacity > 0) {
        dest->removeOutEdge(residual);
        this->residual = nullptr;
    }
}
