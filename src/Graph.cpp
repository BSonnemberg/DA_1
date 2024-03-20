#include "Graph.h"

Graph::~Graph() {
    // free mem. allocated to vertices
    for (const Vertex* v : this->nodes) {
        delete v;
    }
}

Graph::Graph(const Graph &g) {
    for (const Vertex* v : g.nodes) {
        // copy nodes to new graph
        //auto* info = new NodeInfo(*v->getInfo());
        // ERROR WHEN HANDLING MEMORY
        this->nodes.push_back(new Vertex(v->getInfo()));
    }
    // then copy the edges
    for (const Vertex* v : g.nodes) {
        for (const auto* e : v->adj) {
            const NodeInfo* i1 = v->getInfo();
            const NodeInfo* i2 = e->getDest()->getInfo();
            this->addEdge(*i1, *i2, e->getCapacity());
        }
    }
}

const std::vector<Vertex*>& Graph::getNodes() const {
    return this->nodes;
}

Vertex* Graph::findVertex(const NodeInfo& info) const {
    return this->findVertex(info.getCode());
}

Vertex* Graph::findVertex(const std::string& code) const {
    for (Vertex* v : this->nodes) {
        if (v->getInfo()->getCode() == code) return v;
    }
    return nullptr;
}

Vertex* Graph::addVertex(NodeInfo* info) {
    if (findVertex(info->getCode()) != nullptr) return nullptr;
    auto* vtx = new Vertex(info);
    this->nodes.push_back(vtx);
    return vtx;
}

bool Graph::removeVertex(const NodeInfo& info) {
    for (auto it = nodes.begin(); it != nodes.end(); ++it) {
        const Vertex* v = *it;
        // found target
        if (*v->getInfo() == info) {
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

bool Graph::addEdge(const NodeInfo &i1, const NodeInfo &i2, const int &cap) {
    Vertex* v1 = this->findVertex(i1);
    Vertex* v2 = this->findVertex(i2);
    if (v1 == nullptr || v2 == nullptr) return false;
    v1->addEdgeTo(v2, cap);
    return true;
}
