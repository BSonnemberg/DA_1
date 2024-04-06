#include "DataLoader.h"
#include "DataHandler.h"

int test(const std::string& path, const std::string &p1, const std::string &p2) {
    Graph g;
    if (!DataLoader::loadToGraph(g, path)) {
        printf("Error loading dataset!\n");
        return 1;
    }
    int flow = DataHandler::edmondsKarp(g);

    Edge* e1 =  nullptr;
    for (Vertex* v : g.getNodes()) {
        if (v->getInfo()->getCode() == p1) {
            for (Edge* e : v->getOutEdges()) {
                if (e->getDest()->getInfo()->getCode() == p2) {
                    e1 = e;
                }
            }
        }
    }
    if (e1 == nullptr) printf("error finding edge g, what?\n");

    Graph g2(g);

    Edge* e2 =  nullptr;
    for (Vertex* v : g2.getNodes()) {
        if (v->getInfo()->getCode() == p1) {
            for (Edge* e : v->getOutEdges()) {
                if (e->getDest()->getInfo()->getCode() == p2) {
                    e2 = e;
                }
            }
        }
    }
    if (e2 == nullptr) printf("error finding edge g2, what?\n");


    // regular method
    g2.findVertex(p1)->removeEdgeTo(e2->getDest());
    int NORMAL = DataHandler::edmondsKarp(g2);

    // sus method
    int DRAINED = DataHandler::drainEdge(g, e1);

    // temp remove edge
    e1->getOrigin()->removeOutEdge(e1, false);

    for (Vertex* v : g.getNodes()) {
        for (Edge* e : v->getOutEdges()) {
            e->createResidual();
        }
    }

    int ADDED = DataHandler::edmondsKarp(g);

    //put back edge
    e1->getOrigin()->addOutEdge(e1);

if (NORMAL != (flow-DRAINED+ADDED)) {
    printf("fodeu totalmente  %s -> %s!   (normal > %d)  (drained > %d, added > %d, final > %d)    DIFF > %d\n", p1.c_str(), p2.c_str(),NORMAL, DRAINED, ADDED, flow-DRAINED+ADDED, NORMAL - (flow-DRAINED+ADDED));
}
    return (NORMAL != (flow-DRAINED+ADDED));
}

// int test(const std::string& path, const std::string &p1) {
//     Graph g;
//     if (!DataLoader::loadToGraph(g, path)) {
//         printf("Error loading dataset!\n");
//         return 1;
//     }
//     int flow = DataHandler::edmondsKarp(g);
//
//
//     Vertex* v1 = g.findVertex(p1);
//     if (v1 == nullptr) {
//         printf("NOT FOUND VERTEX!");
//         return 1;
//     }
//
//     int in = 0, out = 0;
//     for (Edge* e : v1->getOutEdges()) {
//         out += e->getFlow();
//     }
//     for (Edge* e : v1->getInEdges()) {
//         in += e->getFlow();
//     }
//
//     Graph g2(g);
//     Vertex* v2 = g2.findVertex(p1);
//
//
//     // regular method
//     g2.removeVertex(*v2->getInfo());
//     int NORMAL = DataHandler::edmondsKarp(g2);
//
//     // sus method
//     int DRAINED = DataHandler::drainNode(g, v1);
//
//     if (DRAINED != out || out != in || DRAINED != in) {
//         printf("WTF, drained != out ????!\n");
//     }
//
//     // temp remove edge
//     const char* vtx = v1->getInfo()->getCode().c_str();
//     g.removeVertex(*v1->getInfo());
//     //e1->getOrigin()->removeOutEdge(e1, false);
//
//     for (Vertex* v : g.getNodes()) {
//         for (Edge* e : v->getOutEdges()) {
//             e->createResidual();
//         }
//     }
//
//     int ADDED = DataHandler::edmondsKarp(g);
//
//     //put back edge
//     //e1->getOrigin()->addOutEdge(e1);
//
//     if (NORMAL != (flow-DRAINED+ADDED)) {
//         printf("fodeu totalmente  %s!   (normal > %d)  (tbd > %d,  drained > %d, added > %d, final > %d)     ->> DIF > %d\n", vtx, NORMAL, out, DRAINED, ADDED, flow-DRAINED+ADDED, NORMAL-(flow-DRAINED+ADDED));
//     }
//     return (NORMAL != (flow-DRAINED+ADDED));
// }

int main() {
    bool working = 0;

    std::string path = "../dataset-small/";

    std::string line;
    std::ifstream stream(path+"/Cities.csv");
    std::getline(stream , line);

    while (std::getline(stream, line)) {

        if (line.back()=='\r') line.pop_back();
        std::istringstream iss(line);
        std::string a, b, c, d;

        // extract data
        std::getline(iss, a, ',');
        std::getline(iss, b, ',');
        std::getline(iss, c, ',');
        std::getline(iss, d, ',');

        working |= test(path, a, b);
    }

    if (!working) printf("deu certo caralhoooooooooooo!!!!\n");

    return 0;
}

// int main() {
//     Graph g;
//     if (!DataLoader::loadToGraph(g, "../dataset-small/")) {
//         printf("Error loading dataset!");
//         return 1;
//     }
//     printf("Max flow > %d\n", DataHandler::edmondsKarp(g));
//     return 0;
// }
