//
// Created by carlo on 26/03/2025.
//

#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "data_structures/Structures.h"

/* Helper function for Dijkstra */
template <class T>
bool relax(Edge<T> *edge);

/* Dijkstra to compute the shortest paths */
template <class T>
void dijkstra(Graph<T> * g, const Location &origin, bool walkingMode);

/* Traces the best path back starting with dest node */
template <class T>
pair<vector<Vertex<T>*>, double> getShortestPath(Graph<T>* g, const Location& destination);

/* Traces the second-best path eliminating the best path */
template <class T>
pair<vector<Vertex<T>*>, double> getAlternativeRoute(Graph<T>* g, const Location& orig, const Location& dest, vector<Vertex<T>*> Best_path);



#endif //ALGORITHMS_H
