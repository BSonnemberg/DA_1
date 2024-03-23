#include "Vertex.h"
#include "Edge.h"

Vertex::Vertex(const Vertex* v) {
    this->info = v->info;
    // new copy
    this->info.second++;
    this->path = v->path;
    this->minFlow = v->minFlow;
}

Vertex::Vertex(NodeInfo* info) {
    // keeps track of no. of copies of this vertex, so memory
    // for NodeInfo is only dealloc. when no copies are left
    this->info = {info, new int{0}};
    this->path = nullptr;
    this->minFlow = INT_MAX;
}

Vertex::~Vertex() {
    for (const auto* edge : out) {
        delete edge;
    }
    if (*info.second == 0) {
        // no copies, safe to delete
        delete info.first;
        delete info.second;
    }
    else *info.second--;
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

void Vertex::addEdgeTo(Vertex *v, const int& cap, const int& flow = 0) {
    auto* e = new Edge(this, v, cap, flow);
    out.push_back(e);
    v->in.push_back(e);
}

bool Vertex::removeEdgeTo(Vertex* v) {
    for (auto a = out.begin(); a != out.end(); ++a) {
        const Edge* e = *a;
        // find outgoing edge
        if (e->getDest() == v) {
            out.erase(a);
            // find incoming edge
            for (auto b = v->in.begin(); b != v->in.end(); ++b) {
                if (*b == e) {
                    v->in.erase(b);
                    break;
                }
            }
            delete e;
            return true;
        }
    }
    return false;
}
