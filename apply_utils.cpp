//
// Created by carlo on 28/03/2025.
//



#include "algorithms.cpp"
#include "data_structures/Graph.h"


//* CHECK IF IT HAS RESTRICTIONS DRIVING *//
bool HasDriveRestriction(const InputData inputData) {
    return !(inputData.includeNode == -1 && inputData.avoidNodes.empty() && inputData.avoidSegments.empty()); //returns true if it has drive restriction
}

//* CHECK IF IT HAS INCLUDE NODE *//
bool HasIncludeNode(const InputData inputData) {
    return inputData.includeNode != -1;
}

//* CHECK IF IT HAS NO OTHER RESTRICTION OTHER THAN MAXWALKTIME (DRIVING-WALKING) //*
bool HasWalkRestriction(const InputData inputData) {
    return !(inputData.avoidNodes.empty() && inputData.avoidSegments.empty());
}

//* SET THE OUTPUT DATA *//
void SetBestDriveRoute(OutputData &output, const vector<Vertex<Location>*> &path, double weight) {
    for (auto v : path) {
        output.BestDrivingRoute.push_back(v->getInfo().id);
    }
    output.best_time = weight;
}

void SetAlternativeDriveRoute(OutputData &output, const vector<Vertex<Location>*> &path, double weight) {
    for (auto v : path) {
        output.AlternativeDrivingRoute.push_back(v->getInfo().id);
    }
    output.time_alternative = weight;
}

void SetRestrictedDriveRoute(OutputData &output, const vector<Vertex<Location>*> &path, double weight) {
    for (auto v : path) {
        output.RestrictedDrivingRoute.push_back(v->getInfo().id);
    }
    output.time_restricted = weight;
}

void SetDriveWalkRoute(OutputData &output, const vector<Vertex<Location>*> &path_d,
    const double time_d,const Location& parkingNode, const vector<Vertex<Location>*> &path_w,
    const double time_w, const double total_t ) {

    for (auto v : path_d) {
        output.DrivingRoute.push_back(v->getInfo().id);
    }
    output.time_DrivingRoute = time_d;
    output.ParkingNode = parkingNode.id;
    for (auto v : path_w) {
        output.WalkingRoute.push_back(v->getInfo().id);
    }
    output.time_WalkingRoute= time_w;
    output.total_time = total_t;
}

void SetDriveWalkRoute2(OutputData &output, const vector<Vertex<Location>*> &path_d,
    const double time_d,const Location& parkingNode, const vector<Vertex<Location>*> &path_w,
    const double time_w, const double total_t ) {

    for (auto v : path_d) {
        output.DrivingRoute2.push_back(v->getInfo().id);
    }
    output.time_DrivingRoute2 = time_d;
    output.ParkingNode2 = parkingNode.id;
    for (auto v : path_w) {
        output.WalkingRoute2.push_back(v->getInfo().id);
    }
    output.time_WalkingRoute2= time_w;
    output.total_time2 = total_t;
}












//* REMOVE NODES *//
void RemoveNodes(Graph<Location> *g, const InputData& inputData) {
    for (int node : inputData.avoidNodes) {
        Location temp;
        temp.id = node;

        g -> removeVertex(temp);
    }
}

//* REMOVE EDGES *//
void RemoveEdges(Graph<Location> *g, const InputData& inputData) {
    for (auto [first, second] : inputData.avoidSegments) {
        Location temp1;
        Location temp2;
        temp1.id = first;
        temp2.id = second;
        g -> removeEdge(temp1, temp2);
        g -> removeEdge(temp2, temp1);
    }
}

// GET PARKING VALUE
bool GetParking(const Graph<Location>* g, const Location& l) {
    return g -> findVertex(l) -> getInfo().parking;
}
