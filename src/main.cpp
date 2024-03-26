#include "DataLoader.h"
#include "DataHandler.h"

int main() {
    Graph g;
    if (!DataLoader::loadToGraph(g, "../dataset-large/")) {
        printf("Error loading dataset!");
        return 1;
    }
    printf("Loaded dataset!\n\n");

    printf("Original max flow > %d\n\n", DataHandler::edmondsKarp(g));
    Graph g2(g);

    for (Vertex* v : g.getNodes()) {
        if (v->getInfo()->getCode()=="R_MASTER") {
            for (Edge* e : v->getOutEdges()) {
                const auto* r = dynamic_cast<Reservoir*>(e->getDest()->getInfo());
                printf("Reservoir %s with flow >> %d / %d\n", e->getDest()->getInfo()->getCode().c_str(), e->getFlow(), e->getCapacity());
            }
        }
    }

    std::string code = "R_21";

    g.removeVertex(NodeInfo(6, code));
    printf("\nMax flow after removal in G > %d\n\n", DataHandler::edmondsKarp(g));

    int a, b;
    a = DataHandler::removeNodeCascade(g2, g2.findVertex(code));
    b = DataHandler::edmondsKarp(g2, false);
    printf("Max flow after cascade in G2 > %d   (rem: %d, added: %d)\n", 24163-a+b, a, b);
    return 0;
}
