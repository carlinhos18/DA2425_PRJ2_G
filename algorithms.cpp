#include "data_structures/Structures.h"




template <class T>
bool relax(Edge<T> *edge) {
    Vertex<T> *u = edge->getOrig();
    Vertex<T> *v = edge->getDest();
    double weight = edge->getDriveWeight();

    if (weight < 0) return false;

    if (v->getDist() > u->getDist() + weight) {
        v->setDist(u->getDist() + weight);
        v->setPath(edge);
        return true;
    }
    return false;
}

template <class T>
void dijkstra(Graph<T> * g, const Location &origin) {
    MutablePriorityQueue<Vertex<T>> pqueue;

    for (Vertex<T>* v : g -> getVertexSet()) {
        v -> setDist(numeric_limits<double>::infinity());
        v -> setPath(nullptr);
        v-> setVisited(false);
    }

    Vertex<T> *s = g->findVertex(origin);
    s -> setDist(0);
    pqueue.insert(s);

    if (!s) {
        std::cerr << "Error: Origin vertex not found in graph!" << std::endl;
        return;
    }

    while (!pqueue.empty()) {
        Vertex<T> *v = pqueue.extractMin();
        v -> setVisited(true);
        for (Edge<T> *e : v -> getAdj()) {
            if (e->getDriveWeight() == -1) continue; // as arestas com -1 sao ignoradas
            if (!e->getDest() -> isVisited()) {
                if (relax(e)) {
                    pqueue.insert(e -> getDest());
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
        return {path, -1};
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
    dijkstra(g, orig);
    pair<vector<Vertex<T>*>, double> alternativePath = getShortestPath(g, dest);

    // Retornar o caminho alternativo ou {} se não existir
    return alternativePath.first.size() >= 2 ? alternativePath : make_pair(vector<Vertex<T>*>(), -1.0);
}





