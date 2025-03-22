#include "data_structures/Structures.h"

#include <climits>



template <class T>
bool relax(Edge<T> *edge) {
    Vertex<T> *u = edge->getOrig();
    Vertex<T> *v = edge->getDest();
    double weight = edge->getDriveWeight();

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
        v -> setDist(INT_MAX);
        v -> setPath(nullptr);
        v-> setVisited(false);
    }

    Vertex<T> *s = g->findVertex(origin);
    s -> setDist(0);
    pqueue.insert(s);

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