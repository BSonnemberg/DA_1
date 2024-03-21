#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include "Graph.h"

/**
 * Provides a bundle of functions to analyze
 * and manage the water supply network graph
 */
class DataHandler {
    static bool findAugmPath(Graph& g, Vertex* src, Vertex* sink);
public:
    static int edmondsKarp(Graph& g);
    static std::vector<std::pair<City*, int>> undersuppliedCities(Graph& g);
};

#endif
