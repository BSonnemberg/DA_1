#include "DataHandler.h"
#include <queue>

/**
 * Find an augmenting path from a source to a sink node
 * @param g target graph
 * @param s source node
 * @param t sink node
 * @return whether a path was found
 */
bool DataHandler::findAugmPath(Graph& g, Vertex* s, Vertex* t) {

    std::queue<Vertex*> q;
    for (Vertex* v : g.getNodes()) {
        v->path = nullptr;
        v->minFlow = INT_MAX;
    }
    q.push(s);

    // start bfs search
    while (!q.empty()) {

        Vertex* v = q.front();
        q.pop();

        for (Edge* e : v->out) {

            // optimize by ignoring all residual
            // edges going to master source
            if (e->getDest() == s) continue;

            // residual capacity
            int r = e->getCapacity() - e->getFlow();
            if (r <= 0) continue;

            // node is unvisited
            Vertex* v2 = e->getDest();
            if (v2->path == nullptr) {
                v2->minFlow = std::min(v->minFlow, r);
                v2->path = e;
                q.push(v2);
            }

            if (v2 == t) return true;
        }
    }
    return false;
}

/**
 * Perform the edmonds-karp algorithm to find the
 * maximum flow of the water supply network
 *
 * @param g target graph
 * @return max flow between source and sink
 */
int DataHandler::edmondsKarp(Graph& g) {

    int maxFlow = 0;
    Vertex* src = g.getNodes()[0];
    Vertex* sink = g.getNodes()[1];

    while (findAugmPath(g, src, sink)) {

        // min residual capacity of the path
        const int bneck = sink->minFlow;

        for (Vertex* v=sink; v!=src; v=v->path->getOrigin()) {

            // update flow
            v->path->setFlow(v->path->getFlow() + bneck);

            // create residual edge if absent
            v->path->createResidual();
        }
        maxFlow += bneck;
    }

    // clean up graph
    for (Vertex* v : g.getNodes()) {
        for (Edge* e : v->getOutEdges()) {
            e->destroyResidual();
        }
    }
    return maxFlow;
}
