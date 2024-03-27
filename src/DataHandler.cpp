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
 * @param src source node
 * @param sink sink node
 * @return max flow between source and sink
 */
int DataHandler::edmondsKarp(Graph& g, Vertex* src, Vertex* sink) {

    int maxFlow = 0;

    while (findAugmPath(g, src, sink)) {

        // bottleneck of the sink represents
        // the min residual capacity of the path
        const int bneck = sink->minFlow;

        for (Vertex* v = sink; v!=src; v=v->path->getOrigin()) {

            // creates residual edge if not present
            v->path->createResidual();

            // update flow (reverse edge is auto-updated)
            v->path->setFlow(v->path->getFlow() + bneck);
        }
        maxFlow += bneck;
    }
    return maxFlow;
}

/**
 * Find the maximum flow of the water supply network
 * @param g target graph
 * @return max flow of the graph
 */
int DataHandler::getMaxFlow(Graph &g) {

    Vertex* src = g.nodes[0];
    Vertex* sink = g.nodes[1];

    // reset flow for all edges
    for (const Vertex* v : g.nodes) {
        for (Edge* e : v->out) {
            e->setFlow(0);
        }
    }

    int maxFlow = edmondsKarp(g, src, sink);

    // clean up graph
    for (Vertex* v : g.nodes) {
        v->path = nullptr;
        for (Edge* e : v->getOutEdges()) {
            e->destroyResidual();
        }
    }
    return maxFlow;
}

/**
 * Shrink the flow of an edge in cascade form
 * @param e target edge
 * @param flow how much flow to remove
 * @param fw whether cascade moves forward v. backwards
 */
void DataHandler::shrinkEdge(Edge* e, int flow, const int& fw) {

    if (flow == 0) return;
    e->setFlow(e->getFlow() - flow);

    // next set of edges in cascade
    std::vector<Edge*> next = e->getOrigin()->in;
    if (fw) next = e->getDest()->out;

    if (next.empty()) {
        // end of cascade
        return;
    }

    for (Edge* e2 : next) {

        if (flow == 0) {
            return;
        }
        if (e2->getFlow() == 0) {
            continue;
        }

        Vertex* v = fw? e2->getDest() : e2->getOrigin();

        // nodes must be unvisited
        if (v->path == nullptr) {
            v->path = e2;
            const int t = std::min(flow, e2->getFlow());
            shrinkEdge(e2, t, fw);
            flow -= t;
        }
    }
}

/**
 * Remove an edge from a graph in cascade form
 * and calculate change in flow post removal
 *
 * @param g target graph
 * @param e target edge
 * @return added flow post removal
 */
int DataHandler::removeEdgeCascade(Graph& g, Edge* e) {

    int flow = e->getFlow();

    // remove flow in cascade form
    shrinkEdge(e, flow, true);
    e->setFlow(flow);
    shrinkEdge(e, flow, false);

    e->getOrigin()->removeOutEdge(e);

    // put back residual edges
    for (const Vertex* v : g.nodes) {
        for (Edge* e2 : v->out) {
            e2->createResidual();
        }
    }
    return -flow +edmondsKarp(g, g.nodes[0], g.nodes[1]);
}

/**
 * Remove a node from a graph using a cascade method
 * and calculate the change in flow post removal
 *
 * @param g target graph
 * @param v target node
 * @return added flow post removal
 */
int DataHandler::removeNodeCascade(Graph& g, Vertex* v) {

    if (v->out.empty()) return 0;
    v->path = v->out[0]; // mark as visited

    int flow = 0; // flow to be removed

    for (Edge* out : v->out) {
        flow += out->getFlow();
        shrinkEdge(out, out->getFlow(), true);
    }
    for (Edge* in : v->in) {
        shrinkEdge(in, in->getFlow(), false);
    }

    g.removeVertex(*v->getInfo());

    // put back residual edges
    for (const Vertex* v2 : g.nodes) {
        for (Edge* e : v2->out) {
            e->createResidual();
        }
    }
    return -flow +edmondsKarp(g, g.nodes[0], g.nodes[1]);
}
