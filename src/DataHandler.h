#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include "Graph.h"

/**
 * Provides a bundle of functions to analyze
 * and manage the water supply network graph
 */
class DataHandler {
    static void dfs(Graph& g, const NodeInfo& start, const NodeInfo& end);
public:
    static void maxFlow(Graph& g);
};

#endif
