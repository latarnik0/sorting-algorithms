#pragma once
#include "Record.hpp"
#include <vector>
#include <unordered_map>
#include <fstream>
#include <cstdlib>
#include <map>
#include <iostream>
#include <algorithm>
#include <sstream>    
#include "Tree.hpp"

AVLTree<std::string, std::string> loadTitles(const std::string& filename);
std::vector<Record> loadRatings(const std::string& filename);
void removeEmptyRating(std::vector<Record>& records);
void saveSortedData(const std::string& filename, const std::vector<Record>& sortedRatings, const AVLTree<std::string, std::string>& titleTree);