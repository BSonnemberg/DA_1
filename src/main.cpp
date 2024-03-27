#include "DataLoader.h"
#include "DataHandler.h"

int mainTEST(std::string LINE) {
    Graph g;
    if (!DataLoader::loadToGraph(g, "../dataset-large/")) {
        printf("Error loading dataset!");
        return 1;
    }
    //printf("Loaded dataset!\n\n\n");
    int a = DataHandler::getMaxFlow(g);
    //printf("Max flow > %d\n", a);

    Graph g2(g);
    Graph g3(g);

    std::istringstream iss(LINE);
    std::string c1, c2, X, Y;
    // std::getline(iss, X, ',');
    // std::getline(iss, Y, ',');

    std::getline(iss, c1, ',');
    std::getline(iss, c2, ',');

    // Vertex* v = g2.findVertex(c1);
    // int b = DataHandler::removeNodeCascade(g2, v);
    // // printf("New flow OUR METHOD > %d\n\n", a+b);
    //
    // // for (Vertex* vaux : g3.getNodes()) {
    // //     if (*vaux->getInfo() == NodeInfo(0, "R_4")) {
    // //         int flowA = 0;
    // //         for (Edge* ee : vaux->getOutEdges()) flowA += ee->getFlow();
    // //         printf("Truth has flow >> %d\n", flowA);
    // //     }
    // // }
    // g3.removeVertex(NodeInfo(0, c1));
    // int z = DataHandler::getMaxFlow(g3);
    // // printf("New flow truth > %d\n", z);







    Vertex* v1 = g.findVertex(c1);
    Vertex* v2 = g.findVertex(c2);
    Edge* targetEdge = nullptr;

    for (Edge* findingE : v1->getOutEdges()) {
        if (findingE->getDest()==v2) targetEdge = findingE;
    }

    Vertex* v1_g2 = g2.findVertex(c1);
    Vertex* v2_g2 = g2.findVertex(c2);
    Edge* targetEdge_g2 = nullptr;

    for (Edge* findingE : v1_g2->getOutEdges()) {
        if (findingE->getDest()==v2_g2) targetEdge_g2 = findingE;
    }

    int b = DataHandler::removeEdgeCascade(g, targetEdge);
    //printf("Using our method > %d\n", a+b);

    v1_g2->removeOutEdge(targetEdge_g2);
    int z = DataHandler::getMaxFlow(g2);
    //printf("Using their method > %d\n", z);
    // if (a+b != z) {
    //     printf("DEU MERDA EM EDGE de %s para %s (true > %d, fodeu > %d, dif > %d)\n", v->getInfo()->getCode().c_str(), v2->getInfo()->getCode().c_str(), a+b, z, a+b-z);
    // }
    return a+b == z;
}

int main() {

    bool VAIDARCERTO = true;

    std::string line;
    std::ifstream stream("../dataset-large/Pipes.csv");
    std::getline(stream , line);

    while (std::getline(stream, line)) {

        if (line.back()=='\r') line.pop_back();
        if (!mainTEST(line)) VAIDARCERTO = false;
    }

    if (VAIDARCERTO) {
        printf("Ai caralho deu tudo certo aaaaaaaaaa! FESTEJAR");
    }
    else printf("ESTAMOS TOTALMENTE FODIDOS E QUERO ME MATAR CHAMA 112 FDS");
    return 0;
}