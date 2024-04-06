#include "DataHandler.h"
#include <fstream>
#include <queue>

/**
 * @brief Find an augmenting path from a source to a sink node
 * @param g target graph
 * @param s source node
 * @param t sink node
 * @re O(E)
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
 * @brief Perform the edmonds-karp algorithm to find the
 * maximum flow of the water supply network
 *
 * @param g target graph
 * @complexity O(V * E^2)
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
 * @brief Find a path from source to sink where flow can be drained
 * @param g target graph
 * @param s source node
 * @param t sink node
 * @complexity O(E)
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
 * @brief Drain a node by removing flow passing through it from the network
 * @param g target graph
 * @param v node to be drained
 * @complexity O(2*E*V)
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
 * @brief Drain an edge by removing flow going through it from the network
 * @param g target graph
 * @param e edge to be drained
 * @complexity O(2*E*V)
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
 * @brief Print water network supply status to a file
 * @complexity O(c), c -> no. of cities in the graph
 * @param g target graph
 * @return file name
 */
std::string DataHandler::printToFile(const Graph& g) {

    std::time_t t = std::time(nullptr); // get time
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

/**
 * @brief Compute metrics to evaluate performance of the water supply network
 * @complexity O(2*c + 2*E), c -> no. of cities in the graph
 * @param g target graph
 */
Metrics DataHandler::computeMetrics(const Graph& g) {

    Metrics res = {};
    auto cities = g.getCities();

    // compute avg demand met for all cities

    for (auto p : cities) {
        const double demand = p.second->getDemand();
        const double supply = p.first->out[0]->getFlow();
        res.avgDemandMet += supply/demand;
    }
    res.avgDemandMet /= cities.size();

    // calculate basic pipe metrics

    int noPipes = 0;

    for (const Vertex* v : g.getNodes()) {
        for (const Edge* e : v->out) {
            const double x = e->getFlow();
            const int y = e->getCapacity();
            // update max diff
            if (y-x > res.maxPipeDiff) {
                res.maxPipeDiff = y-x;
            }
            res.avgPipeRatio += x/y;
            noPipes++;
        }
    }
    res.avgPipeRatio /= noPipes;

    // compute variance in pipes

    for (const Vertex* v : g.getNodes()) {
        for (const Edge* e : v->out) {
            const double x = e->getFlow();
            const int y = e->getCapacity();
            double z = (x/y) - res.avgPipeRatio;
            res.pipeVariance += z*z;
        }
    }
    res.pipeVariance /= noPipes;
    return res;
}

/**
 * @brief Runs an iteration of a heuristics-based algorithm
 * for balancing flow of a water supply network graph
 * @complexity O(E^2 * 2*V)
 * @param g target graph
 */
void DataHandler::balanceNetworkIter(Graph& g) {

    constexpr double lowerBound = 0.5;
    constexpr double upperBound = 0.84;
    constexpr double midBound = (lowerBound+upperBound)/2.0;

    for (const Vertex* v : g.getNodes()) {
        for (Edge* e : v->getOutEdges()) {

            const double flow = e->getFlow();
            const double ratio = flow / e->getCapacity();

            // find high flow pipes
            if (ratio > upperBound) {

                // temporarily remove edge
                e->getOrigin()->removeOutEdge(e, false);

                Vertex* s = e->getOrigin();
                Vertex* t = e->getDest();

                if (findAugmPath(g, s, t)) {

                    int totalNodes = 1;
                    double avgRatio = 0;
                    const Vertex* current = t;

                    while (current != s) {
                        const Edge* tmp = current->path;
                        // find avg flow/capacity ratio of path
                        // to check if it's "underutilized"
                        const double f = tmp->getFlow();
                        avgRatio += f / tmp->getCapacity();
                        current = current->path->getOrigin();
                        totalNodes++;
                    }

                    avgRatio /= totalNodes;

                    // found underutilized path
                    if (avgRatio < lowerBound) {

                        const int a = e->getFlow() - midBound*e->getCapacity();
                        const int delta = std::min(t->minFlow, a);

                        current = t;
                        while (current != s) {
                            // redirect flow
                            Edge* aux = current->path;
                            aux->setFlow(aux->getFlow() + delta);
                            current = current->path->getOrigin();
                        }
                        e->setFlow(e->getFlow() - delta);
                    }
                }
                e->getOrigin()->addOutEdge(e);
            }
        }
    }
}

/**
 * @brief Balance network load by forcing flow to be
 * rerouted to different pipes using heuristics
 *
 * @complexity best case: O(E^2 * 2*V);
 * worst case: impossible to predict
 *
 * @param g target graph
 * @return metrics after balance
 */
Metrics DataHandler::balanceNetwork(Graph& g) {

    // minimum improvement per iteration
    // to continue balancing process
    constexpr double minStep = 0.003;

    Metrics metrics = computeMetrics(g);
    double delta = minStep;

    while (delta > 0 && delta >= minStep) {
        balanceNetworkIter(g);
        double prev = metrics.pipeVariance;
        metrics = computeMetrics(g);
        delta = prev - metrics.pipeVariance;
    }
    return metrics;
}
