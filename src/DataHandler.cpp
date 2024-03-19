#include "DataHandler.h"
#include <queue>

bool DataHandler::findAugmPath(Graph &g, Vertex* src, Vertex* sink) {

    std::queue<Vertex*> q;
    for (auto* v : g.nodes) {
        v->path = nullptr;
        v->bottleneck = INT_MAX;
    }
    q.push(src);

    // start bfs search
    while (!q.empty()) {

        Vertex* v = q.front();
        q.pop();

        if (v == sink) {
            // target found
            return true;
        }

        for (Edge e : v->adj) {
            int aux = e.capacity - e.flow;
            if (aux == 0) {
                // pipe at capacity, skip
                continue;
            }
            Vertex* v2 = e.getDest();
            if (v2->path == nullptr) {
                v2->bottleneck = std::min(v->bottleneck, aux);
                v2->path = &e;
                q.push(v2);
            }
        }
    }
    return false;
}

void DataHandler::edmondsKarp(Graph &g) {

    int maxFlow = 0;
    Graph g2(g); // copy/ residual graph

    // create master and sink nodes
    const NodeInfo src(-1, "P_MASTER");
    const NodeInfo sink(-1, "C_MASTER");

    Vertex* srcVtx = g2.addVertex(src);
    Vertex* sinkVtx = g2.addVertex(sink);

    for (Vertex* v : g2.nodes) {
        if (v->getInfo()->getType() == WATER_RESERVOIR) {
            // connect master source to all sources
            // edge weight is source capacity
            const auto* r = static_cast<Reservoir*>(v->getInfo());
            srcVtx->addEdgeTo(v, r->getMaxDelivery());
        }
        else if (v->getInfo()->getType() == DELIVERY_SITE) {
            // connect sinks to master sink
            v->addEdgeTo(sinkVtx, INT_MAX);
        }
    }

    while (findAugmPath(g2, srcVtx, sinkVtx)) {
        const int bneck = sinkVtx->bottleneck;
        // update residual graph
        for (Vertex* v = sinkVtx; v != srcVtx; v = v->path->getOrigin()) {
            v->path->flow += bneck;
            Edge* residual = v->path->getReverse();
            if (residual != nullptr) {
                residual += bneck;
            } else {
                // setup residual edge
                v->addEdgeTo(v->path->getOrigin(), -bneck);
            }
        }
        maxFlow += bneck;
    }
    printf("\nStopped");
}