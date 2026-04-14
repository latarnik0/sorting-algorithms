#include "Record.hpp"
#include "Sorting.hpp"
#include "DataManage.hpp"
#include "TimeMeasure.hpp"

int main() {
    std::unordered_map<std::string, std::string> titleMap = loadTitlesMap("datab.tsv");
    std::vector<Record> allMovies = mergeRatingToTitle("datar.tsv", titleMap);
    titleMap.clear();

    // czyszczenie
    removeEmptyRating(allMovies);

    // rozmiary do testow
    std::vector<size_t> testSizes = {10000, 100000, 500000, 1000000, allMovies.size()};

    for(size_t limit : testSizes){
        // jesli danych jest mniej niz podany limit
        size_t hardLimit = std::min(limit, allMovies.size());

        std::vector<Record> probka(allMovies.begin(), allMovies.begin() + hardLimit);

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
        if(hardLimit % 2 == 0){
            mediana = (probka[hardLimit / 2 - 1].rating + probka[hardLimit / 2].rating) / 2.0;
        }
        else{
            mediana = probka[hardLimit / 2].rating;
        }

        // średnia
        double suma = 0.0;
        for(const auto& rec : probka){
            suma += rec.rating;
        }
        double srednia = suma / hardLimit;

        std::cout<<"Srednia: "<<srednia<<std::endl;
        std::cout<<"Mediana: "<<mediana<<std::endl;

        // zapis do pliku
        if (limit == allMovies.size()) {
            saveFile(probka, "sorted.tsv");
        }
    }
    return 0;
}