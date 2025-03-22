//
// Created by carlo on 22/03/2025.
//

#ifndef STRUCTURES_H
#define STRUCTURES_H

#include "Graph.h"
#include "UFDS.h"
#include <string>
#include <unordered_set>

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

struct InputData {
    string mode;
    int source;
    int destination;
    unordered_set<int> avoidNodes;
    vector<pair<int, int>> avoidSegments;
    int includeNode = 0;
    int MaxWalkTime = 0;
};

struct OutputData {
    // FOR DRIVING MODE //
    vector<int> BestDrivingRoute;
    int time_best = 0;
    vector<int> AlternativeDrivingRoute;
    int time_alternative = 0;
    vector<int> RestrictedDrivingRoute;
    int time_restricted = 0;

    // FOR DRIVE-WALKING MODE //
    vector<int> DrivingRoute;
    int time_DrivingRoute = 0;
    int ParkingNode;
    vector<int> WalkingRoute;
    int time_WalkingRoute = 0;
    int total_time = time_DrivingRoute + time_WalkingRoute;
    string message;


};

#endif //STRUCTURES_H
