#include "Graph.h"

Graph::Graph() {
    // create master source and sink nodes, that will
    // stay permanently attached to the graph
    auto* src = new NodeInfo(-1, "R_MASTER");
    auto* sink = new NodeInfo(-2, "C_MASTER");
    this->nodes.push_back(new Vertex(src));
    this->nodes.push_back(new Vertex(sink));
}

Graph::~Graph() {
    // free mem. allocated to vertices
    for (const Vertex* v : this->nodes) {
        delete v;
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

    if (findVertex(info->getCode()) != nullptr) {
        return nullptr;
    }
    auto* vtx = new Vertex(info);
    this->nodes.push_back(vtx);

    // connect master source to vertex
    if (info->getType() == WATER_RESERVOIR) {
        const auto* r = dynamic_cast<Reservoir*>(info);
        nodes[0]->addEdgeTo(vtx, r->getMaxDelivery());
    }

    // connect vertex to master sink
    else if (info->getType() == DELIVERY_SITE) {
        vtx->addEdgeTo(nodes[1], INT_MAX);
    }
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

bool Graph::addEdge(const NodeInfo &i1, const NodeInfo &i2, const int &cap) const {
    Vertex* v1 = this->findVertex(i1);
    Vertex* v2 = this->findVertex(i2);
    if (v1 == nullptr || v2 == nullptr) return false;
    v1->addEdgeTo(v2, cap);
    return true;
}
