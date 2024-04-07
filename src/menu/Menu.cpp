#include "Menu.h"
#include <iomanip>
#include <iostream>

#define SEL (FGROUND(238) + BGROUND(248))
#define SEL_ALT BGROUND(210)

// print selection line
void printSelection(const std::string& idx, const std::string& text, const std::string& color) {
    print << RESET << "   ";
    print << color << " " << BOLD << "/" << idx << "\\";
    print << RESET << color << " " << text << " " << RESET;
}

// menu used to select dataset
void Menu::openDatasetMenu(Graph& g, std::string& dataset) {

    clear();
    set_cursor(0,0);
    empty_line(2);

    int control;

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
    printSelection("0", " Quit program", SEL_ALT);
    empty_line(3);

    print << GRAY << ITALIC;
    std::cin >> control;

    switch(control){
        case 1:{        //DATASET-SMALL
            dataset = "dataset-small";
            break;
        }
        case 2:{        //DATASET-LARGE
            dataset = "dataset-large";
            break;
        }
        case 3:{        //CUSTOM DATASET
            print << "Enter path > ";
            std::cin >> dataset;
            print << RESET;
            break;
        }
        case 0:{        //EXIT
            exit(0);
        }
        default:{break;}
    }

}

// main interface
void Menu::openMainMenu(Graph& g) {

    clear();
    set_cursor(0,0);
    empty_line(2);

    int ctrl;

    print << GRAY;
    print << "   Your dataset has been loaded!" << newl;
    print << "   Choose one of the options below.";

    empty_line(2);
    printSelection("1,<node>", "Effect of node removal", SEL);

    empty_line(2);
    printSelection("2,<pipe>", "Effect of pipe removal", SEL);

    empty_line(2);
    printSelection("3", "Calculate maximum flow", SEL);

    empty_line(3);
    printSelection("0", "Quit program", SEL_ALT);
    empty_line(3);

    print << GRAY << ITALIC;
    std::cin >> ctrl;

    switch (ctrl) {
        case 1:{        // NODE REMOVAL
            std::string node;
            printf("Enter node code > ");
            std::cin >> node;
            for(auto a: g.getNodes()){
                if (a->getInfo()->getCode()==node){
                    openNodeRemovalMenu(g, a);
                }
            }
            printf("Invalid, retry > ");
            break;
        }
        case 2:{        //EDGE REMOVAL
            std::string origin, dest;
            printf("Enter pipe source > ");
            std::cin >> origin;
            printf("Enter pipe destination > ");
            std::cin >> dest;
            for(auto a: g.getNodes()){
                for (auto e: a->getOutEdges()){
                    if (e->getOrigin()->getInfo()->getCode()==origin){
                        for (auto d: e->getOrigin()->getOutEdges()){
                            if(d->getDest()->getInfo()->getCode()==dest){
                                openPipeRemovalMenu(g, d);
                            }
                        }
                    }
                }

            }
            printf("Invalid pipe, ");
            break;
        }


        case 3:{        //MAX FLOW
            openFlowMenu(g);
            break;
        }
        case 0:{        //EXIT
            exit(0);
        }
        default:{break;}
    }
}

// menu used to display maximum flow
void Menu::openFlowMenu(Graph& g) {
    Graph gC = g;
    int maxFlow = DataHandler::edmondsKarp(g);
    int ctrl;

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
    printSelection("1", "Print to file", SEL);

    print << " ";
    printSelection("2", "Balance the flow", SEL);

    print << " ";
    printSelection("0", "Back to Main Menu", SEL_ALT);

    empty_line(3);

    print << GRAY << ITALIC;
    std::cin >> ctrl;

    switch (ctrl) {
        case 1:{        //PRINT TO FILE
            DataHandler::printToFile(g);
            break;
        }
        case 2:{        //BALANCE FLOW
            openBalanceMenu(g);
            break;
        }
        case 0:{    //RETURN TO MAIN MENU
            openMainMenu(gC);
            break;
        }
        default:{break;}
    }
}

// menu used to show before/after balancing metrics
void Menu::openBalanceMenu(Graph &g) {
    Graph gC = g;
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
    printSelection("0", "Back to Main Menu", SEL_ALT);
    empty_line(3);

    print << GRAY << ITALIC;
    int ctrl;
    std::cin >> ctrl;

    switch (ctrl) {
        case 0:{        //RETURN TO MAIN MENU
            openMainMenu(gC);
            break;
        }
        default:{break;}
    }
}

