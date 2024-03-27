#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include "Graph.h"

/**
 * Provides a bundle of functions to analyze
 * and manage the water supply network graph
 */
class DataHandler {
    static bool findAugmPath(Graph& g, Vertex* s, Vertex* t);
    static int edmondsKarp(Graph& g, Vertex* src, Vertex* sink);
    static void shrinkEdge(Edge* e, int flow, const int& fw);
public:
    static int getMaxFlow(Graph& g);
    static int removeEdg(Graph& g, Vertex* v);
};

#endif
