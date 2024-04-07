#include "Menu.h"

// todo: make sure edmonds karp has been run before some of the menus

int Menu::open() {

    clear();
    set_cursor(0,0);
    empty_line(2);

    print << GRAY;

    print << "   Welcome to the water supply network!" << newl;
    print << "   Which dataset would you like to work with?" << newl;

    print << newl << "   /1\\ Select small dataset" << newl;
    print << newl << "   /2\\ Select large dataset" << newl;
    print << newl << "   /3\\ Select alternative dataset" << newl;

    print << newl;
    print << newl << "   /Q\\ Quit program" << newl;
    empty_line(3);


    return 0;
}

int Menu::open2(Graph& g) {

    int maxFlow = DataHandler::edmondsKarp(g);

    clear();
    empty_line(100);
    set_cursor(0,0);
    empty_line(3);

    print << GRAY;


    print << "   Maximum flow of > " << maxFlow << newl;
    print << newl;

    for (auto p : g.getCities()) {
        print << "   ";
        int flow = p.first->getOutEdges()[0]->getFlow();
        int demand = p.second->getDemand();
        City* c = p.second;
        print << c->getName();
        print << " (" << c->getCode() << ")";
        print << " gets " << flow << " / " << demand << newl;
    }

    print << newl << "   /P\\ Print to file" << newl;
    print << newl << "   /B\\ Balance the flow" << newl;
    print << newl << "   /Q\\ Back to main menu" << newl;
    empty_line(2);
}

int Menu::open3(Graph &g) {

    Metrics oldMetrics = DataHandler::computeMetrics(g);
    Metrics newMetrics = DataHandler::balanceNetwork(g);
    // todo: make sure to rerun edmonds karp afterward

    clear();
    set_cursor(0,0);
    empty_line(2);

    print << GRAY;

    print << "   Average pipe flow/capacity ratio " << newl << "   ";
    print << oldMetrics.avgPipeRatio << " >>> " << newMetrics.avgPipeRatio << newl;

    print << newl << "   Pipe flow/capacity variance " << newl << "   ";
    print << oldMetrics.pipeVariance << " >>> " << newMetrics.pipeVariance << newl;

    print << newl << "   Max flow-capacity difference " << newl << "   ";
    print << oldMetrics.maxPipeDiff << " >>> " << newMetrics.maxPipeDiff << newl;

    print << newl << "   Average city demand met " << newl << "   ";
    print << oldMetrics.avgDemandMet << " >>> " << newMetrics.avgDemandMet << newl;

    print << newl << newl << "   /Q\\ Back to main menu" << newl;

    empty_line(2);
}

// pipeline removal menu
int Menu::open4(Graph& g, Edge* e) {

    int maxFlow = DataHandler::edmondsKarp(g);
    std::vector<std::pair<City*, int>> oldFlow;

    // save old flow first
    for (auto p : g.getCities()) {
        int flow = p.first->getOutEdges()[0]->getFlow();
        oldFlow.emplace_back(p.second, flow);
    }

    int rem = DataHandler::drainEdge(g, e);
    // temporarily remove edge
    e->getOrigin()->removeOutEdge(e, false);

    for (Vertex* v : g.getNodes()) {
        for (Edge* e : v->getOutEdges()) {
            e->createResidual();
        }
    }

    int added = DataHandler::edmondsKarp(g);
    e->getOrigin()->addOutEdge(e);

    clear();
    set_cursor(0,0);
    empty_line(2);

    print << GRAY;

    print << "Removing edge " << e->getOrigin()->getInfo()->getCode();
    print << " -> " << e->getDest()->getInfo()->getCode() << ":";


    print << newl << newl;

    print << "Old flow > " << maxFlow << ", New flow > " << maxFlow-rem+added;
    print << newl << newl;
    auto p = g.getCities();
    for (int i=0; i<p.size(); i++) {
        int flowN = p[i].first->getOutEdges()[0]->getFlow();
        int flowO = oldFlow[i].second;
        if (flowN != flowO) {
            print << "Flow of " << p[i].second->getName() << " changed from " << flowO << " to " << flowN << "!";
            print << newl << newl;
        }
    }
}

