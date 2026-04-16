#pragma once
#include "Record.hpp"
#include <vector>
#include <unordered_map>
#include <fstream>
#include <cstdlib>
#include <map>
#include <iostream>
#include <algorithm>
#include "Tree.hpp"

AVLTree<std::string, std::string> loadTitles(const std::string& filename);
std::vector<Record> mergeRatingToTitle(const std::string& ratingsFilename, const AVLTree<std::string, std::string>& titleTree);
void removeEmptyRating(std::vector<Record>& records);