#include <iostream>


using namespace std;
int main(){
    std::cout << "entry point" << std::endl;
}


#include "apply.cpp"
#include "mode.cpp"

/*int main(){
    read_locations("./For Students/Locations.csv", location_map, map);
    read_distances("./For Students/Distances.csv", location_map, map);
    read_locations("./Example/Locations.csv", location_map, map);
    read_distances("./Example/Distances.csv", location_map, map);


    InputData inputData;

    inputData = HandleUserInput();

    OutputData outputData;

    apply_func(map, inputData, outputData);

    writeOutput(inputData, outputData);


    delete map;
    return 0;
}*/