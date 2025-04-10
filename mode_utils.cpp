//
// Created by carlo on 10/04/2025.
//

#include "mode_utils.h"

bool isFileValid(const std::string& filename,const std::string& prefix, const std::string& suffix){
    bool valid = filename.size() > prefix.size() + suffix.size() &&
                       filename.substr(0, prefix.size()) == prefix &&
                       filename.substr(filename.size() - suffix.size()) == suffix;
    return valid;
}