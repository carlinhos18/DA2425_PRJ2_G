//
// Created by ceraizi on 26-03-2025.
//

#ifndef MODE_H
#define MODE_H

#include <string>
#include "data_structures/structures.h"
#include <iomanip>

/**
 * 
 * @brief Prompts the user to seelct a valid algorithm.
 * 
 * This function continuously prompts the user via standard input
 * until a valid algorithm is entered. Valid algorithms include:
 * "exhaustive", "dynamic programming", "approximation", "genetic", and "benchmark".
 * 
 * @return A string representing the selected algorithm.
 * 
 * @note the function will not return until a valid input is provided.
 */
std::string getAlgorithm();

/**
 * 
 * @brief Prompts the user for a valid integer input.
 * 
 * This function prompts the user with a given message until a valid integer
 * is entered. It handles invalid inputs gracefully and continues to prompt
 * until a valid integer is provided.
 * 
 * @param prompt The message to display to the user when asking for input.
 * @return The valid integer input from the user.
 *
 */
int getValidInteger(const std::string &prompt);


/**
 * 
 * @brief Handles user input for selecting the algorithm and dataset.ADJ_FREQUENCY
 * 
 * This function prompts the user to select an algorithm and a dataset.
 * 
 * @return InputData A structure containing the selected algorithm and dataset filename.
 * 
 */
InputData HandleUserInput();


/**
 * @brief Asks the user whether to skip long-running algorithms.
 * 
 * This function prompts the user with a yes/no question about skipping
 * time-consuming algorithms (e.g., exhaustive search on large datasets).
 * It continues to prompt until a valid input is provided.
 * 
 * Acceptable inputs (case-insensitive):
 * - "yes", "y": returns true
 * - "no", "n": returns false
 * 
 * @return true If the user chooses to skip long-running algorithms.
 * @return false If the user chooses to include all algorithms.
 */
bool askSkipLongAlgorithms();

#endif //MODE_H
