#ifndef DATALOADER_H
#define DATALOADER_H

#include "Graph.h"
#include <fstream>
#include <sstream>

class DataLoader {
    /**
     * Load pumping stations from file
     * @param g target graph
     * @param path dataset path
     * @complexity O(n), n -> no. of files
     */
    static void loadStations(Graph& g, const std::string& path);
    /**
     * Load water reservoirs from file
     * @param g target graph
     * @param path dataset path
     * @complexity O(n), n -> no. of files
     */
    static void loadReservoirs(Graph& g, const std::string& path);
    /**
     * Load delivery sites from file
     * @param g target graph
     * @param path dataset path
     * @complexity O(n), n -> no. of files
     */
    static void loadCities(Graph& g, const std::string& path);
    /**
     * Load pipelines from file
     * @param g target graph
     * @param path dataset path
     * @complexity O(n), n -> no. of files
     */
    static void loadPipes(Graph& g, const std::string& path);
public:
    /**
     * Load dataset into a graph
     * @param g target graph
     * @param path dataset path
     * @complexity O(n), n -> total no. of lines of all dataset files
     * @return whether successful
     */
    static bool loadToGraph(Graph& g, const std::string& path);
};

#endif
