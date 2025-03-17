#include "read_files.cpp"
#include "algorithms.cpp"
Graph<Location>* map = new Graph<Location>();

unordered_map<string, Location> location_map; // maps the codes on the csv files

int main(){
    read_locations("./For Students/Locations.csv", location_map, map);

    /*if (!map->getVertexSet().empty()) {
        for (Vertex<Location>* v : map->getVertexSet()) {
            cout << "Location: " << v->getInfo().name << ", ID: " << v->getInfo().id
                 << ", Code: " << v->getInfo().code << ", Parking: "
                 << (v->getInfo().parking ? "Yes" : "No") << endl;
        }
    } else {
        cerr << "No locations were loaded." << endl;
    }*/

    read_distances("./For Students/Distances.csv", location_map, map);

    for (auto vertex : map->getVertexSet()) {
        cout << "Location: " << vertex->getInfo().code << " -> ";

        for (auto edge : vertex->getAdj()) {
            auto v = edge->getDest();
            cout << v->getInfo().code
                 << " (Drive: " << edge->getDriveWeight()
                 << ", Walk: " << edge->getWalkWeight()
                 << "), ";
        }
        cout << endl;
    }

    char choice;

    InputData inputData;

    cout << "Choose an input type:\n'f' for input.txt file; 'c' for manual write on the console" << endl;

    while (true) {
        cin >> choice;

        if (choice == 'f'){
            string filename = "input.txt";
            inputData =  read_input_file(filename);

            break;
        }else if (choice == 'c') {
            cin.clear();
            cin.ignore();

            string mode;

            while (true) {
                cout << "Mode (walking, driving, driving-walking): ";
                getline(cin, mode);

                if (mode == "walking" || mode == "driving" || mode == "driving-walking") {
                    break;
                } else {
                    cout << "Invalid mode! Please enter 'walking', 'driving', or 'driving-walking'." << endl;
                }
            }

            int source = getValidInteger("Source: ");
            int destination = getValidInteger("Destination: ");

            inputData.source = source;
            inputData.destination = destination;
            inputData.mode = mode;

            break;
        }
        else {
            cout << "Invalid choice! Please enter 'f' or 'c'." << endl;

            cin.clear();
            cin.ignore();
        }
    }


    if (inputData.mode.empty()) {
        cerr << "Invalid Input File. Ignoring" << endl;
        return 1;
    }

    displayInputData(inputData);





    delete map;
    return 0;
}