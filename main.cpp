#include "read_files.cpp"

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

    InputData inputData;

    read_input_file("input.txt", inputData);

    displayInputData(inputData);
    delete map;
    return 0;
}