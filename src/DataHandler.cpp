#include "DataHandler.h"
#include <queue>

bool DataHandler::findAugmPath(Graph &g, Vertex* src, Vertex* dest) {

    std::vector<Vertex*> res;
    std::queue<Vertex*> q;

    for (auto v : g.nodes) {
        v->visited = false;
        v->parent = nullptr;
    }
    q.push(src);
    src->visited = true;

    // start bfs search
    while (!q.empty()) {

        Vertex* v = q.front();
        q.pop();

        if (v == dest) {
            // found target
            break;
        }

        NodeType t = v->getInfo().getType();
        if (t == NodeType::WATER_RESERVOIR) {
            auto* r = static_cast<Reservoir*>(v->getInfo());
            continue;
        }

        for (Edge e : v->adj) {
            if (e.isAtCapacity()) {
                // pipe at capacity, skip
                continue;
            }
            Vertex* v2 = e.getDest();
            if (!v2->visited) {
                q.push(v2);
                v2->visited = true;
                v2->parent = v;
            }
        }
    }
    // reconstruct path
    if (dest->visited) {
        Vertex* current = dest;
        while (current->parent != nullptr) {
            res.push_back(current);
            current = current->parent;
        }
        std::reverse(res.begin(), res.end());
    }
    return res;
}
