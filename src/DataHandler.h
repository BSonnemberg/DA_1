#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include "Graph.h"

/**
 * Provides a bundle of functions to analyze
 * and manage the water supply network graph
 */
class DataHandler {
    bool findAugmPath(Graph &g, Vertex* src, Vertex* dest);
};

#endif
