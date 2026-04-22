#include "DataManage.hpp"
#include "Record.hpp"
#include "Tree.hpp"

AVLTree<std::string, std::string> loadTitles(const std::string& filename) {
    AVLTree<std::string, std::string> tree;
    std::ifstream file(filename);
    std::string line;
    
    std::getline(file, line); 
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string tconst, tempType, title;
        std::getline(ss, tconst, '\t');
        std::getline(ss, tempType, '\t');
        std::getline(ss, title, '\t');
        
        tree.insert(tconst, title);
    }
    return tree;
}


std::vector<Record> loadRatings(const std::string& filename){
    std::vector<Record> ratings;
    std::ifstream file(filename);
    std::string line;

    std::getline(file, line); 
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string tconst, ratingStr;
        
        std::getline(ss, tconst, '\t');
        std::getline(ss, ratingStr, '\t');

        try {
            Record rec;
            rec.id = tconst;
            rec.rating = std::stod(ratingStr);
            ratings.push_back(rec);
        } catch (...) { continue; } 
    }
    return ratings;
}


void removeEmptyRating(std::vector<Record>& records){
    records.erase(
        std::remove_if(records.begin(), records.end(), [](const Record& rec){
            return rec.rating < 0.0;  
        } 
    ), records.end() );
}


void saveSortedData(const std::string& filename, const std::vector<Record>& sortedRatings, const AVLTree<std::string, std::string>& titleTree){
    std::ofstream outFile(filename);

    if(!outFile.is_open()){
        std::cerr << "Blad: Nie udalo sie otworzyc pliku " << filename << " do zapisu!\n";
        return;
    }

    for (const auto& rec : sortedRatings) {
        std::string* titlePtr = titleTree.search(rec.id);
        std::string title = (titlePtr != nullptr) ? *titlePtr : "Brak tytulu";
        outFile << rec.id << "\t" << rec.rating << "\t" << title << "\n";
    }
    outFile.close();
}