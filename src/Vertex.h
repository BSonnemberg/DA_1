#ifndef VERTEX_H
#define VERTEX_H

#include <vector>
#include "Reservoir.h"
#include "Station.h"
#include "City.h"

class Edge;

/**
 * NodeInfo is immutable - to avoid allocating memory
 * for it when copying a graph, a sharedptr is used
 */
typedef std::shared_ptr<NodeInfo> NodeInfoPtr;

class Vertex {
    NodeInfoPtr info;
    std::vector<Edge*> out;
    std::vector<Edge*> in;
    // utilities
    Edge* path;
    int bneck;
    int flow;
    //...
    void addEdgeTo(Vertex* v, const int& cap, const int& flow=0);
    bool removeEdgeTo(Vertex* v);
    friend class Graph;
    friend class DataLoader;
    friend class DataHandler;
public:
    ~Vertex();
    explicit Vertex(const NodeInfoPtr& info);
    const std::vector<Edge*>& getOutEdges() const;
    const std::vector<Edge*>& getInEdges() const;
    NodeInfo* getInfo() const;
    int getFlow() const;
};

#endif
