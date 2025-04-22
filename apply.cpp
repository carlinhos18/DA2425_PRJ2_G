//
// Created by carlo on 11/04/2025.
//
#include "data_structures/structures.h"
#include "algorithms.cpp"


void apply(OutputData &output, Algorithm &data, const InputData& input){
    const string algorithm = input.algorithm;

    if (algorithm == "exhaustive") {
        exhaustive(output, data);
    }
    if (algorithm == "dynamic programming") {

    }
    if (algorithm == "approximation") {

    }
    if (algorithm == "integer linear programming") {

    }
    weight_used(output);
}