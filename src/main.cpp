#include "Record.hpp"
#include "Tree.hpp"
#include "Sorting.hpp"
#include "DataManage.hpp"
#include "TimeMeasure.hpp"

int main() {
    AVLTree<std::string, std::string> titleTree = loadTitles("datab.tsv");

    auto startSearch = std::chrono::high_resolution_clock::now();
    std::vector<Record> allMovies = mergeRatingToTitle("datar.tsv", titleTree);
    auto endSearch = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<double, std::milli> searchTime = endSearch - startSearch;
    std::cout<<"Czas przeszukiwania drzewa: "<<searchTime.count()<<" ms\n";

    // czyszczenie
    removeEmptyRating(allMovies);

    // rozmiary do testow
    std::vector<size_t> testSizes = {10000, 100000, 500000, 1000000, allMovies.size()};

    for(size_t limit : testSizes){
        std::vector<Record> probka(allMovies.begin(), allMovies.begin() + limit);

        double timeQS = measureTime(probka, quickSort);
        double timeMS = measureTime(probka, mergeSort);
        double timeBS = measureTime(probka, bucketSort);

        std::cout<<"Quick Sort:  "<<timeQS<<" ms" <<std::endl;
        std::cout<<"Merge Sort:  "<<timeMS<<" ms" <<std::endl;
        std::cout<<"Bucket Sort: "<<timeBS<<" ms" <<std::endl;

        // sortujemy
        bucketSort(probka); 

        // mediana
        double mediana = 0.0;
        if(limit % 2 == 0){
            mediana = (probka[limit / 2 - 1].rating + probka[limit / 2].rating) / 2.0;
        }
        else{
            mediana = probka[limit / 2].rating;
        }

        // średnia
        double suma = 0.0;
        for(const auto& rec : probka){
            suma += rec.rating;
        }
        double srednia = suma / limit;

        std::cout<<"Srednia: "<<srednia<<std::endl;
        std::cout<<"Mediana: "<<mediana<<std::endl;

        // zapis do pliku
        if(limit == allMovies.size()){
            AVLTree<double, std::string> finalTree; 

            for(const auto& rec : probka){
                finalTree.insert(rec.rating, rec.title); 
            }
            finalTree.saveToFile("sorted.tsv");
        }
    }
    return 0;
}