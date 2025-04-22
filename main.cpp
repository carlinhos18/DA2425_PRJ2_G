#include "mode.cpp"
#include "apply.cpp"
#include "write_output.cpp"
using namespace std;

int main() {
    Algorithm data;
    OutputData output;

    //handle user input
    InputData inputData = HandleUserInput();

    //read file depending on the user input
    read_truck_file(inputData.filename, data);

    //apply specific algorithm to the dataset
    apply(output, data, inputData);

    //write the output
    write_output(output);

    return 0;
}
