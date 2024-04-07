#include "Menu.h"
#include <iomanip>

#define SEL (FGROUND(238) + BGROUND(248))
#define SEL_ALT BGROUND(210)

// print selection line
void printSelection(const std::string& idx, const std::string& text, const std::string& color) {
    print << RESET << "   ";
    print << color << " " << BOLD << "/" << idx << "\\";
    print << RESET << color << " " << text << " " << RESET;
}

// menu used to select dataset
int Menu::openDatasetMenu() {

    clear();
    set_cursor(0,0);
    empty_line(2);

    print << GRAY;
    print << "   🌊 Welcome to the ";
    print << BOLD << "water supply network";
    print << RESET << GRAY << "!" << newl;
    print << "   Which dataset would you like to work with?";

    empty_line(2);
    printSelection("1", "Select small dataset", SEL);

    empty_line(2);
    printSelection("2", "Select large dataset", SEL);

    empty_line(2);
    printSelection("3", "Select alternative dataset", SEL);

    empty_line(3);
    printSelection("Q", " Quit program", SEL_ALT);

    empty_line(3);
    return 0;
}

// menu used to display maximum flow
int Menu::openFlowMenu(Graph& g) {

    int maxFlow = DataHandler::edmondsKarp(g);

    clear();
    empty_line(100);
    set_cursor(0,0);
    empty_line(2);

    for (auto p : g.getCities()) {
        const City* c = p.second;
        int demand = c->getDemand();
        int flow = p.first->getOutEdges()[0]->getFlow();
        // print flow and demand for all cities
        print << GRAY << BOLD "   " << c->getCode() << " aka. " << c->getName();
        print << RESET << GRAY << " gets " << flow << "/" << demand;
        if (flow < demand) {
            print << FGROUND(25) << ITALIC << " (Δ=" << demand-flow << ")";
        }
        print << newl;
    }

    print << newl << GRAY << ITALIC;
    print << "   ^ scroll up if necessary ^ " << newl << RESET << GRAY;
    print << "   Maximum network flow -> " << maxFlow << " (m³/s)";

    empty_line(2);
    printSelection("P", "Print to file", SEL);

    print << " ";
    printSelection("B", "Balance the flow", SEL);

    print << " ";
    printSelection("Q", "Back to Main Menu", SEL_ALT);

    empty_line(3);
    return 0;
}

// menu used to show before/after balancing metrics
int Menu::openBalanceMenu(Graph &g) {

    Metrics oldMetrics = DataHandler::computeMetrics(g);
    Metrics newMetrics = DataHandler::balanceNetwork(g);

    clear();
    set_cursor(0,0);
    empty_line(2);

    print << GRAY << ITALIC;
    print << "   (ran flow balancing method)" << newl;
    print << RESET << GRAY;
    print << "   Before v. after network metrics:";

    empty_line(2);
    print << std::fixed << std::setprecision(2);
    print << "   Flow/capacity ratio, on average" << newl << "   ";

    double avg1 = oldMetrics.avgPipeRatio;
    double avg2 = newMetrics.avgPipeRatio;
    print << ((avg1 > avg2) ? RED : (avg2 > avg1) ? GREEN : LIGHT_WHITE);
    print << BOLD << 100*avg1 << "% -> " << 100*avg2 << "%";

    empty_line(2);
    print << std::fixed << std::setprecision(5) << RESET << GRAY;
    print << "   Flow/capacity variance, σ₂" << newl << "   ";

    const double var1 = oldMetrics.pipeVariance;
    const double var2 = newMetrics.pipeVariance;
    print << ((var1 > var2) ? GREEN : (var2 > var1) ? RED : LIGHT_WHITE);
    print << BOLD << 100*var1 << " -> " << 100*var2;

    empty_line(2);
    print << RESET << GRAY;
    print << "   Max flow-capacity difference" << newl << "   ";

    const int diff1 = oldMetrics.maxPipeDiff;
    const int diff2 = newMetrics.maxPipeDiff;
    print << ((diff1 > diff2) ? GREEN : (diff2 > diff1) ? RED : LIGHT_WHITE);
    print << BOLD << diff1 << " -> " << diff2;

    empty_line(2);
    print << std::fixed << std::setprecision(2) << RESET << GRAY;
    print << "   City demand met, on average" << newl << "   ";

    avg1 = oldMetrics.avgDemandMet;
    avg2 = newMetrics.avgDemandMet;
    print << ((avg1 > avg2) ? RED : (avg2 > avg1) ? GREEN : LIGHT_WHITE);
    print << BOLD << 100*avg1 << "% -> " << 100*avg2 << "%";

    empty_line(3);
    printSelection("Q", "Back to Main Menu", SEL_ALT);

    empty_line(3);
    return 0;
}

