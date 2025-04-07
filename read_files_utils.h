//
// Created by ceraizi on 26-03-2025.
//

#ifndef READ_FILES_UTILS_H
#define READ_FILES_UTILS_H

#include <sstream>
#include <fstream>
#include <iostream>
#include "data_structures/Structures.h"
#include <unordered_map>
#include <string>
using namespace std;

/* Check if number in file is valid */
/**
 * @brief Checks if a given string represents a valid non-negative integer.
 *
 * This function verifies whether the input string consists entirely of digit characters.
 * It ensures that the string is not empty and contains only numeric characters (0-9).
 *
 * @param str The input string to validate.
 * @return `true` if the string represents a valid non-negative integer, otherwise `false`.
 *
 * @details
 * - The function uses `std::all_of` to check if all characters in the string are digits.
 * - An empty string is considered invalid.
 * - Negative numbers or numbers with non-digit characters are not considered valid.
 */
bool is_valid_integer(const string& str);

string get_truck_id(const string& filename);


#endif //READ_FILES_UTILS_H
