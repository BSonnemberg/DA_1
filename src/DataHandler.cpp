#include "DataHandler.h"
#include <queue>

void DataHandler::dfs(Graph &g, const NodeInfo &start, const NodeInfo &end) {
    std::queue<Vertex*> q;
    for (auto v : g.nodes) {
        v->visited = false;
    }
    //...
}

void DataHandler::maxFlow(Graph &g) {
    Graph gCopy(g);
    //...
}
