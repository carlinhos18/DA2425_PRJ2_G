//
// Created by ceraizi on 26-03-2025.
//

#ifndef READ_FILES_UTILS_H
#define READ_FILES_UTILS_H

#include <sstream>
#include <iostream>
#include "data_structures/structures.h"
#include <string>
#include <algorithm>
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


/**
 * 
 * @brief Extracts the truck ID from a given filename.
 * 
 * This function parses a filename of the format "prefix_ID.suffix" and extracts the ID portion,
 * which is the substring between the last underscore ('_') and the last dot ('.').
 * 
 * For example, given the input `"TruckAndPallets_05.csv"`, the function will return `"05"`.
 *
 * @param filename The name of the file to extract the truck ID from.
 * @return string The extracted truck ID, or an empty string if the format is invalid.  
 * 
 */
string get_truck_id(const string& filename);


#endif //READ_FILES_UTILS_H
