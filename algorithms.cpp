#include "algorithms.h"

template <class T>
bool relax(Edge<T> *edge, bool walkingMode) {
    Vertex<T> *u = edge->getOrig();
    Vertex<T> *v = edge->getDest();
    double weight = walkingMode ? edge->getWalkWeight() : edge->getDriveWeight();

    if (weight < 0) return false;

    if (v->getDist() > u->getDist() + weight) {
        v->setDist(u->getDist() + weight);
        v->setPath(edge);
        return true;
    }
    return false;
}

template <class T>
void dijkstra(Graph<T> * g, const Location &origin, bool walkingMode) {
    MutablePriorityQueue<Vertex<T>> pqueue;

    for (Vertex<T>* v : g -> getVertexSet()) {
        v->setDist(numeric_limits<double>::infinity());
        v->setPath(nullptr);
        v->setVisited(false);
    }

    Vertex<T> *s = g->findVertex(origin);
    if (!s) {
        cerr << "Error: Origin vertex not found in graph!" << endl;
        exit(EXIT_FAILURE);
    }

    s->setDist(0);
    pqueue.insert(s);

    while (!pqueue.empty()) {
        Vertex<T> *v = pqueue.extractMin();
        v->setVisited(true);

        for (Edge<T> *e : v->getAdj()) {
            if (!e->getDest()->isVisited()) {
                if (relax(e, walkingMode)) {
                    pqueue.insert(e->getDest());
                }
            }
        }
    }
}



template <class T>
pair<vector<Vertex<T>*>, double> getShortestPath(Graph<T>* g, const Location& destination) {
    vector<Vertex<T>*> path;
    Vertex<T>* v = g->findVertex(destination);

    if (!v) {
        std::cerr << "Error: Destination vertex not found in graph!" << std::endl;
        exit(EXIT_FAILURE);
    }

    if (v->getDist() == numeric_limits<double>::infinity())
        return {path, -1};

    double totalWeight = v->getDist();

    while (v != nullptr) {
        path.push_back(v);
        if (v->getPath() == nullptr) break;
        v = v->getPath()->getOrig();
    }

    reverse(path.begin(), path.end());

    return {path, totalWeight};
}

template <class T>
pair<vector<Vertex<T>*>, double> getAlternativeRoute(Graph<T>* g, const Location& orig, const Location& dest, vector<Vertex<T>*> Best_path) {
    if (Best_path.size() < 2) return {{}, -1}; // Se o caminho ótimo não for válido

    // remover edges do best_path
    for (size_t i = 0; i < Best_path.size() - 1; i++) {
        g->removeEdge(Best_path[i]->getInfo(), Best_path[i + 1]->getInfo());
    }

    // correr dijkstra outra vez e obter o segundo melhor caminho
    dijkstra(g, orig, false);
    pair<vector<Vertex<T>*>, double> alternativePath = getShortestPath(g, dest);

    // Retornar o caminho alternativo ou {} se não existir
    return alternativePath.first.size() >= 2 ? alternativePath : make_pair(vector<Vertex<T>*>(), -1.0);
}

template <class T>
tuple<vector<Vertex<T>*>, double, Location, vector<Vertex<T>*>, double, double>
eco_friendly_route(Graph<T>* g, const Location& orig, const Location& dest, double maxWalkTime) {
    auto start = g->findVertex(orig);
    auto end = g->findVertex(dest);

    if (!start || !end) {
        cerr << "Error: Origin or destination not found in graph.\n";
        exit(EXIT_FAILURE);
    }

    for (auto e : start->getAdj()) {
        if (e->getDest() == end) {
            cerr << "Error: Origin and destination cannot be adjacent nodes.\n";
            exit(EXIT_FAILURE);
        }
    }
    cout << orig.parking << " -> " << dest.parking << endl;
    if (orig.parking && dest.parking) { // Ambos são parques
        cerr << "Error: Origin and destination cannot be parking nodes.\n";
        exit(EXIT_FAILURE);

    }


    vector<Vertex<T>*> bestDrivingPath;
    double bestDrivingTime = numeric_limits<double>::max();
    Location bestParking;
    vector<Vertex<T>*> bestWalkingPath;
    double bestWalkingTime = numeric_limits<double>::max();
    double bestTotalTime = numeric_limits<double>::max();

    // Identificar todos os locais de estacionamento
    vector<Location> parkingLocations;
    for (auto v : g->getVertexSet()) {
        if (v->getInfo().parking) {
            parkingLocations.push_back(v->getInfo());
        }
    }

    if (parkingLocations.empty()) {
        cerr << "Error: No parking nodes available.\n";
        exit(EXIT_FAILURE);

    }

    // Testar todas as opções de estacionamento
    for (const auto& parking : parkingLocations) {
        dijkstra(g, orig, false); // Executa Dijkstra no modo de condução
        auto [drivingPath, drivingTime] = getShortestPath(g, parking);

        if (drivingPath.empty()) continue;

        dijkstra(g, parking, true); // Executa Dijkstra no modo de caminhada
        auto [walkingPath, walkingTime] = getShortestPath(g, dest);

        if (walkingPath.empty() || walkingTime > maxWalkTime) continue;

        double totalTime = drivingTime + walkingTime;
        if (totalTime < bestTotalTime || (totalTime == bestTotalTime && walkingTime > bestWalkingTime)) {
            bestTotalTime = totalTime;
            bestDrivingPath = drivingPath;
            bestDrivingTime = drivingTime;
            bestParking = parking;
            bestWalkingPath = walkingPath;
            bestWalkingTime = walkingTime;
        }
    }

    if (bestDrivingPath.empty() || bestWalkingPath.empty()) {
        return {};
    }

    return {bestDrivingPath, bestDrivingTime, bestParking, bestWalkingPath, bestWalkingTime, bestTotalTime};
}






