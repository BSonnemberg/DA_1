#include "Vertex.h"
#include "Edge.h"

Vertex::Vertex(NodeInfo* info) {
    this->info = {info, new int(1)};
    this->minFlow = INT_MAX;
    this->path = nullptr;
}

Vertex::Vertex(const Vertex* v) {
    this->info = v->info;
    this->minFlow = INT_MAX;
    this->path = nullptr;
    // register new copy
    (*info.second)++;
}

Vertex::~Vertex() {
    for (const auto* edge : out) {
        delete edge;
    }
    if (--(*info.second) == 0) {
        delete info.first;
        delete info.second;
    }
}

NodeInfo* Vertex::getInfo() const {
    return this->info.first;
}

const std::vector<Edge*>& Vertex::getOutEdges() const {
    return this->out;
}

const std::vector<Edge*>& Vertex::getInEdges() const {
    return this->in;
}

Edge* Vertex::addEdgeTo(Vertex* dest, const int& cap) {
    auto* e = new Edge(this, dest, cap);
    out.push_back(e);
    if (cap > 0) {
        // residual edges are not added as INcoming
        // edges to the destination - not necessary
        dest->in.push_back(e);
    }
    return e;
}

bool Vertex::removeOutEdge(const Edge* e) {
    if (e == nullptr) return false;
    for (auto it = out.begin(); it != out.end(); ++it) {
        if (*it == e) {
            out.erase(it);
            Vertex* v = e->getDest();
            // find incoming edge
            for (auto it2 = v->in.begin(); it2 != v->in.end(); ++it2) {
                if (*it2 == e) {
                    v->in.erase(it2);
                    break;
                }
            }
            delete e;
            return true;
        }
    }
    return false;
}

bool Vertex::removeEdgeTo(Vertex* v) {
    for (auto it = out.begin(); it != out.end(); ++it) {
        const Edge* e = *it;
        // found target (non-residual only)
        if (e->getDest() == v && e->getCapacity() > 0) {
            out.erase(it);
            // find incoming edge
            for (auto it2 = v->in.begin(); it2 != v->in.end(); ++it2) {
                if (*it2 == e) {
                    v->in.erase(it2);
                    break;
                }
            }
            delete e;
            return true;
        }
    }
    return false;
}
