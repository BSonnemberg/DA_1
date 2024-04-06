#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include "Graph.h"

struct Metrics {
    int maxPipeDiff;
    double pipeVariance;
    double avgPipeRatio;
    double avgDemandMet;
};

/**
 * Provides a bundle of functions to analyze
 * and manage the water supply network graph
 */
class DataHandler {
    static bool findAugmPath(Graph& g, Vertex* s, Vertex* t);
    static bool findDrainPath(Graph& g, Vertex* s, Vertex* t);
    static void balanceNetworkIter(Graph& g);
public:
    static int edmondsKarp(Graph& g);
    static int drainNode(Graph& g, Vertex* v);
    static int drainEdge(Graph& g, Edge* e);
    static Metrics balanceNetwork(Graph& g);
    static Metrics computeMetrics(const Graph& g);
    static std::string printToFile(const Graph& g);
};

#endif
