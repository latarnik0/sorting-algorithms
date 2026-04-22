#include "Record.hpp"
#include "Tree.hpp"
#include "Sorting.hpp"
#include "DataManage.hpp"
#include "TimeMeasure.hpp"

int main() {

    auto startSearchT = std::chrono::high_resolution_clock::now();
    AVLTree<std::string, std::string> titleTree = loadTitles("datab.tsv"); 
    auto endSearchT = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<double, std::milli> loadTimeT = endSearchT - startSearchT;
    std::cout << "Czas wczytywania tytulow: " << loadTimeT.count() << " ms\n";

    auto startSearch = std::chrono::high_resolution_clock::now();
    std::vector<Record> allMovies = loadRatings("datar.tsv"); 
    auto endSearch = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<double, std::milli> loadTime = endSearch - startSearch;
    std::cout << "Czas wczytywania ratingow: " << loadTime.count() << " ms\n";

    removeEmptyRating(allMovies);

    // Rozmiary do testow
    std::vector<size_t> testSizes = {10000, 100000, 500000, 1000000, allMovies.size()};

    for(size_t limit : testSizes) {
        std::cout << "\n=== TEST DLA " << limit << " REKORDOW ===" << std::endl;
        std::vector<Record> probka(allMovies.begin(), allMovies.begin() + limit);

        // Pomiary czasu
        double timeQS = measureTime(probka, quickSort);
        double timeMS = measureTime(probka, mergeSort);
        double timeBS = measureTime(probka, bucketSort);

        std::cout << "Quick Sort:  " << timeQS << " ms" << std::endl;
        std::cout << "Merge Sort:  " << timeMS << " ms" << std::endl;
        std::cout << "Bucket Sort: " << timeBS << " ms" << std::endl;

        // Ostateczne sortowanie próbki
        bucketSort(probka); 

        // Obliczanie mediany
        double mediana = 0.0;
        if(limit % 2 == 0) {
            mediana = (probka[limit / 2 - 1].rating + probka[limit / 2].rating) / 2.0;
        } else {
            mediana = probka[limit / 2].rating;
        }

        // Obliczanie średniej
        double suma = 0.0;
        for(const auto& rec : probka){
            suma += rec.rating;
        }
        double srednia = suma / limit;

        std::cout << "Srednia: " << srednia << std::endl;
        std::cout << "Mediana: " << mediana << std::endl;

        // Zapis do pliku 
        if(limit == allMovies.size()) {
            saveSortedData("sorted.tsv", probka, titleTree);
        }
    }
    return 0;
}