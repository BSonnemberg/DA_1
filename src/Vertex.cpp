#include "Vertex.h"
#include <utility>

Vertex::Vertex(NodeInfo info) : info(std::move(info)) {}

const std::vector<Edge>& Vertex::getAdj() const {
    return this->adj;
}

NodeInfo Vertex::getInfo() const {
    return this->info;
}

bool Vertex::removeEdgeTo(Vertex *v) {
    for (auto it = adj.begin(); it != adj.end(); it++) {
        if (it->getDest() == v) {
            adj.erase(it);
            return true;
        }
    }
    return false;
}