// menu used to show effect of removing a pipe
int Menu::openPipeRemovalMenu(Graph& g, Edge* e) {

    int maxFlow = DataHandler::edmondsKarp(g);
    std::vector<int> oldFlow;

    // save old flow first
    for (auto p : g.getCities()) {
        int flow = p.first->getOutEdges()[0]->getFlow();
        oldFlow.emplace_back(flow);
    }

    int removed = DataHandler::drainEdge(g, e);

    // temporarily remove edge
    e->getOrigin()->removeOutEdge(e, false);

    // temporarily put back residual edges
    for (Vertex* v : g.getNodes()) {
        for (Edge* e : v->getOutEdges()) {
            e->createResidual();
        }
    }

    int added = DataHandler::edmondsKarp(g);
    e->getOrigin()->addOutEdge(e);

    int newFlow = maxFlow - removed + added;

    //-- start of actual interface
    clear();
    set_cursor(0,0);
    empty_line(2);

    print << GRAY;
    print << "   By removing a pipe from " << BOLD;
    print << e->getOrigin()->getInfo()->getCode() << RESET << GRAY;
    print << " -> " << BOLD << e->getDest()->getInfo()->getCode();
    print << RESET << GRAY << ":";

    empty_line(2);
    int a = 0;

    auto p= g.getCities();
    for (int i=0; i<p.size(); i++) {
        int flowN = p[i].first->getOutEdges()[0]->getFlow();
        int flowO = oldFlow[i];
        if (flowN != flowO) {
            print << "   📉 Flow of " << p[i].second->getName() << " changed from " << flowO << " to " << flowN << "!";
            print << newl << newl;
            a++;
        }
    }

    if (a == 0) {
        print << ITALIC << "   No cities affected by this change!";
    }

    empty_line(3);
    printSelection("Q", "Back to Main Menu", SEL_ALT);
    empty_line(3);
    return 0;
}

// menu used to show effect of removing a node
int Menu::openNodeRemovalMenu(Graph& g, Vertex* v) {

    int maxFlow = DataHandler::edmondsKarp(g);
    std::vector<int> oldFlow;

    // save old flow first
    for (auto p : g.getCities()) {
        int flow = p.first->getOutEdges()[0]->getFlow();
        oldFlow.emplace_back(flow);
    }

    int removed = DataHandler::drainNode(g, v);

    // temporarily remove node and associated edges
    std::vector<Edge*> edges;
    for (Edge* e : v->getOutEdges()) {
        edges.push_back(e);
    }
    for (Edge* e : v->getInEdges()) {
        edges.push_back(e);
    }
    g.removeVertex(*v->getInfo(), false);

    // temporarily put back residual edges
    for (Vertex* v : g.getNodes()) {
        for (Edge* e : v->getOutEdges()) {
            e->createResidual();
        }
    }

    int added = DataHandler::edmondsKarp(g);

    // put back node and edges (restore graph)
    g.addVertex(v);
    for (Edge* e : edges) {
        e->getOrigin()->addOutEdge(e);
    }

    //-- actual start of interface
    std::string k = "...";
    switch (v->getInfo()->getType()) {
        case WATER_RESERVOIR:
            k = "Reservoir";
            break;
        case PUMPING_STATION:
            k = "Pumping Station";
            break;
        case DELIVERY_SITE:
            k = "Delivery Site";
    }

    int a = 0;
    auto p= g.getCities();
    for (int i=0; i<p.size(); i++) {
        int flowN = p[i].first->getOutEdges()[0]->getFlow();
        int flowO = oldFlow[i];
        if (flowN != flowO) {
            print << " Flow of " << p[i].second->getName() << " changed from " << flowO << " to " << flowN << "!";
            print << newl;
            a++;
        }
    }

    empty_line(3);
    printSelection("Q", "Back to Main Menu", SEL_ALT);
    empty_line(3);
    return 0;
}

