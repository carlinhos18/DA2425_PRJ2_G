#include "apply.cpp"
#include "mode.cpp"

Graph<Location>* map = new Graph<Location>();

unordered_map<string, Location> location_map; // maps the codes on the csv files

int main(){
    /*read_locations("./For Students/Locations.csv", location_map, map);
    read_distances("./For Students/Distances.csv", location_map, map);*/
    read_locations("./Example/Locations.csv", location_map, map);
    read_distances("./Example/Distances.csv", location_map, map);


    InputData inputData;

    inputData = HandleUserInput();

    OutputData outputData;

    apply_func(map, inputData, outputData);

    writeOutput(inputData, outputData);


    delete map;
    return 0;
}