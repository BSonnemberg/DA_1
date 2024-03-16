#include "Vertex.h"
#include <utility>

Vertex::Vertex(NodeInfo info) : info(std::move(info)) {}

const std::vector<Edge>& Vertex::getAdj() const {
    return this->adj;
}
