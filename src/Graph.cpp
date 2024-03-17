#include "Graph.h"

Graph::~Graph() {
    // free mem. allocated to vertices
    for (Vertex* v : this->nodes) {
        delete v;
    }
}

Vertex* Graph::findVertex(const std::string& code) const {
    for (Vertex* v : this->nodes) {
        if (v->getInfo().getCode() == code) return v;
    }
    return nullptr;
}

bool Graph::addVertex(const NodeInfo& info) {
    if (findVertex(info.getCode()) != nullptr) return false;
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

bool Graph::addEdge(const std::string& c1, const std::string& c2, float w) {
    Vertex* v1 = this->findVertex(c1);
    Vertex* v2 = this->findVertex(c2);
    if (v1 == nullptr || v2 == nullptr) return false;
    v1->addEdgeTo(v2, w);
    return true;
}
