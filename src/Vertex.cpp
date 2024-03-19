#include "Vertex.h"

Vertex::~Vertex() {
    delete this->info;
}

Vertex::Vertex(const NodeInfo& info) {
    this->info = new NodeInfo(info);
    this->bottleneck = INT_MAX;
}

NodeInfo* Vertex::getInfo() const {
    return this->info;
}

const std::vector<Edge>& Vertex::getAdj() const {
    return this->adj;
}

void Vertex::addEdgeTo(Vertex *v, const int& cap) {
    this->adj.emplace_back(this, v,cap);
}

bool Vertex::removeEdgeTo(const Vertex* v) {
    for (auto it = adj.begin(); it != adj.end(); ++it) {
        if (it->getDest() == v) {
            adj.erase(it);
            return true;
        }
    }
    return false;
}
