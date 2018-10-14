#include <iostream>
#include <string>
#include <cmath>

template <class T, class Comparator>
void merge (std::vector<T>* myArray, int l, int r, int m, Comparator comp) {
    int i = l, j = m + 1;
    std::vector<T> temp;
    while (i <= m || j <= r) {
        if (i <= m && (j > r || comp(myArray->at(i), myArray->at(j)))) {
            temp.push_back(myArray->at(i));
            i++;
        }
        else {
            temp.push_back(myArray->at(j));
            j++;
        }
    }
    for (int k = 0; k < r + l - 1; k++) {
        //myArray[k + 1] = temp[k];
    }
}

template <class T, class Comparator>
void multMergeSort(std::vector<T>& myArray, int k, int low, int high, Comparator comp) {
    if (low < high) {
        int m = ceil((high + low)/k);
        std::cout << m << std::endl;
        for (size_t i = low - 1; i <= high; i+=m) {
            //if (i + m > high) i = high - m;
            multMergeSort(myArray, k, i + 1, i + m, comp);
        }
        merge(&myArray, low, high, m, comp);
    }
}

/*template <class T, class Comparator>
void mergeSort (std::vector<T> myArray, int k, Comparator comp) {
    int low = 0;
    int high = myArray.size();
    multMergeSort(myArray, k, low, high, comp);
}
*/
