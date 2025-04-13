#include "mode.cpp"
#include "apply.cpp"
using namespace std;

int main() {

    InputData inputData;
    Algorithm data;
    OutputData output;

    //handle user input
    inputData = HandleUserInput();

    //read file depending on the user input
    read_truck_file(inputData.filename, data);

    //apply specific algorithm to the dataset
    apply(output, data, inputData);

    return 0;
}
