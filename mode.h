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

/**
 * @brief Prompts the user to input a valid mode of transportation.
 *
 * This function repeatedly asks the user to input either "driving" or "driving-walking" as the mode of transportation.
 * It ensures that the input is valid and only returns when a valid mode is provided.
 *
 * @return A string representing the chosen mode of transportation, either "driving" or "driving-walking".
 *
 */
string getMode();


/**
 * @brief Prompts the user to input a list of node IDs to avoid.
 *
 * This function allows the user to input a comma-separated list of node IDs to avoid. It parses the input string, converts the values
 * to integers, and stores them in an unordered set to ensure uniqueness. If the input is invalid, it will prompt the user again.
 *
 * @return An unordered set of integers representing the node IDs that should be avoided.
 *
 */
unordered_set<int> getAvoidNodes();

/**
 * @brief Prompts the user to input a list of segments (pairs of nodes) to avoid.
 *
 * This function allows the user to input a list of node pairs (segments) to avoid, where each segment is represented by two nodes,
 * separated by a comma and enclosed in parentheses (e.g., "(n1,n2)"). It parses the input string, converts the node values to integers,
 * and stores them as pairs in a vector. If the input format is incorrect, it will prompt the user to re-enter the data.
 *
 * @return A vector of pairs of integers representing the segments that should be avoided.
 *
 */
vector<pair<int, int>> getAvoidSegments();

/**
 * @brief Prompts the user to input a node ID to include.
 *
 * This function allows the user to input a single node ID to include in the route. If the user does not enter any input,
 * the function returns -1 to indicate that no node is specified. If the user enters an invalid value (not an integer),
 * the function prompts them to enter a valid integer.
 *
 * @return The node ID to include, or -1 if no node is specified.
 *
 */
int getIncludeNode();

/**
 * @brief Prompts the user to input the maximum walking time.
 *
 * This function asks the user to input the maximum walking time in minutes. If the user does not provide a value,
 * the function will repeatedly prompt for input until a valid integer is entered. The input must be a valid integer, and if
 * the input is invalid, the user will be prompted again.
 *
 * @return The maximum walking time in minutes as an integer.
 *
 */
int getMaxWalk();

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
