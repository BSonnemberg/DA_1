#include "DataHandler.h"

void DataHandler::dfs(Graph &g, const NodeInfo &start, const NodeInfo &end) {
    for (auto v : g.nodes) {
        v->visited = false;
    }
    //...
}
