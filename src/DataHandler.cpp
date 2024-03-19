#include "DataHandler.h"
#include <queue>

// return true if a path was found

// 1. start by setting visited=false?? and parent to nullptr

// 2. start the queueing process

// 3. for every edge, if there's remaining flow and !visited? (aka parent is nullptr (!))
// then set parent, and have a minimum value for each vertex that is set aswell

// 3X. (besides that, we need to make sure that we don't exceed the max delivery of the source)
// maybe have another property of vertex that saves its source? and from then always check

// 4. if the target vertex is found, break, else add edge dest aka v2 to queue

// theres no need to store the source for each node
// only exception for the max delovery is that when we find a source node we min it with the current min


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
            // check if max delivery
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
