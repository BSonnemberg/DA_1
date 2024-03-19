#include "DataHandler.h"
#include <queue>

bool DataHandler::findAugmPath(Graph &g, Vertex* src, Vertex* dest) {

    std::vector<Vertex*> res;
    std::queue<Vertex*> q;

    for (auto v : g.nodes) {
        v->parent = nullptr;
        v->bottleneck = INT_MAX;
    }
    q.push(src);


    // start bfs search
    while (!q.empty()) {

        Vertex *v = q.front();
        q.pop();

        if (v == dest) {
            // found target
            break;
        }

        NodeType t = v->getInfo()->getType();
        if (t == NodeType::WATER_RESERVOIR) {
            auto *r = static_cast<Reservoir *>(v->getInfo());
            printf("%d\n", r->getMaxDelivery());
            continue;
        }

       for (Edge e : v->adj) {
            if (e.isAtCapacity()) {
                // pipe at capacity, skip
                continue;
            }
            Vertex* v2 = e.getDest();
            if (v2->parent == nullptr
            ) {
                q.push(v2);
                v2->parent = v;
            }
        }
    }
    return false;
}
