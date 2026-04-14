#pragma once
#include "Record.hpp"
#include <cmath>
#include <vector>

int partitionQS(std::vector<Record>& arr, int l, int r){
    Record pivot = arr[l]; 
    int i = l - 1;
    int j = r + 1;
    
    while(true){
        do{ 
            i++; 
        }while(arr[i].rating > pivot.rating);
        
        do{ 
            j--; 
        } while(arr[j].rating < pivot.rating);

        if(i>=j) return j;
        std::swap(arr[i], arr[j]);
    }
}

void quickSortRecursive(std::vector<Record>& arr, int l, int r){
    if(l<r){
        int p = partitionQS(arr, l, r);
        quickSortRecursive(arr, l, p);
        quickSortRecursive(arr, p + 1, r);
    }
}

// Wrapper
void quickSort(std::vector<Record>& arr){
    if(!arr.empty()){
        quickSortRecursive(arr, 0, arr.size() - 1);
    }
}


// MERGE SORT
void merge(std::vector<Record>& arr, int left, int mid, int right){
    int n1 = mid - left + 1;
    int n2 = right - mid;
    std::vector<Record> L(n1), R(n2);

    for(int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for(int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0;
    int k = left;

    while(i < n1 && j < n2){
        if (L[i].rating >= R[j].rating) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while(i < n1){
        arr[k] = L[i];
        i++;
        k++;
    }
    while(j < n2){
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSortRecursive(std::vector<Record>& arr, int left, int right){
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    mergeSortRecursive(arr, left, mid);
    mergeSortRecursive(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

// wrapper
void mergeSort(std::vector<Record>& arr){
    if(!arr.empty()){
        mergeSortRecursive(arr, 0, arr.size() - 1);
    }
}

// BUCKET SORT
void bucketSort(std::vector<Record>& arr){
    if (arr.empty()) return;
    std::vector<std::vector<Record>> buckets(101);

    for(const auto& rec : arr){
        int index = std::round(rec.rating * 10.0);
        if (index < 0) index = 0;
        if (index > 100) index = 100;

        buckets[index].push_back(rec);
    }

    int currentIndex = 0;
    
    for(int i = 100; i >= 0; i--){
        for (const auto& rec : buckets[i]) {
            arr[currentIndex] = rec;
            currentIndex++;
        }
    }
}