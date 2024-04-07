#ifndef GRAPH_H
#define GRAPH_H

#include "Edge.h"

class Graph {
    std::vector<Vertex*> nodes;
    Vertex* addVertex(NodeInfo* i);
    /* since all operations are meant to be executed directly
     * on the original graph, without a need for copies, the
     * max flow is cached and can be invalidated */
    int maxFlow = -1;
    friend class DataHandler;
public:
    ~Graph();
    Graph();
    Graph(const Graph& g);
    const std::vector<Vertex*>& getNodes() const;
    std::vector<std::pair<Vertex*, City*>> getCities() const;
    Vertex* findVertex(const std::string& code) const;
    Vertex* findVertex(const NodeInfo& info) const;
    bool addVertex(Vertex* v);
    Vertex* addVertex(Reservoir* i);
    Vertex* addVertex(Station* i);
    Vertex* addVertex(City* i);
    bool removeVertex(const NodeInfo& info, const bool& freeMem = true);
};

#endif
