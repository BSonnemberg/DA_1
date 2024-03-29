#include "DataHandler.h"
#include <fstream>
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

/**
 * Find a path from source to sink where flow can be drained
 * @param g target graph
 * @param s source node
 * @param t sink node
 * @return whether a path was found
 */
bool DataHandler::findDrainPath(Graph& g, Vertex* s, Vertex* t) {

    std::queue<Vertex*> q;
    for(Vertex* v : g.getNodes()) {
        v->path = nullptr;
        v->minFlow = INT_MAX;
    }
    q.push(s);

    while (!q.empty()) {

        Vertex* v = q.front();
        q.pop();

        for (Edge* e : v->out) {

            // only non-residual, non-empty paths
            if (e->getFlow() <= 0) {
                continue;
            }

            Vertex* v2 = e->getDest();
            if (v2->path == nullptr) {
                v2->minFlow = std::min(v->minFlow, e->getFlow());
                v2->path = e;
                q.push(v2);
            }

            if (v2 == t) {
                // found target
                return true;
            }
        }
    }
    return false;
}

/**
 * Drain a node by removing flow passing through it from the network
 * @param g target graph
 * @param v node to be drained
 * @return amount that was drained
 */
int DataHandler::drainNode(Graph& g, Vertex* v) {

    if (v == nullptr) {
        return 0;
    }

    int drained = 0;
    Vertex* src = g.getNodes()[0];
    Vertex* sink = g.getNodes()[1];

    // drain from v -> sink
    while (findDrainPath(g, v, sink)) {

        // bneck -> min flow of path
        const int bneck = sink->minFlow;
        const Vertex* v2 = sink;

        while (v2 != v) {
            v2->path->setFlow(v2->path->getFlow() - bneck);
            v2 = v2->path->getOrigin();
        }
        drained += bneck;
    }

    // drain from src -> v
    while (findDrainPath(g, src, v)) {

        const int bneck = v->minFlow;
        const Vertex* v2 = v;

        while (v2 != src) {
            v2->path->setFlow(v2->path->getFlow() - bneck);
            v2 = v2->path->getOrigin();
        }
    }
    return drained;
}

/**
 * Drain an edge by removing flow going through it from the network
 * @param g target graph
 * @param e edge to be drained
 * @return amount that was drained
 */
int DataHandler::drainEdge(Graph& g, Edge* e) {

    if (e == nullptr) {
        return 0;
    }

    int drained = 0;
    Vertex* start = e->getDest();
    Vertex* end = g.getNodes()[1];

    for (int i=0; i<2; i++) {

        // first drain from e.dest -> sink
        while (findDrainPath(g, start, end)) {

            int bneck = std::min(e->getFlow(), end->minFlow);
            const Vertex* v2 = end;

            while (v2 != start) {
                v2->path->setFlow(v2->path->getFlow() - bneck);
                v2 = v2->path->getOrigin();
            }

            drained += bneck;
            if (drained == e->getFlow()) {
                break;
            }
        }

        // then drain from src -> e.origin
        if (i == 0) {
            start = g.getNodes()[0];
            end = e->getOrigin();
            drained = 0;
        }
    }
    e->setFlow(0);
    return drained;
}

/**
 * Print water network supply status to a file
 * @param g target graph
 * @return file name
 */
std::string DataHandler::printSupplyToFile(Graph& g) {

    std::time_t t = std::time(0); // get time
    std::tm* now = std::localtime(&t);

    std::string y = std::to_string(-100+now->tm_year);
    std::string m = std::to_string(now->tm_mon);
    std::string d = std::to_string(now->tm_mday);

    std::string h = std::to_string(now->tm_hour);
    std::string min = std::to_string(now->tm_min);
    std::string s = std::to_string(now->tm_sec);

    if (m.size() == 1) m = "0" + m;
    if (h.size() == 1) h = "0" + h;
    if (min.size() == 1) min = "0" + min;
    if (s.size() == 1) s = "0" + s;

    std::string file = "log-"+y+"-"+m+"-"+d+"-"+h+":"+min+":"+s+".txt";

    std::ofstream out("../"+file);
    out << "Code / Name / Supply / Demand / % of demand met\n";
    out << "----------------------------------------------\n";
    out << std::fixed << std::setprecision(1);

    for (auto p : g.getCities()) {

        City* c = p.second;
        double supply = p.first->out[0]->getFlow();

        out << c->getCode() << " / ";
        out << c->getName() << " / ";
        out << (int) supply << " / ";
        out << c->getDemand() << " / ";
        out << 100 * (supply / c->getDemand()) << "%\n";
    }
    out.close();
    return file;
}
