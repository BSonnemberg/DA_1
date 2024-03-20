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

        for (Edge* e : v->getAdj()) {

            // r > residual capacity
            int r = e->capacity - e->flow;
            if (r <= 0) continue;

            if (e->getDest() == src) continue;

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
    }
    return false;
}

int DataHandler::edmondsKarp(Graph& g) {

    int maxFlow = 0;
    Vertex* src = g.nodes[0];
    Vertex* sink = g.nodes[1];

    while (findAugmPath(g, src, sink)) {

        // bottleneck of the sink represents
        // the min residual capacity of the path
        const int bneck = sink->bneck;

        for (Vertex* v = sink; v!=src; v=v->path->orig) {

            v->path->flow += bneck; // update flow

            Edge* res = v->path->getReverse();
            if (res != nullptr) res->flow += bneck;
            else {
                // create residual edge
                v->addEdgeTo(v->path->orig, 0, -bneck);
            }
        }
        maxFlow += bneck;
    }

    // clean up graph
    for (Vertex* v : g.nodes) {
        for (auto it = v->adj.begin(); it != v->adj.end();) {
            Edge* e = *it;
            // remove residual edge
            if (e->capacity == 0) {
                v->adj.erase(it);
                delete e;
            }
            else {
                e->flow = 0;
                ++it;
            }
        }
    }
    return maxFlow;
}