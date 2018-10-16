#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <vector>
#include "functor.h"

template <class T, class Comparator>
void merge (std::vector<T>& myArray, int l, int r, int m, Comparator comp) {
    int i = l, j = m + 1, k = 0;
    std::vector<T> temp;
    while (i <= m || j <= r) {
        if (i <= m && (j > r || comp(myArray[i], myArray[j]) ) ) {
            temp[k] = myArray[i];
            i++;
            k++;
        }
        else {
            temp[k] = myArray[i];
            j++;
            k++;
        }
    }
    for (int k = 0; k < r + l - 1; k++) {
        myArray[k + 1] = temp[k];
    }

   /* for (size_t k = 0; k < temp.size(); k++) {
        std::cout << "HI" << std::endl;
        std::cout << temp[k] << " ";
    }*/
    std::cout << std::endl;
}

template <class T, class Comparator>
void multMergeSort(std::vector<T>& myArray, int k, int low, int high, Comparator comp) {
    if (low < high) {
        int m = floor((high + low)/k);

        std::vector<int> index((high + low)/k);
        index[0] = low;
        index[index.size() - 1] = high;
        for (size_t i = 1; i < index.size() - 1; i++) {
            if (i % 2 == 0) index[i] = m*i;
            else index[i] = (m*i) + 1;
        }
        for (int i = 0; i < index.size() - 1; i++) {
            multMergeSort(myArray, k, index[i], index[i + 1], comp);
        }
        merge(myArray, low, high, m, comp);
    }
}

template <class T, class Comparator>
void mergeSort (std::vector<T>& myArray, int k, Comparator comp) {
    int low = 0;
    int high = myArray.size() - 1;
    multMergeSort(myArray, k, low, high, comp);
}


