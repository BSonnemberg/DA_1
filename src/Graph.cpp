#include "Graph.h"

Graph::Graph() {
    // master nodes stay permanently attached to the graph
    auto* src = new NodeInfo(-1, "R_MASTER");
    auto* sink = new NodeInfo(-2, "C_MASTER");
    this->nodes.push_back(new Vertex(src));
    this->nodes.push_back(new Vertex(sink));
}

Graph::Graph(const Graph& g) {
    // copy nodes
    for (const Vertex* v : g.nodes) {
        this->nodes.push_back(new Vertex(v));
    }
    // copy edges
    for (const Vertex* v : g.nodes) {
        for (const Edge* e : v->out) {
            Vertex* s = findVertex(*v->getInfo());
            Vertex* d = findVertex(*e->getDest()->getInfo());
            s->addEdgeTo(d, e->getCapacity(), e->getFlow());
        }
    }
}

Graph::~Graph() {
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

    if (info == nullptr) return nullptr;
    if (findVertex(info->getCode()) != nullptr) {
        return nullptr;
    }

    Vertex* vtx = new Vertex(info);
    this->nodes.push_back(vtx);

    // connect master src to reservoir
    if (info->getType() == WATER_RESERVOIR) {
        const auto* r = dynamic_cast<Reservoir*>(info);
        if (r == nullptr) return nullptr;
        nodes[0]->addEdgeTo(vtx, r->getMaxDelivery());
    }

    // connect city to master sink
    else if (info->getType() == DELIVERY_SITE) {
        vtx->addEdgeTo(nodes[1], INT_MAX);
    }
    return vtx;
}

bool Graph::removeVertex(const NodeInfo& info) {
    for (auto it = nodes.begin(); it != nodes.end(); ++it) {
        Vertex* v = *it;
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

bool Graph::addEdge(const std::string& c1, const std::string& c2, const int& cap) {
    Vertex* v1 = this->findVertex(c1);
    Vertex* v2 = this->findVertex(c2);
    if (v1 == nullptr || v2 == nullptr) return false;
    v1->addEdgeTo(v2, cap);
    return true;
}