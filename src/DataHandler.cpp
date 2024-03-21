#include "DataHandler.h"
#include <queue>

/**
 * Find an augmenting path from a source to a sink node
 * @param g target graph
 * @param src source node
 * @param sink sink node
 * @return whether a path was found
 */
bool DataHandler::findAugmPath(Graph& g, Vertex* src, Vertex* sink) {

    std::queue<Vertex*> q;
    for (Vertex* v : g.nodes) {
        v->path = nullptr;
        v->bneck = INT_MAX;
    }
    q.push(src);

    // start bfs search
    while (!q.empty()) {

        Vertex* v = q.front();
        q.pop();

        for (Edge* e : v->adj) {

            // optimize by ignoring all residual
            // edges going to master source
            if (e->dest == src) continue;

            // residual capacity
            int r = e->capacity - e->flow;
            if (r <= 0) continue;

            // node is unvisited
            Vertex* v2 = e->dest;
            if (v2->path == nullptr) {
                v2->bneck = std::min(v->bneck, r);
                v2->path = e;
                q.push(v2);
            }

            if (v2 == sink) return true;
        }
    }
    return false;
}

/**
 * Perform the edmonds-karp algorithm to find the
 * maximum flow of the water supply network
 *
 * @param g target graph
 * @return max flow of the graph
 */
int DataHandler::edmondsKarp(Graph& g) {

    int maxFlow = 0;
    Vertex* src = g.nodes[0];
    Vertex* sink = g.nodes[1];

    // reset flow for all edges
    for (Vertex* v : g.nodes) {
        v->inFlow = 0;
        for (Edge* e : v->adj) {
            e->flow = 0;
        }
    }

    while (findAugmPath(g, src, sink)) {

        // bottleneck of the sink represents
        // the min residual capacity of the path
        const int bneck = sink->bneck;

        for (Vertex* v = sink; v!=src; v=v->path->orig) {

            // update flow
            v->path->flow += bneck;

            Edge* res = v->path->getReverse();
            if (res != nullptr) res->flow -= bneck;
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
            const Edge* e = *it;
            // remove residual edge
            if (e->capacity == 0) {
                v->adj.erase(it);
                delete e;
            }
            else {
                // update incoming flow for each vtx
                e->dest->inFlow += e->flow;
                ++it;
            }
        }
    }
    return maxFlow;
}

/**
 * Get cities whose water needs are not met
 * (make sure to run Edmonds-karp first)
 * @param g target graph
 * @return list of undersupplied cities
 */
std::vector<City*> DataHandler::undersuppliedCities(Graph& g) {

    std::vector<City*> res;
    // assuming edmonds karp was run before this
    // and inFlow values are updated

    for (const Vertex* v : g.nodes) {
        NodeInfo* info = v->getInfo();
        if (info->getType() == DELIVERY_SITE && info->getId() != -2) {
            // downcast back to City
            auto* c = dynamic_cast<City*>(info);
            if (c == nullptr) continue;
            if (v->inFlow < c->getDemand()) res.push_back(c);
        }
    }
    return res;
}
