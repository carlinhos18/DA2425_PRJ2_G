#include "read_files.h"
#include "read_files_utils.cpp"

void read_locations(const string& filename, unordered_map<string, Location>& location_map, Graph<Location>* map) {
    ifstream infile(filename);
    string line;

    if (!infile.is_open()) {
        cerr << "Could not open file " << filename << endl;
        exit(EXIT_FAILURE);
    }

    getline(infile, line); // Ignorar cabeçalho

    while (getline(infile, line)) {
        stringstream ss(line);
        Location loc;
        string idStr, parkingStr;

        getline(ss, loc.name, ',');
        getline(ss, idStr, ',');
        getline(ss, loc.code, ',');
        getline(ss, parkingStr, ',');

        // Converter para int e garantir que espaços extras não afetam a leitura
        try {
            loc.id = stoi(idStr);
            loc.parking = (stoi(parkingStr) == 1);
        } catch (exception& e) {
            cerr << "Error parsing line: " << line << " | " << e.what() << endl;
            continue;
        }

        map->addVertex(loc);
        location_map[loc.code] = loc;
    }

    infile.close();
}




void read_distances(const string& filename, unordered_map<string, Location>& location_map, Graph<Location>* map) {
    ifstream infile(filename);
    string line;
    if (!infile.is_open()) {
        cerr << "Could not open file " << filename << endl;
        exit(EXIT_FAILURE);

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

InputData read_input_file(const string& filename) {
    InputData inputData;

    ifstream infile(filename);
    if (!infile.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        exit(EXIT_FAILURE);

    }

    bool hasMode = false, hasSource = false, hasDestination = false;

    string line;
    while (getline(infile, line)) {
        stringstream ss(line);
        string key, value;

        getline(ss, key, ':');
        getline(ss, value);

        if (key == "Mode") {
            if (value != "driving" && value != "driving-walking") {
                cerr << "Invalid mode: " << value << endl;
                exit(EXIT_FAILURE);

            }
            inputData.mode = value;
            hasMode = true;
        }
        else if (key == "Source") {
            if (!is_valid_integer(value) || stoi(value) <= 0) {
                cerr << "Invalid Source: " << value << endl;
                exit(EXIT_FAILURE);
            }
            inputData.source = stoi(value);
            hasSource = true;
        }
        else if (key == "Destination") {
            if (!is_valid_integer(value) || stoi(value) <= 0) {
                cerr << "Invalid Destination: " << value << endl;
                exit(EXIT_FAILURE);
            }
            inputData.destination = stoi(value);
            hasDestination = true;
        }
        else if (key == "MaxWalkTime" && inputData.mode == "driving-walking") {
            if (!is_valid_integer(value) || stoi(value) <= 0) {
                cerr << "Invalid MaxWalkTime: " << value << endl;
                exit(EXIT_FAILURE);
            }
            inputData.MaxWalkTime = stoi(value);
        }
        else if (key == "AvoidNodes"){
            if (value.empty()) {
                continue;
            }
            stringstream nodes(value);
            string node;
            while (getline(nodes, node, ',')) {
                if (is_valid_integer(node)) {
                    inputData.avoidNodes.insert(stoi(node));
                } else {
                    cerr << "Invalid AvoidNode: " << node << endl;
                    exit(EXIT_FAILURE);
                }
            }
        }
        else if (key == "AvoidSegments") {
            if (value.empty()) {
                continue;
            }

            size_t pos = 0;
            while ((pos = value.find('(')) != string::npos) {
                size_t endPos = value.find(')', pos);
                if (endPos == string::npos) {
                    cerr << "Invalid AvoidSegment format: " << value << endl;
                    exit(EXIT_FAILURE);
                }

                string segment = value.substr(pos + 1, endPos - pos - 1);
                value = value.substr(endPos + 1);

                stringstream pairStream(segment);
                string first, second;

                if (getline(pairStream, first, ',') && getline(pairStream, second, ',')) {
                    first.erase(remove(first.begin(), first.end(), ' '), first.end());
                    second.erase(remove(second.begin(), second.end(), ' '), second.end());

                    if (is_valid_integer(first) && is_valid_integer(second)) {
                        int firstInt = stoi(first);
                        int secondInt = stoi(second);
                        if (firstInt > 0 && secondInt > 0) {
                            inputData.avoidSegments.emplace_back(firstInt, secondInt);
                        } else {
                            cerr << "Invalid AvoidSegment values: " << segment << endl;
                            exit(EXIT_FAILURE);
                        }
                    } else {
                        cerr << "Invalid AvoidSegment format: " << segment << endl;
                        exit(EXIT_FAILURE);
                    }
                } else {
                    cerr << "Malformed AvoidSegment pair: " << segment << endl;
                    exit(EXIT_FAILURE);
                }
            }
        }

        else if (key == "IncludeNode") {
            if (value.empty()) {
               continue;
            }

            if (!is_valid_integer(value) || stoi(value) <= 0) {
                cerr << "Invalid IncludeNode: " << value << endl;
                exit(EXIT_FAILURE);
            }
            inputData.includeNode = stoi(value);
        }
        else {
            cerr << "Invalid key: " << key << endl;
            exit(EXIT_FAILURE);
        }
    }

    if (!hasMode || !hasSource || !hasDestination) {
        cerr << "Missing required fields in input file." << endl;
        exit(EXIT_FAILURE);
    }

    infile.close();

    return inputData;
}

/*void displayInputData(const InputData& inputData) {
    cout << "Mode: " << inputData.mode << endl;
    cout << "Source: " << inputData.source << endl;
    cout << "Destination: " << inputData.destination << endl;
    if (inputData.MaxWalkTime > 0)    cout << "MaxWalkTime: " << inputData.MaxWalkTime << endl;

    if (!inputData.avoidNodes.empty()) {
        cout << "AvoidNodes: ";
        bool first = true;
        for (auto an : inputData.avoidNodes) {
            if (!first) cout << ", ";
            cout << an;
            first = false;
        }
        cout << endl;
    }

    if (!inputData.avoidSegments.empty()) {
        cout << "AvoidSegments: ";
        bool first = true;
        for (auto as : inputData.avoidSegments) {
            if (!first) cout << ", ";
            cout << "(" << as.first << ", " << as.second << ")";
            first = false;
        }
        cout << endl;
    }
    if (inputData.includeNode > 0)    cout << "IncludeNode: " << inputData.includeNode << endl;

}*/

void writeOutput(const InputData& inputData, const OutputData& outputData) {
    ofstream outfile("output.txt");

    outfile << "Source: " << inputData.source << endl;
    outfile << "Destination: " << inputData.destination << endl;

    if (inputData.mode == "driving") {
        if (inputData.includeNode == -1 && inputData.avoidNodes.empty() && inputData.avoidSegments.empty()) {
            outfile << "BestDrivingRoute: ";
            if (outputData.BestDrivingRoute.empty()) {
                outfile << "none" << endl;
            }
            else {
                for (size_t i = 0; i < outputData.BestDrivingRoute.size(); i++) {
                    outfile << outputData.BestDrivingRoute[i];
                    if (i < outputData.BestDrivingRoute.size() - 1) {
                        outfile << ",";
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
                for (size_t i = 0; i < outputData.AlternativeDrivingRoute.size(); i++) {
                    outfile << outputData.AlternativeDrivingRoute[i];
                    if (i < outputData.AlternativeDrivingRoute.size() - 1) {
                        outfile << ",";
                    }
                }
                outfile<<" (" << outputData.time_alternative << ")";
                outfile << endl;
            }
        }
        else {
            outfile << "RestrictedDrivingRoute: ";

            if (outputData.RestrictedDrivingRoute.empty()) {
                outfile << "none" << endl;
            }
            else {
                for (size_t i = 0; i < outputData.RestrictedDrivingRoute.size(); i++) {
                    outfile << outputData.RestrictedDrivingRoute[i];
                    if (i < outputData.RestrictedDrivingRoute.size() - 1) {
                        outfile << ",";
                    }
                }
                outfile<<" (" << outputData.time_restricted << ")";
                outfile << endl;
            }
        }
    }
    else if (inputData.mode == "driving-walking") {
        //se houver solução:
        if (outputData.message.empty()) {
            outfile << "DrivingRoute: ";
            for (size_t i = 0; i < outputData.DrivingRoute.size(); i++) {
                outfile << outputData.DrivingRoute[i];
                if (i < outputData.DrivingRoute.size() - 1) {
                    outfile << ",";
                }
            }
            outfile << "(" << outputData.time_DrivingRoute << ")" << endl;
            outfile << "ParkingNode: " << outputData.ParkingNode << endl;
            outfile << "Walking Route: ";
            for (size_t i = 0; i < outputData.WalkingRoute.size(); i++) {
                outfile << outputData.WalkingRoute[i];
                if (i < outputData.WalkingRoute.size() - 1) {
                    outfile << ",";
                }
            }
            outfile << "(" << outputData.time_WalkingRoute << ")" << endl;
            outfile << "TotalTime: " << outputData.total_time << endl;
        }
        else{
            // se nao houver soluçao colocar tudo a none com a message a dizer
            // uma sugestao para que haja soluçao
            // ou entao dar possiveis rotas que se aproximem com o que
            // o utilizador pediu
            outfile << "Message: " << outputData.message << endl;
            outfile << "Approximate Solutions" << endl;
            vector<RouteInfo> routes;

            if (!outputData.DrivingRoute.empty() && !outputData.WalkingRoute.empty()) {
                routes.push_back({outputData.DrivingRoute, outputData.time_DrivingRoute,
                                  outputData.ParkingNode, outputData.WalkingRoute,
                                  outputData.time_WalkingRoute, outputData.total_time});
            }

            if (!outputData.DrivingRoute2.empty() && !outputData.WalkingRoute2.empty()) {
                routes.push_back({outputData.DrivingRoute2, outputData.time_DrivingRoute2,
                                  outputData.ParkingNode2, outputData.WalkingRoute2,
                                  outputData.time_WalkingRoute2, outputData.total_time2});
            }

            sort(routes.begin(), routes.end(), [](const RouteInfo& a, const RouteInfo& b) {
                if (a.total_time == b.total_time) {
                    return a.time_WalkingRoute < b.time_WalkingRoute;
                }
                return a.total_time < b.total_time;
            });

            for (size_t i = 0; i < routes.size(); i++) {
                outfile << "DrivingRoute" << (i + 1) << ":";
                for (size_t j = 0; j < routes[i].DrivingRoute.size(); ++j) {
                    if (j > 0) outfile << ",";
                    outfile << routes[i].DrivingRoute[j];
                }
                outfile << "(" << routes[i].time_DrivingRoute << ")" << endl;

                outfile << "ParkingNode" << (i + 1) << ":" << routes[i].ParkingNode << endl;

                outfile << "WalkingRoute" << (i + 1) << ":";
                for (size_t j = 0; j < routes[i].WalkingRoute.size(); ++j) {
                    if (j > 0) outfile << ",";
                    outfile << routes[i].WalkingRoute[j];
                }
                outfile << "(" << routes[i].time_WalkingRoute << ")" << endl;

                outfile << "TotalTime" << (i + 1) << ":" << routes[i].total_time << endl;
            }
        }
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


