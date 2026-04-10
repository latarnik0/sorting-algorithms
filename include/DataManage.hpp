#pragma once
#include "Record.hpp"
#include <vector>
#include <unordered_map>
#include <fstream>
#include <cstdlib>
#include <map>
#include <iostream>
#include <algorithm>

std::unordered_map<std::string, std::string> loadTitlesMap(const std::string& filename);
std::vector<Record> mergeRatingToTitle(const std::string& ratingsFilename, const std::unordered_map<std::string, std::string>& titleMap);
void removeEmptyRating(std::vector<Record>& records);
void saveFile(const std::vector<Record>& records, const std::string& filename);