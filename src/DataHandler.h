#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include "Graph.h"

/**
 * Provides a bundle of functions to analyze
 * and manage the water supply network graph
 */
class DataHandler {
    static int edmondsKarp(Graph& g, Vertex* src, Vertex* sink);
    static bool findAugmPath(Graph& g, Vertex* s, Vertex* t);
    static void removeEdgeCascade(Edge* e, int flow);
public:
    static int getMaxFlow(Graph& g);
};

#endif
