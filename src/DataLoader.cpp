#include "DataLoader.h"

bool DataLoader::loadToGraph(Graph& g, const std::string& path) {
    try {
        loadStations(g, path);
        loadReservoirs(g, path);
        loadCities(g, path);
        loadPipes(g, path);
    } catch (const std::exception& e) {
        return false;
    }
    return true;
}

void DataLoader::loadStations(Graph& g, const std::string& path) {

    std::string line;
    std::ifstream stream(path+"Stations.csv");
    std::getline(stream , line);

    while (std::getline(stream, line)) {

        if (line.back()=='\r') line.pop_back();
        std::istringstream iss(line);
        std::string id, code;

        // extract data
        std::getline(iss, id, ',');
        std::getline(iss, code, ',');

        // create object
        auto* station = new Station(stoi(id), code);
        g.addVertex(station);
    }
    stream.close();
}

void DataLoader::loadPipes(Graph &g, const std::string &path) {

    std::string line;
    std::ifstream stream(path+"Pipes.csv");
    std::getline(stream , line);

    while (std::getline(stream, line)) {

        if (line.back()=='\r') line.pop_back();
        std::istringstream iss(line);
        std::string c1, c2, cap, dir;

        std::getline(iss, c1, ',');
        std::getline(iss, c2, ',');
        std::getline(iss, cap, ',');
        std::getline(iss, dir, ',');

        // create edge
        g.addEdge(c1, c2, stoi(cap));
        if (dir == "0") { // bidirectional edge
            g.addEdge(c2, c1, stoi(cap));
        }
    }
    stream.close();
}

void DataLoader::loadReservoirs(Graph& g, const std::string& path) {

    std::string line;
    std::ifstream stream(path+"Reservoir.csv");
    std::getline(stream , line);

    while (std::getline(stream, line)) {

        if (line.back()=='\r') line.pop_back();
        std::istringstream iss(line);
        std::string id_, code, name, munic, max_;

        std::getline(iss, name, ',');
        std::getline(iss, munic, ',');
        std::getline(iss, id_, ',');
        std::getline(iss, code, ',');
        std::getline(iss, max_, ',');

        int id = stoi(id_);
        int max = stoi(max_);

        // create obj and add it to graph
        auto* res = new Reservoir(id, code, name, munic, max);
        g.addVertex(res);
    }
    stream.close();
}

void DataLoader::loadCities(Graph& g, const std::string& path) {

    std::string line;
    std::ifstream stream(path+"Cities.csv");
    std::getline(stream , line);

    while (std::getline(stream, line)) {

        if (line.back()=='\r') line.pop_back();
        std::istringstream iss(line);
        std::string id_, code, name, demand_, pop_;

        std::getline(iss, name, ',');
        std::getline(iss, id_, ',');
        std::getline(iss, code, ',');
        std::getline(iss, demand_, ',');
        std::getline(iss, pop_, ',');

        int id = stoi(id_);
        int demand = stoi(demand_);
        int pop = stoi(pop_);

        // create object
        auto* city = new City(id, code, name, demand, pop);
        g.addVertex(city);
    }
    stream.close();
}