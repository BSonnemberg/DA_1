#include "DataHandler.h"
#include <queue>

bool DataHandler::findAugmPath(Graph& g, Vertex* src, Vertex* sink) {

    std::queue<Vertex*> q;
    for (auto* v : g.nodes) {
        v->path = nullptr;
        v->bneck = INT_MAX;
    }
    q.push(src);

    // start bfs search
    while (!q.empty()) {

        const Vertex* v = q.front();
        q.pop();

        printf("AT VERTEX >>> %s\n", v->getInfo()->getCode().c_str());

        for (Edge* e : v->getAdj()) {

            // r > residual capacity
            int r = e->capacity - e->flow;
            if (r <= 0) continue;

            if (e->getDest() == src) continue;

            if (e->getCapacity() == 0) {
                printf("At RESIDUAL edge from %s > %s\n", e->getOrigin()->getInfo()->getCode().c_str(), e->getDest()->getInfo()->getCode().c_str());
            }
            else printf("At edge from %s > %s\n", e->getOrigin()->getInfo()->getCode().c_str(), e->getDest()->getInfo()->getCode().c_str());

            // node is unvisited
            Vertex* v2 = e->getDest();
            if (v2->path == nullptr) {
                v2->bneck = std::min(v->bneck, r);
                v2->path = e;
                q.push(v2);
            }

            // target found
            if (v2 == sink) return true;
        }
        printf("-----\n");
    }
    return false;
}

int DataHandler::edmondsKarp(Graph& g) {

    int maxFlow = 0;
    Graph g2(g); // residual graph

    // create master and sink nodes
    auto* src = new NodeInfo(-1, "R_MASTER");
    auto* sink = new NodeInfo(-2, "C_MASTER");

    Vertex* srcVtx = g2.addVertex(src);
    Vertex* sinkVtx = g2.addVertex(sink);

    // connect master nodes and original nodes
    for (Vertex* v : g2.nodes) {
        if (v->getInfo()->getType() == WATER_RESERVOIR && v != srcVtx) {
            const auto* r = static_cast<Reservoir*>(v->getInfo());
            srcVtx->addEdgeTo(v, r->getMaxDelivery());
        }
        else if (v->getInfo()->getType() == DELIVERY_SITE) {
            v->addEdgeTo(sinkVtx, INT_MAX);
        }
    }

    while (findAugmPath(g2, srcVtx, sinkVtx)) {

        Vertex* v = sinkVtx;
        int bneck = sinkVtx->bneck;

        while (v != srcVtx) {

            // update flow
            v->path->flow += bneck;

            Edge* res = v->path->getReverse();
            if (res != nullptr) {
                // update residual edge
                res->flow += bneck;
            } else {
                // create residual edge
                v->addEdgeTo(v->path->getOrigin(), 0, -bneck);
            }
            v = v->path->getOrigin();
        }
        maxFlow += bneck;
        printf("\n+++++++++++++++++++\n\n");
    }
    return maxFlow;
}
