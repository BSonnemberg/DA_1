#include "DataLoader.h"
#include "DataHandler.h"

int main() {
    Graph g;
    if (!DataLoader::loadToGraph(g, "../dataset-large/")) {
        printf("Error loading dataset!");
        return 1;
    }

    printf("Max flow > %d\n\n", DataHandler::edmondsKarp(g));

    Metrics m = DataHandler::computeMetrics(g);
    printf("Average pipe ratio > %f\n", m.avgPipeRatio);
    printf("Pipe variance > %f\n", m.pipeVariance);
    printf("Max pipe difference > %d\n", m.maxPipeDiff);
    printf("Avg demand met > %f\n\n", m.avgDemandMet);

    int i = 0, o = 0;
    for (Vertex* v : g.getNodes()) {
        for (Edge* out : v->getOutEdges()) {
            o += out->getFlow();
        }
        for (Edge* in : v->getInEdges()) {
            i += in->getFlow();
        }
    }
    if (i==o) printf("passed integrity check!\n\n");
    else {
        printf("integrity check failed! (in > %d, out > %d)\n\n", i, o);
    }

    m = DataHandler::balanceNetwork(g);

    printf("\nAverage pipe ratio > %f\n", m.avgPipeRatio);
    printf("Pipe variance > %f\n", m.pipeVariance);
    printf("Max pipe difference > %d\n", m.maxPipeDiff);
    printf("Avg demand met > %f\n\n", m.avgDemandMet);

    i = 0, o = 0;
    for (Vertex* v : g.getNodes()) {
        for (Edge* out : v->getOutEdges()) {
            o += out->getFlow();
        }
        for (Edge* in : v->getInEdges()) {
            i += in->getFlow();
        }
    }
    if (i==o) printf("passed integrity check!\n\n");
    else {
        printf("integrity check failed! (in > %d, out > %d)\n\n", i, o);
    }

    return 0;
}
