#include "data_structures/Structures.h"
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <iostream>







void read_locations(const string& filename, unordered_map<string, Location>& location_map, Graph<Location>* map) {
    ifstream infile(filename);
    string line;

    if (!infile.is_open()) {
        cerr << "Could not open file " << filename << endl;
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
        cerr << "Could not open file " << filename << endl;
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

int getValidInteger(const string &prompt) {
    string input;
    int value;

    while (true) {
        cout << prompt;
        getline(std::cin, input);

        try {
            size_t pos;
            value = stoi(input, &pos);

            if (pos == input.size() && is_valid_integer(input)) {
                break;
            }
        } catch (...) {

        }

        cout << "Invalid input. Please enter a valid integer.\n";
    }

    return value;
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
        else if (key == "MaxWalkTime") {
            if (!is_valid_integer(value)) {
                cerr << "Invalid MaxWalkTime: " << value << endl;
                continue;
            }
            inputData.MaxWalkTime = stoi(value);
        }
        else if (key == "AvoidNodes"){
            // TODO
            stringstream nodes(value);
            string node;
            while (getline(nodes, node, ',')) {
                if (is_valid_integer(node)) {
                    inputData.avoidNodes.insert(stoi(node));
                } else {
                    cerr << "Invalid AvoidNode: " << node << endl;
                }
            }
        }
        else if (key == "AvoidSegments") {
            // TODO
            stringstream segments(value);
            string segment;
            while (getline(segments, segment, ')')) {
                segment.erase(remove(segment.begin(), segment.end(), '('), segment.end());
                segment.erase(remove(segment.begin(), segment.end(), ' '), segment.end());

                if (segment.empty()) continue;

                stringstream pairStream(segment);
                string first, second;
                if (getline(pairStream, first, ',') && getline(pairStream, second, ',')) {
                    if (is_valid_integer(first) && is_valid_integer(second)) {
                        inputData.avoidSegments.emplace_back(stoi(first), stoi(second));
                    } else {
                        cerr << "Invalid AvoidSegment: " << segment << endl;
                    }
                }
            }
        }
        else if (key == "IncludeNode") {
            //TODO
            if (!is_valid_integer(value)) {
                cerr << "Invalid IncludeNode: " << value << endl;
                continue;
            }
            inputData.includeNode = stoi(value);
        }
        else {
            cerr << "Invalid key: " << key << endl;
            return {};
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

void writeOutput(const InputData& inputData, const OutputData& outputData) {
    ofstream outfile("output.txt");

    outfile << "Source: " << inputData.source << endl;
    outfile << "Destination: " << inputData.destination << endl;

    if (inputData.mode == "driving") {
        if (inputData.includeNode == 0 && inputData.avoidNodes.empty() && inputData.avoidSegments.empty()) {
            outfile << "BestDrivingRoute: ";
            if (outputData.BestDrivingRoute.empty()) {
                outfile << "none" << endl;
            }
            else {
                for (size_t i = 0; i < outputData.BestDrivingRoute.size(); i++) {
                    outfile << outputData.BestDrivingRoute[i];
                    if (i < outputData.BestDrivingRoute.size() - 1) {
                        outfile << "->";
                    }
                }
                outfile<<" (" << outputData.best_time << ")";
                outfile << endl;
            }

            outfile << "AlternativeDrivingRoute: ";
            if (outputData.AlternativeDrivingRoute.empty()) {
                outfile << "none" << endl;
            }
            else {
                for (int node : outputData.AlternativeDrivingRoute) {
                    outfile << node << " ";
                }
                outfile<<" (" << outputData.time_alternative << ")";
                outfile << endl;
            }
        }
        else {
            outfile << "AlternativeDrivingRoute: ";
            for (int node : outputData.RestrictedDrivingRoute) {
                outfile << node << " ";
            }
            outfile << outputData.time_restricted;
            outfile << endl;
        }
    }
    else if (inputData.mode == "driving-walking") {
        //se houver solução:
        outfile << "DrivingRoute: ";
        for (int node : outputData.DrivingRoute) {
            outfile << node << " ";
        }
        outfile << outputData.time_DrivingRoute << endl;
        outfile << "ParkingNode: " << outputData.ParkingNode << endl;
        outfile << "Walking Route: ";
        for (int node : outputData.WalkingRoute) {
            outfile << node << " ";
        }
        outfile << endl;
        outfile << "TotalTime: " << outputData.total_time << endl;
        // se nao houver soluçao colocar tudo a none com a message a dizer
        // uma sugestao para que haja soluçao
        // ou entao dar possiveis rotas que se aproximem com o que
        // o utilizador pediu
    }

    ifstream infile("output.txt");
    if (infile) {
        cout << "\nOutput File Content:\n";
        string line;
        while (getline(infile, line)) {
            cout << line << endl;
        }
    }
    infile.close();
}


