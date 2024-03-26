#include "Edge.h"

Edge::Edge(Vertex* orig, Vertex* dest, const int& cap) {
    this->orig = orig;
    this->dest = dest;
    this->capacity = cap;
}

Edge::~Edge() {
    destroyResidual();
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

// auto-updates flow of residual edge too
void Edge::setFlow(const int& flow) {
    this->flow = flow;
    if (residual != nullptr) {
        residual->flow = -flow;
    }
}

Edge* Edge::createResidual() {
    if (residual == nullptr) {
        residual = dest->addEdgeTo(orig, 0);
        residual->residual = this;
        residual->flow = -flow;
    }
    return residual;
}

void Edge::destroyResidual() {
    if (this->capacity > 0) {
        this->dest->removeOutEdge(residual);
        this->residual = nullptr;
    }
}
