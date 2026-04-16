#include "DataManage.hpp"
#include "Record.hpp"
#include "Tree.hpp"

AVLTree<std::string, std::string> loadTitles(const std::string& filename){
    AVLTree<std::string, std::string> titleTree;
    std::ifstream file(filename);
    std::string line;

    if(!file.is_open()){
        std::cerr << "Blad otwarcia pliku " << filename << std::endl;
        return titleTree;
    }

    std::getline(file, line);

    while(std::getline(file, line)){
        if (line.empty()) continue;
        size_t tab1 = line.find('\t');
        if(tab1 != std::string::npos){
            std::string tconst = line.substr(0, tab1);

            size_t tab2 = line.find('\t', tab1 + 1);
            if(tab2 != std::string::npos){
                size_t tab3 = line.find('\t', tab2 + 1);
                
                std::string title = line.substr(tab2 + 1, tab3 - tab2 - 1);
                titleTree.insert(tconst, title);
            }
        }
    }
    return titleTree;
}



std::vector<Record> mergeRatingToTitle(const std::string& ratingsFilename, const AVLTree<std::string, std::string>& titleTree){
    std::vector<Record> records;
    std::ifstream file(ratingsFilename);
    std::string line;

    if(!file.is_open()){
        std::cerr << "Blad otwarcia pliku " << ratingsFilename << std::endl;
        return records;
    }
    std::getline(file, line);

    while(std::getline(file, line)){
        if (line.empty()) continue;
        size_t tabPos = line.find('\t');
        if (tabPos != std::string::npos) {
            std::string tconst = line.substr(0, tabPos);
            
            size_t tab2Pos = line.find('\t', tabPos + 1);
            std::string ratingStr = line.substr(tabPos + 1, tab2Pos - tabPos - 1);

            Record rec;
            std::string* foundTitle = titleTree.search(tconst); 
            if (foundTitle != nullptr) {
                rec.title = *foundTitle; 
            } 
            else{
                rec.title = "Brak tytułu"; 
            }

            if(ratingStr.empty() || ratingStr == "\\N"){
                rec.rating = -1.0; 
            }
            else{
                try{
                    rec.rating = std::stod(ratingStr);
                } catch (...) {
                    rec.rating = -1.0;
                }
            }

            records.push_back(rec);
        }
    }
    return records;
}


void removeEmptyRating(std::vector<Record>& records){
    records.erase(
        std::remove_if(records.begin(), records.end(), [](const Record& rec){
            return rec.rating < 0.0;  
        } 
    ), records.end() );
}


void saveFile(const std::vector<Record>& records, const std::string& filename){
    std::multimap<double, std::string, std::greater<double>> tree;

    for(const auto& rec : records){
        tree.insert({rec.rating, rec.title});
    }

    std::ofstream outFile(filename);
    
    if(!outFile.is_open()){
        std::cerr<<"Nie mozna utworzyc pliku "<< std::endl;
        return;
    }

    for(const auto& node : tree){
        outFile << node.first << "\t" << node.second << "\n";
    }
    outFile.close();
}