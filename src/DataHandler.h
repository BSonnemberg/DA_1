#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include "Graph.h"

/**
 * Stores metric data regarding the
 * current state of the supply network
 */
struct Metrics {
    int maxPipeDiff;
    double pipeVariance;
    double avgPipeRatio;
    double avgDemandMet;
};

// flow before v. after an algorithm
struct CityStat {
    City* city;
    int oldFlow;
    int newFlow;
};

/**
 * Provides a bundle of functions to analyze
 * and manage the water supply network graph
 */
class DataHandler {
    static bool findAugmPath(Graph& g, Vertex* s, Vertex* t);
    static bool findDrainPath(Graph& g, Vertex* s, Vertex* t);
    static void balanceNetworkIter(Graph& g);
    static int drainNode(Graph& g, Vertex* v);
    static int drainEdge(Graph& g, Edge* e);
public:
    static int edmondsKarp(Graph& g);
    static Metrics balanceNetwork(Graph& g);
    static std::vector<CityStat> testNodeRemoval(Graph& g, Vertex* v);
    static std::vector<CityStat> testPipeRemoval(Graph& g, Edge* e);
    // metrics and logs
    static Metrics computeMetrics(const Graph& g);
    static std::string printToFile(const Graph& g);
};

#endif