#include "Vertex.h"
#include "Edge.h"

Vertex::Vertex(NodeInfo* info) {
    this->info = info;
    this->bneck = INT_MAX;
    this->inFlow = 0;
}

Vertex::~Vertex() {
    for (const auto* edge : adj) {
        delete edge;
    }
    delete this->info;
}

NodeInfo* Vertex::getInfo() const {
    return this->info;
}

int Vertex::getIncomingFlow() const {
    return this->inFlow;
}

const std::vector<Edge*>& Vertex::getAdj() const {
    return this->adj;
}

void Vertex::addEdgeTo(Vertex *v, const int& cap, const int& flow) {
    this->adj.emplace_back(new Edge(this,v,cap,flow));
}

bool Vertex::removeEdgeTo(const Vertex* v) {
    for (auto it = adj.begin(); it != adj.end(); ++it) {
        const Edge* e = *it;
        if (e->getDest() == v) {
            adj.erase(it);
            delete e;
            return true;
        }
    }
    return false;
}
