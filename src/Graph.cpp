#include "Graph.h"

Graph::~Graph() {
    // free mem. allocated to vertices
    for (Vertex* v : this->nodes) {
        delete v;
    }
}

Vertex* Graph::findVertex(const NodeInfo& info) const {
    for (Vertex* v : this->nodes) {
        if (v->getInfo() == info) return v;
    }
    return nullptr;
}

bool Graph::addVertex(const NodeInfo& info) {
    if (findVertex(info) != nullptr) return false;
    this->nodes.push_back(new Vertex(info));
    return true;
}

bool Graph::removeVertex(const NodeInfo& info) {
    for (auto it = nodes.begin(); it != nodes.end(); it++) {
        Vertex* v = *it;
        // found target
        if (v->getInfo() == info) {
            nodes.erase(it);
            for (Vertex* u : this->nodes) {
                // remove edges > to target
                u->removeEdgeTo(v);
            }
            delete v;
            return true;
        }
    }
    return false;
}
