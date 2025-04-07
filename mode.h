//
// Created by ceraizi on 26-03-2025.
//

#ifndef MODE_H
#define MODE_H

#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;


string getMode();


/**
 * @brief Prompts the user to input a valid integer.
 *
 * This function repeatedly prompts the user for input, asking them to enter a valid integer. It ensures that the input is
 * a valid integer by checking the entire input string and using the `stoi` function to convert the string to an integer.
 * If the input is not a valid integer, the function will prompt the user again until a valid input is provided.
 *
 * @param prompt The message displayed to the user, prompting them for the integer input.
 *
 * @return A valid integer input provided by the user.
 *
 */
int getValidInteger(const string &prompt);

/**
 * @brief Handles user input for selecting the mode of operation and gathering necessary input data.
 *
 * This function allows the user to either read input from a file or enter the input manually. If the user chooses to read
 * from a file, the function attempts to read the input data from a file and validates the file's contents. If the user chooses
 * to input manually, the function prompts the user for various parameters (mode, source, destination, max walking time, avoid
 * nodes, avoid segments, and optional include node) and collects them into an `InputData` structure.
 *
 * @return An `InputData` structure containing the user's selected mode and input data.
 *
 */
InputData HandleUserInput();

#endif //MODE_H
