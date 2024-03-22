#include "Vertex.h"
#include "Edge.h"

Vertex::Vertex(const NodeInfoPtr& info) {
    this->info = info;
    this->bneck = INT_MAX;
    this->path = nullptr;
    this->flow = 0;
}

Vertex::~Vertex() {
    for (const auto* edge : out) {
        delete edge;
    }
}

NodeInfo* Vertex::getInfo() const {
    return this->info.get();
}

// flow passing through, run Edmonds-Karp first
int Vertex::getFlow() const {
    return this->flow;
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
