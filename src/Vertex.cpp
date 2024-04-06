#include "Vertex.h"
#include "Edge.h"

Vertex::Vertex(NodeInfo* info) {
    this->info = info;
    this->copies = new int(0);
    this->minFlow = INT_MAX;
    this->path = nullptr;
}

Vertex::Vertex(const Vertex* v) {
    this->info = v->info;
    this->minFlow = INT_MAX;
    this->path = nullptr;
    // register new copy
    this->copies = v->copies;
    (*this->copies)++;
}

Vertex::~Vertex() {
    for (const Edge* edge : out) {
        delete edge;
    }
    if ((*this->copies)-- == 0) {
        // free if no copies active
        delete this->info;
        delete this->copies;
    }
}

NodeInfo* Vertex::getInfo() const {
    return this->info;
}

const std::vector<Edge*>& Vertex::getOutEdges() const {
    return this->out;
}

const std::vector<Edge*>& Vertex::getInEdges() const {
    return this->in;
}

bool Vertex::addOutEdge(Edge* e) {
    for (const Edge* out : out) {
        if (out == e) return false;
    }
    out.push_back(e);
    e->getDest()->in.push_back(e);
    return true;
}

Edge* Vertex::addEdgeTo(Vertex* to, const int& weight) {
    if (to == nullptr) {
        return nullptr;
    }
    Edge* e = new Edge(this, to, weight);
    out.push_back(e);
    // residual edges aren't marked as incoming edges
    if (weight > 0) {
        to->in.push_back(e);
    }
    return e;
}

bool Vertex::removeEdgeTo(const Vertex* v, const bool& freeMem) {
    if (v == nullptr) {
        return false;
    }
    for (const Edge* e : this->out) {
        // targets non-residual edges only
        if (e->getDest() == v && e->getCapacity() > 0) {
            return removeOutEdge(e, freeMem);
        }
    }
    return false;
}

bool Vertex::removeOutEdge(const Edge* e, const bool& freeMem) {
    if (e == nullptr) {
        return false;
    }
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
            if (freeMem) delete e;
            return true;
        }
    }
    return false;
}
