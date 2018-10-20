#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <queue>
#include "functor.h"

template <class T, class Comparator>
void merge (std::vector<T>& myArray, std::vector<int>& index, int m, Comparator comp) {
    std::vector<T> temp;

    std::priority_queue<T, std::vector<T>, Comparator> pq;
    for (size_t i = 0; i < myArray.size(); i++) {
        pq.emplace(myArray[index[i]]);
    }

    while (!pq.empty()) {
        T smallest = pq.top();
        temp.push_back(smallest);
        pq.pop();
        for (size_t j = 0; j < index.size(); j++) {
            if (myArray[index[j]] == smallest) {
                index[j]++;
                if (index[j] % m == 0) break;
                pq.emplace(myArray[index[j]]);
                break;
            }
        }

    }

}

template <class T, class Comparator>
void multMergeSort(std::vector<T>& myArray, int k, int low, int high, Comparator comp) {
    if (low < high) {
        int rem = -1;
        if (myArray.size() % k != 0) rem = myArray.size() % k;
        
        int m = (myArray.size() - rem)/k;
        
        //int m = ceil((high + low)/k);
        std::vector<int> index;

        for (size_t i = 0; i < myArray.size()/k; i++) {
            index.push_back(m*i);
        }

        int cnt = rem;
        for (size_t j = index.size(); j++) {
            if (rem != 0) index[j] -= 1;
        }
 
        for (size_t i = 0; i < index.size() - 2; i+=2) {
            multMergeSort(myArray, k, index[i], index[i + 1], comp);
        }
        merge(myArray, index, m, comp);
    }
}

template <class T, class Comparator>
void mergeSort (std::vector<T>& myArray, int k, Comparator comp) {
    int low = 0;
    int high = myArray.size() - 1;
    multMergeSort(myArray, k, low, high, comp);
}