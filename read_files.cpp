#include "./data_structures/Graph.h"
#include "data_structures/UFDS.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>
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
    int includeNode;
};


void read_locations(const string& filename, unordered_map<string, Location>& location_map, Graph<Location>* map) {
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

void add_edge(const Distance& info, unordered_map<string, Location>& location_map, Graph<Location>* map) {
    const auto it1 = location_map.find(info.start_node);
    const auto it2 = location_map.find(info.dest_node);

    if (it1 == location_map.end() || it2 == location_map.end()) {
        cerr << "Could not add edge between " << info.start_node << " and "
        << info.dest_node << endl;
    }
    Location loc1 = it1->second;
    Location loc2 = it2->second;
    map->addEdge(loc1, loc2, info.drive_dist, info.walk_dist);
}

void read_distances(const string& filename, unordered_map<string, Location>& location_map, Graph<Location>* map) {
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
        add_edge(info,location_map,map);
    }
    infile.close();
}

bool is_valid_integer(const string& str) {
    return !str.empty() && all_of(str.begin(), str.end(), ::isdigit);
}

InputData read_input_file(const string& filename) {
    InputData inputData;

    ifstream infile(filename);
    if (!infile.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return {};
    }

    bool hasMode = false, hasSource = false, hasDestination = false;

    string line;
    while (getline(infile, line)) {
        stringstream ss(line);
        string key, value;

        getline(ss, key, ':');
        getline(ss, value);

        if (key == "Mode") {
            if (value != "driving" && value != "driving-walking" && value != "walking") {
                cerr << "Invalid mode: " << value << endl;
                return {};
            }
            inputData.mode = value;
            hasMode = true;
        }
        else if (key == "Source") {
            if (!is_valid_integer(value)) {
                cerr << "Invalid Source: " << value << endl;
                return {};
            }
            inputData.source = stoi(value);
            hasSource = true;
        }
        else if (key == "Destination") {
            if (!is_valid_integer(value)) {
                cerr << "Invalid Destination: " << value << endl;
                return {};
            }
            inputData.destination = stoi(value);
            hasDestination = true;
        }
        else if (key == "AvoidNodes"){
            // TODO
        }
        else if (key == "AvoidSegments") {
            // TODO
        }
        else if (key == "IncludeNode") {
            //TODO
        }
        else {
            cerr << "Invalid key: " << key << endl;
        }
    }

    if (!hasMode || !hasSource || !hasDestination) {
        cerr << "Missing required fields in input file." << endl;
        return {};
    }

    infile.close();

    return inputData;
}

void displayInputData(const InputData& inputData) {
    cout << "Mode: " << inputData.mode << endl;
    cout << "Source: " << inputData.source << endl;
    cout << "Destination: " << inputData.destination << endl;
}

