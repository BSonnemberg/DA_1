#include "Graph.h"

Graph::Graph(const Graph& g) {
    for (Vertex* v : g.nodes) {
        this->nodes.push_back(new Vertex(v->info));
    }
    for (Vertex* v : g.nodes) {
        for (Edge* e : v->out) {
            Vertex* src = this->findVertex(*v->getInfo());
            Vertex* dest = this->findVertex(*e->getDest()->getInfo());
            src->addEdgeTo(dest, e->getCapacity(), e->getFlow());
        }
    }
}

Graph::Graph() {
    // create master source and sink nodes, that will
    // stay permanently attached to the graph
    auto src = std::make_shared<NodeInfo>(-1, "R_MASTER");
    auto sink = std::make_shared<NodeInfo>(-2, "C_MASTER");
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

Vertex* Graph::addVertex(const NodeInfoPtr& info) {

    if (findVertex(info->getCode()) != nullptr) {
        return nullptr;
    }
    auto* vtx = new Vertex(info);
    this->nodes.push_back(vtx);

    // connect master source to vertex
    if (info->getType() == WATER_RESERVOIR) {
        const auto* r = dynamic_cast<Reservoir*>(info.get());
        if (r == nullptr) return nullptr;
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

bool Graph::addEdge(const NodeInfo &i1, const NodeInfo &i2, const int &cap) const {
    Vertex* v1 = this->findVertex(i1);
    Vertex* v2 = this->findVertex(i2);
    if (v1 == nullptr || v2 == nullptr) return false;
    v1->addEdgeTo(v2, cap);
    return true;
}
