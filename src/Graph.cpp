#include "Graph.h"

Graph::Graph() {
    // master nodes stay attached to the graph
    auto* src = new NodeInfo(-1, "R_MASTER");
    auto* sink = new NodeInfo(-2, "C_MASTER");
    this->nodes.push_back(new Vertex(src));
    this->nodes.push_back(new Vertex(sink));
}

Graph::Graph(const Graph& g) {
    for (const Vertex* v : g.nodes) {
        this->nodes.push_back(new Vertex(v));
    }
    for (const Vertex* v : g.nodes) {
        for (const Edge* e : v->getOutEdges()) {
            // copy edges
            Vertex* v1 = findVertex(*v->getInfo());
            Vertex* v2 = findVertex(*e->getDest()->getInfo());
            v1->addEdgeTo(v2, e->getCapacity());
        }
    }
}

Graph::~Graph() {
    for (const Vertex* vtx : this->nodes) {
        delete vtx;
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

bool Graph::addVertex(Vertex *v) {
    if (findVertex(*v->getInfo()) != nullptr) {
        return false;
    }
    this->nodes.push_back(v);
    return true;
}

Vertex* Graph::addVertex(NodeInfo* i) {
    if (i == nullptr) {
        return nullptr;
    }
    if (findVertex(*i) != nullptr) {
        return nullptr;
    }
    Vertex* vtx = new Vertex(i);
    this->nodes.push_back(vtx);
    return vtx;
}

Vertex* Graph::addVertex(Reservoir* i) {
    Vertex* vtx = addVertex(static_cast<NodeInfo*>(i));
    // connect to master src
    nodes[0]->addEdgeTo(vtx, i->getMaxDelivery());
    return vtx;
}

Vertex* Graph::addVertex(Station* i) {
    return addVertex(static_cast<NodeInfo*>(i));
}

Vertex *Graph::addVertex(City *i) {
    Vertex* vtx = addVertex(static_cast<NodeInfo*>(i));
    if (vtx != nullptr) {
        // connect to master sink
        vtx->addEdgeTo(nodes[1], i->getDemand());
    }
    return vtx;
}

bool Graph::removeVertex(const NodeInfo& info, const bool& freeMem) {
    for (auto it = nodes.begin(); it != nodes.end(); ++it) {
        Vertex* v = *it;
        // found target
        if (*v->getInfo() == info) {
            nodes.erase(it);
            for (Edge* e : v->getOutEdges()) {
                // remove edge from target > ...
                v->removeOutEdge(e, freeMem);
            }
            for (Vertex* u : this->nodes) {
                // remove edges > to target
                u->removeEdgeTo(v, freeMem);
            }
            if (freeMem) delete v;
            return true;
        }
    }
    return false;
}

/**
 * @brief Get all delivery sites in the graph
 * @remark function is O(n), c -> no. of nodes in the graph
 * @return vector of pairs of Vertices + City* object
 */
std::vector<std::pair<Vertex*, City*>> Graph::getCities() const {
    std::vector<std::pair<Vertex*, City*>> res;
    for (Vertex* v : nodes) {
        if (v->getInfo()->getType() == DELIVERY_SITE) {
            auto* c = dynamic_cast<City*>(v->getInfo());
            if (c != nullptr) {
                res.emplace_back(v, c);
            }
        }
    }
    return res;
}
