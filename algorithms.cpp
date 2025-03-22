#include "data_structures/Structures.h"

#include <climits>



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

    if (!v || v->getDist() == numeric_limits<double>::infinity())
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

