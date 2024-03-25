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
    for (Vertex* v : g.nodes) {
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
 * @return max flow of the graph
 */
int DataHandler::edmondsKarp(Graph& g, bool s) {

    int maxFlow = 0;
    Vertex* src = g.nodes[0];
    Vertex* sink = g.nodes[1];
    // reset flow for all edges
    if (s) {
        for (Vertex* v : g.nodes) {
            for (Edge* e : v->out) {
                e->setFlow(0);
                //e->destroyResidual();
            }
        }
    }
    while (findAugmPath(g, src, sink)) {

        // bottleneck of the sink represents
        // the min residual capacity of the path
        const int bneck = sink->minFlow;

        for (Vertex* v = sink; v!=src; v=v->path->getOrigin()) {

            // update flow
            v->path->setFlow(v->path->getFlow() + bneck);

            Edge* res = v->path->getResidual();
            if (res == nullptr) {
                // create residual edge
                v->path->createResidual();
            }
        }
        maxFlow += bneck;
    }

    // clean up graph
    for (Vertex* v : g.nodes) {
        for (Edge* e : v->getOutEdges()) {
            e->destroyResidual();
        }
    }
    return maxFlow;
}

void DataHandler::removeEdgeCascade(Edge* e, int flow) {

    e->setFlow(e->getFlow() - flow);

    if (e->getDest()->out.empty()) {
        // end of cascade
        return;
    }

    for (Edge* e2 : e->getDest()->out) {
        // remove max flow possible from each
        // edge until 'flow' value is reached
        int aux = std::min(e2->getFlow(), flow);
        removeEdgeCascade(e2, aux);
        if ((flow -= aux) == 0) return;
    }
}

int DataHandler::removeNodeCascade(Graph& g, Vertex* v) {
    int a=0;
    for (Edge* e : v->out) {
        if (e->getFlow() > 0) {
            a+= e->getFlow();
            removeEdgeCascade(e, e->getFlow());
        }
        v->removeOutEdge(e);
    }
    printf("Total flow removed > %d\n", a);
    /////
     for (Vertex* v : g.nodes) {
         for (Edge* e : v->out) {
             if (e->getFlow() > 0) {
                 // put back residual edge
                 e->createResidual();
             }
         }
     }
    return a;
}
