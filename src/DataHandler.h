#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include "Graph.h"

struct Metrics {
    // pipe metrics
    double pipeVariance;
    double avgPipeRatio;
    int maxPipeDiff;
    // city metrics
    double avgDemandMet;
};

/**
 * Provides a bundle of functions to analyze
 * and manage the water supply network graph
 */
class DataHandler {
    static bool findAugmPath(Graph& g, Vertex* s, Vertex* t);
    static bool findDrainPath(Graph& g, Vertex* s, Vertex* t);
public:
    static int edmondsKarp(Graph& g);
    static int drainNode(Graph& g, Vertex* v);
    static int drainEdge(Graph& g, Edge* e);
    static std::string printToFile(const Graph& g);
    static Metrics computeMetrics(const Graph& g);
};

#endif
