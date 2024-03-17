#include "Graph.h"

Graph::~Graph() {
    // free mem. allocated to vertices
    for (Vertex* v : this->nodes) {
        delete v;
    }
}

Graph::Graph(const Graph &g) {
    // copy nodes to new graph
    for (auto v : g.nodes) {
        this->nodes.push_back(new Vertex(v->getInfo()));
    }
    for (auto v : g.nodes) {
        for (auto e : v->adj) {
            // then copy the edges
            std::string c1 = v->getInfo().getCode();
            std::string c2 = e.getDest()->getInfo().getCode();
            this->addEdge(c1, c2, e.getCapacity());
        }
    }
}

const std::vector<Vertex*>& Graph::getNodes() const {
    return this->nodes;
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
