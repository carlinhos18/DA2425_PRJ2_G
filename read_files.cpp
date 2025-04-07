#include "read_files.h"
#include "read_files_utils.cpp"

void read_truck_file(const string& filename, vector<Pallet>* pallets) {
    ifstream infile(filename);
    string line;

    if (!infile.is_open()) {
        cerr << "Could not open file " << filename << endl;
        exit(EXIT_FAILURE);
    }

    getline(infile, line); // Ignorar cabeçalho

    stringstream ss(line);
    Truck truck;

    getline(ss, truck.capacity, ',');
    getline(ss, truck.n_pallets, ',');
    truck.truck_id = get_truck_id(filename);

    string pallets_file = "Pallets_" + truck.truck_id + ".csv";

    read_pallets_file(pallets_file, pallets);

    infile.close();
}


void read_pallets_file(const string& filename, vector<Pallet>* pallets){
    ifstream infile(filename);
    string line;

    if (!infile.is_open()) {
        cerr << "Could not open file " << filename << endl;
        exit(EXIT_FAILURE);
    }

    getline(infile, line); // Ignorar cabeçalho

    while (getline(infile, line)) {
        stringstream ss(line);
        Pallet pallet;
        string idStr, parkingStr;

        getline(ss, pallet.id, ',');
        getline(ss, pallet.weight, ',');
        getline(ss, pallet.profit, ',');

        pallets -> push_back(pallet);
    }

    infile.close();
}

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


