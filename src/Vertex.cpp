#include "Vertex.h"
#include "Edge.h"

Vertex::Vertex(NodeInfo* info) {
    this->info = {info, new int{0}};
    this->minFlow = INT_MAX;
    this->path = nullptr;
}

Vertex::Vertex(const Vertex* v) {
    this->info = v->info;
    this->path = v->path;
    this->minFlow = v->minFlow;
    *info.second++; // new copy
}

Vertex::~Vertex() {
    for (const auto* edge : out) {
        delete edge;
    }
    if (*info.second == 0) {
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

void Vertex::addEdgeTo(Vertex *v, const int& cap, const int& flow) {
    auto* e = new Edge(this, v, cap, flow);
    this->out.push_back(e);
    v->in.push_back(e);
}

bool Vertex::removeEdgeTo(Vertex* v) {
    for (auto a = out.begin(); a != out.end(); ++a) {
        const Edge* e = *a;
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
