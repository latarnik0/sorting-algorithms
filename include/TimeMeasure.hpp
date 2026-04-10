#pragma once
#include "Record.hpp"
#include "Sorting.hpp"
#include <chrono>

template <typename SortFunction>
double measureTime(std::vector<Record> data, SortFunction sortFunc) {
    auto start = std::chrono::high_resolution_clock::now();
    sortFunc(data);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    return duration.count();
};
