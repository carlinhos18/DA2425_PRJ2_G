#include "./data_structures/Graph.h"
#include "data_structures/UFDS.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>
using namespace std;

struct Location{
    string name;
    int id;
    string code;
    bool parking;

    bool operator==(const Location &other) const {
        return id == other.id;
    }
};

struct Distance {
    string start_node;
    string dest_node;
    int drive_dist;
    int walk_dist;
};

Graph<Location>* map = new Graph<Location>();

unordered_map<string, Location> location_map; //maps the codes on the csv files


void read_locations(const string& filename) {
    ifstream infile(filename);
    string line;

    if (!infile.is_open()) {
        cerr << "Could not open file " << filename << std::endl;
        exit(1);
    }

    getline(infile, line);

    while (getline(infile, line)) {
        stringstream ss(line);
        Location loc;
        string parkingStr;

        getline(ss, loc.name, ',');
        ss >> loc.id;
        ss.ignore(); // Ignore comma
        getline(ss, loc.code, ',');
        getline(ss, parkingStr, ',');

        loc.parking = (parkingStr == "1");

        map->addVertex(loc);
        location_map[loc.code] = loc;
    }


    infile.close();

}


void add_edge(const Distance& info) {
    auto it1 = location_map.find(info.start_node);
    auto it2 = location_map.find(info.dest_node);

    if (it1 == location_map.end() || it2 == location_map.end()) {
        cerr << "Could not add edge between " << info.start_node << " and "
        << info.dest_node << endl;
    }
    Location loc1 = it1->second;
    Location loc2 = it2->second;
    map->addBidirectionalEdge(loc1, loc2, info.drive_dist, info.walk_dist);
}

void read_distances(const string& filename) {
    ifstream infile(filename);
    string line;
    if (!infile.is_open()) {
        cerr << "Could not open file " << filename << std::endl;
        exit(1);
    }
    getline(infile, line);
    while (getline(infile, line)) {
        stringstream ss(line);
        Distance info;
        string driveDistStr, walkDistStr;
        getline(ss, info.start_node, ',');
        getline(ss, info.dest_node, ',');
        getline(ss, driveDistStr, ',');
        getline(ss, walkDistStr, ',');
        (driveDistStr == "X") ? (info.drive_dist = -1) : (info.drive_dist = stoi(driveDistStr));
        info.walk_dist = stoi(walkDistStr);
        add_edge(info);
    }
    infile.close();
}



void Driving_Only_Best(Graph<Location>* g, Vertex<Location>* source, Vertex<Location>* dest) {
    // Inicializa vértices
    for (auto v : g->getVertexSet()) {
        v->setVisited(false);
        v->setDist(INT_MAX);
        v->setPath(nullptr);  // Inicializa o caminho como null (sem predecessor)
    }

    source->setDist(0);
    source->setPath(nullptr);  // A origem não tem predecessor

    // Fila de prioridade (min-heap) -> processa primeiro o menor custo
    priority_queue<pair<int, Vertex<Location>*>, vector<pair<int, Vertex<Location>*>>, greater<>> q;
    q.push({0, source});

    while (!q.empty()) {
        auto [dist, u] = q.top();
        q.pop();

        if (u->isVisited()) continue;
        u->setVisited(true);

        for (auto edge : u->getAdj()) {
            Vertex<Location>* neighbor = edge->getDest();  // Obtém o vértice de destino
            int weight = edge->getDriveWeight();             // Obtém o peso da aresta

            int newDist = u->getDist() + weight;
            if (newDist < neighbor->getDist()) {
                neighbor->setDist(newDist);

                // Atualiza o caminho para apontar para o vértice atual (u)
                neighbor->setPath(edge);

                q.push({newDist, neighbor});
            }
        }
    }

    cout << "Melhor distância até " << dest->getInfo().code << ": " << dest->getDist() << endl;

    vector<Vertex<Location>*> path;
    for (auto v = dest; v != nullptr; v = v->getPath() ? v->getPath()->getOrig(): nullptr) {
        path.push_back(v);
    }

    cout << "Caminho percorrido: ";
    for (size_t i = path.size(); i > 0; --i) {
        cout << path[i - 1]->getInfo().code;
        if (i != 1) cout << " -> ";
    }
    cout << endl;
}




int main(){
    read_locations("./For Students/Locations.csv");
    /*if (!map->getVertexSet().empty()) {
        for (Vertex<Location>* v : map->getVertexSet()) {
            cout << "Location: " << v->getInfo().name << ", ID: " << v->getInfo().id
                 << ", Code: " << v->getInfo().code << ", Parking: "
                 << (v->getInfo().parking ? "Yes" : "No") << endl;
        }
    } else {
        cerr << "No locations were loaded." << endl;
    }*/

    read_distances("./For Students/Distances.csv");

    /*for (auto vertex : map->getVertexSet()) {
        cout << "Location: " << vertex->getInfo().code << " -> ";

        for (auto edge : vertex->getAdj()) {
            auto v = edge->getDest();
            cout << v->getInfo().code
                 << " (Drive: " << edge->getDriveWeight()
                 << ", Walk: " << edge->getWalkWeight()
                 << "), ";
        }
        cout << endl;
    }*/
    // Procurar os vértices correspondentes aos códigos
    Vertex<Location>* source = nullptr;
    Vertex<Location>* dest = nullptr;

    // Procurando o vértice correspondente ao código do ponto de origem
    for (auto v : map->getVertexSet()) {
        if (v->getInfo().code == "LD3372") {
            source = v;
            break;
        }
    }

    // Procurando o vértice correspondente ao código do ponto de destino
    for (auto v : map->getVertexSet()) {
        if (v->getInfo().code == "CSA3") {
            dest = v;
            break;
        }
    }

    // Verificar se ambos os vértices foram encontrados
    if (source == nullptr || dest == nullptr) {
        cerr << "Erro: um ou ambos os vértices não foram encontrados." << endl;
        return 1;
    }

    // Chamar a função de cálculo da melhor distância
    Driving_Only_Best(map, source, dest);

    // Limpeza
    delete map;
    return 0;
}