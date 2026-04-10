#include "Record.hpp"
#include "Sorting.hpp"
#include "DataManage.hpp"
#include "TimeMeasure.hpp"

int main(){
    std::unordered_map<std::string, std::string> titles = loadTitlesMap("title.basics.tsv/datab.tsv");
    std::vector<Record> r = mergeRatingToTitle("title.ratings.tsv/datar.tsv", titles);
    
    titles.clear();

    removeEmptyRating(r);

    double t1 = measureTime(r, quickSort);
    double t2 = measureTime(r, mergeSort);
    double t3 = measureTime(r, bucketSort);
    
    std::cout<<"QS: "<<t1<<std::endl;
    std::cout<<"MS: "<<t2<<std::endl;
    std::cout<<"BS: "<<t3<<std::endl;
    //saveFile(r, "sorted.tsv");
    
    return 0;
}