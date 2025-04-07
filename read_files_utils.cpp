//
// Created by ceraizi on 26-03-2025.
//
#include "read_files_utils.h"

bool is_valid_integer(const string& str) {
    return !str.empty() && all_of(str.begin(), str.end(), ::isdigit);
}

string get_truck_id(const string& filename) {
    char number[3]; // 2 digits + null terminator

    char *underscore = strrchr(filename, '_');
    if (underscore != NULL && strlen(underscore) >= 3) {
        strncpy(number, underscore + 1, 2); // copy 2 characters after '_'
        number[2] = '\0'; // null-terminate the string

        printf("Extracted number: %s\n", number);
    } else {
        printf("Could not extract number.\n");
    }

    return 0;
}
}