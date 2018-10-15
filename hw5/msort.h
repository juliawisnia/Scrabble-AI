#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <vector>
#include "functor.h"

template <class T, class Comparator>
void merge (std::vector<T>& myArray, int l, int r, int m, Comparator comp) {
    int i = l, j = m + 1;
    std::vector<T> temp;
    while (i <= m || j <= r) {
        if (i <= m && (j > r || comp(myArray.at(i), myArray.at(j)))) {
            temp.push_back(myArray.at(i));
            i++;
        }
        else {
            temp.push_back(myArray.at(j));
            j++;
        }
    }
    for (int k = 0; k < r + l - 1; k++) {
        myArray[k + 1] = temp[k];
    }
}

template <class T, class Comparator>
void multMergeSort(std::vector<T>& myArray, int k, int low, int high, Comparator comp) {
    if (low < high) {
        int m = ceil((high + low)/k);
        int prevHigh = -1;
        for (int i = 0; i < (high - low)/k; i++) {
            multMergeSort(myArray, k, prevHigh + 1, m*i, comp);
            prevHigh = m*i;
        }
        merge(&myArray, low, high, m, comp);
    }
}

template <class T, class Comparator>
void mergeSort (std::vector<T>& myArray, int k, Comparator comp) {
    int low = 0;
    int high = myArray.size() - 1;
    multMergeSort(myArray, k, low, high, comp);
}

int main() {
    NumStrComp comp;
    std::vector<int> array;
    for (int i = 0; i < 10; i++) {
        array.push_back(rand() % 100);
    }
    mergeSort(array, 3, comp);
    for (int i = 0; i < 10; i++) std::cout << array[i] << std::endl;
}


