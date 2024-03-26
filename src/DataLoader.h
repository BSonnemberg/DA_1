#ifndef DATALOADER_H
#define DATALOADER_H

#include "Graph.h"
#include <fstream>
#include <sstream>

class DataLoader {
    static void loadStations(Graph& g, const std::string& path);
    static void loadReservoirs(Graph& g, const std::string& path);
    static void loadCities(Graph& g, const std::string& path);
    static void loadPipes(Graph& g, const std::string& path);
public:
    /**
     * Load dataset into a graph
     * @param g target graph
     * @param path dataset path
     * @return whether successful
     */
    static bool loadToGraph(Graph& g, std::string path);
};

#endif
