//
// Created by carlo on 10/04/2025.
//

#ifndef MODE_UTILS_H
#define MODE_UTILS_H
#include <string>

/**
 * @brief Checks if a filename matches a given prefix and suffix pattern.
 * 
 * This utility function verifies if the input `filename` starts with the specified `prefix`
 * and ends with the specified `suffix`. It is typically used to validate file naming conventions.
 * 
 * @param filename The name of the file to check.
 * @param prefix The prefix that the filename should start with.
 * @param suffix The suffix that the filename should end with.
 * 
 * 
 * @return true If the filename starts with the given prefix and ends with the given suffix.
 * @return false Otherwise. 
 * 
 */
bool isFileValid(const std::string& filename, const std::string& prefix, const std::string& extension);

#endif //MODE_UTILS_H
