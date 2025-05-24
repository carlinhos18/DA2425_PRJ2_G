#include "mode.cpp"
#include "apply.cpp"
#include "write_output.cpp"
using namespace std;


/**
 * @mainpage Projeto Desenho de Algoritmos
 *
 * @section about About the Project:
 * This project is the optimization of a real-world variation of the knapsack problem,
 * where the goal is to maximize the profit of pallets loaded onto a truck without exceeding its weight capacity.
 * 
 *
 * @section authors Authors:
 *  - Carlos Cristelo, up202307628
 *  - Martim Neves, up202305501
 *  - Tomás Salgueiro, up202305511
 */

/**
 * @brief Entry point of the program.
 *
 * Handles user input, loads truck data, selects and applies the chosen algorithm,
 * and writes the output. If the user selects benchmark mode, runs benchmark tests instead.
 *
 * @return 0
 */
int main() {
    Algorithm data;
    OutputData output;

    //handle user input
    InputData inputData = HandleUserInput();

    if (inputData.algorithm != "benchmark") {
        //read file depending on the user input
        read_truck_file(inputData.filename, data);


        //apply specific algorithm to the dataset
        apply(output, data, inputData);

        //write the output
        write_output(output, data);
    }
    else {
        bool skipLong = askSkipLongAlgorithms();
        benchmarkMode(skipLong);
    }
    return 0;
}
