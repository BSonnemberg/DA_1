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
        Station station(stoi(id), code);
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
        g.addEdge(c1, c2, stof(cap));
        if (dir == "1") { // bidirectional edge
            g.addEdge(c2, c1, stof(cap));
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
        Reservoir res(id, code, name, munic, max);
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
        City city(id, code, name, demand, pop);
        g.addVertex(city);
    }
    stream.close();
}