// menu used to show effect of removing a pipe
void Menu::openPipeRemovalMenu(Graph& g, Edge* e) {
    Graph gC = g;
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
    std::string k1 = "...", k2 = "...";
    switch (e->getOrigin()->getInfo()->getType()) {
        case WATER_RESERVOIR:
            k1 = "Reservoir";
        break;
        case PUMPING_STATION:
            k1 = "Station";
        break;
        case DELIVERY_SITE:
            k1 = "City";
    }
    switch (e->getDest()->getInfo()->getType()) {
        case WATER_RESERVOIR:
            k2 = "Reservoir";
        break;
        case PUMPING_STATION:
            k2 = "Station";
        break;
        case DELIVERY_SITE:
            k2 = "City";
    }

    clear();
    set_cursor(0,0);
    empty_line(2);

    print << GRAY;
    print << "   After removing pipe from " << BOLD;
    print << k1 << " #" << e->getOrigin()->getInfo()->getId() << RESET << GRAY;
    print << " -> " << BOLD << k2 << " #" << e->getDest()->getInfo()->getId();
    print << RESET << GRAY << ":" << newl;

    int a = 0;
    auto p= g.getCities();

    for (int i=0; i<p.size(); i++) {
        City* c = p[i].second;
        int flowAfter = p[i].first->getOutEdges()[0]->getFlow();
        int flowBefore = oldFlow[i];
        int demand = c->getDemand();
        if (flowBefore != flowAfter) {
            print << newl;
            std::string color = (flowBefore > flowAfter) ? RED : (flowAfter==flowBefore) ? LIGHT_WHITE : GREEN;
            print << color << "   ";
            std::string x = std::to_string(flowAfter-flowBefore);
            int spaces = 13- (3+x.size());
            if (flowAfter > flowBefore) {
                print << "+";
                spaces--;
            }
            print << x;
            print << std::string(spaces, ' ');

            std::string y = "Δ=" + std::to_string(demand-flowAfter) + "";
            if (flowAfter < demand) {
                print << FGROUND(25) << ITALIC << "Δ=" << demand-flowAfter << "";
            } else print << LIGHT_WHITE << ITALIC << "Δ=0";
            spaces = 9 - y.size();
            print << std::string(spaces, ' ');

            print << GRAY << BOLD " " << c->getCode() << " aka. " << c->getName();
            print << RESET << GRAY << " now gets " << flowAfter << "/" << demand;
            a++;
        }
    }

    empty_line(3);
    printSelection("0", "Back to Main Menu", SEL_ALT);
    empty_line(3);

    print << GRAY << ITALIC;
    int ctrl;
    std::cin >> ctrl;

    switch (ctrl) {
        case 0:{        //RETURN TO MAIN MENUU
            openMainMenu(gC);
        }
        default:{break;}
    }
}

// menu used to show effect of removing a node
void Menu::openNodeRemovalMenu(Graph& g, Vertex* v) {
    Graph gC = g;
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

    clear();
    set_cursor(0,0);
    empty_line(2);

    print << GRAY;
    print << "   After removing " << BOLD << k << " #";
    print << v->getInfo()->getId() << RESET << GRAY << ":";

    empty_line(1);

    int a = 0;
    auto p= g.getCities();

    for (int i=0; i<p.size(); i++) {
        City* c = p[i].second;
        int flowAfter = p[i].first->getOutEdges()[0]->getFlow();
        int flowBefore = oldFlow[i];
        int demand = c->getDemand();
        if (flowBefore != flowAfter) {
            print << newl;
            std::string color = (flowBefore > flowAfter) ? RED : (flowAfter==flowBefore) ? LIGHT_WHITE : GREEN;
            print << color << "   ";
            std::string x = std::to_string(flowAfter-flowBefore);
            int spaces = 13 - (3+x.size());
            if (flowAfter > flowBefore) {
                print << "+";
                spaces--;
            }
            print << x;
            print << std::string(spaces, ' ');

            std::string y = "Δ=" + std::to_string(demand-flowAfter) + "";
            if (flowAfter < demand) {
                print << FGROUND(25) << ITALIC << "Δ=" << demand-flowAfter << "";
            } else print << LIGHT_WHITE << ITALIC << "Δ=0";
            spaces = 9 - y.size();
            print << std::string(spaces, ' ');

            print << GRAY << BOLD " " << c->getCode() << " aka. " << c->getName();
            print << RESET << GRAY << " now gets " << flowAfter << "/" << demand;
            a++;
        }
    }


    if (a == 0) {
        print << newl;
        print << ITALIC << "   No cities were affected by this change!";
    }

    empty_line(3);
    printSelection("0", "Back to Main Menu", SEL_ALT);
    empty_line(3);

    print << GRAY << ITALIC;
    int ctrl;
    std::cin>>ctrl;

    switch (ctrl) {
        case 0:{        //RETURN TO MAIN MENU
            openMainMenu(gC);
        }
        default:{break;}
    }
}