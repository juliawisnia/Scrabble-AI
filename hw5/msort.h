#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <queue>
#include <functional>
 
template <class T, class Comparator>
void selectionSort(std::vector<T>& array, int start, int end, Comparator comp) { 
    int minIndex = 0;
    for (int i = start; i < end + 1; i++) { 
	    minIndex = i; 
	    for (int j = i + 1; j < end + 1; j++) {
	    	if (comp(array[j], array[minIndex])) 
	        	minIndex = j; 
	    }
	   
	    std::swap(array[minIndex], array[i]); 
	} 
}

template <class T, class Comparator>
void merge (std::vector<T>& myArray, std::vector<std::pair<int, int> >& index,
			 Comparator comp) {
	int low = index[0].first;
	int high = index[index.size() - 1].second;

	std::vector<T> temp;

	while (!index.empty()) {
		// find min element
		T min = myArray[index[0].first];
		int minIndex = 0;
		for (size_t i = 1; i < index.size(); i++) {
			if (!comp(min, myArray[index[i].first])) {
				min = myArray[index[i].first];
				minIndex = i;
			}
		}

		// push min into temp
		temp.push_back(myArray[index[minIndex].first]);
		// increment the index where the min was found
		(index[minIndex].first)++;

		// means all elements from this partition have been placed
		if (index[minIndex].first > index[minIndex].second) {
			index.erase(index.begin() + minIndex);
		}
	}

	// fill myArray
	for (int k = 0; k < high + 1 - low; k++) myArray[k+low] = temp[k];
}

template <class T, class Comparator>
void multMergeSort(std::vector<T>& myArray, int k, int low, int high, Comparator comp) {
	if (low < high) {
		// vector of pairs to hold indicies
		std::vector<std::pair<int, int> > indicies;
		int m = (high - low + 1)/k;

		// push back partitioned indicies
		for (int i = 0; i < k; i++) {
			if (i == 0) {
				std::pair<int, int> addFirst(low, low + m - 1);
				indicies.push_back(addFirst);
			}
			else if (i == k - 1) {
				std::pair<int, int> addLast(indicies.back().second + 1, high);
				indicies.push_back(addLast);
			}
			else {
				std::pair<int, int> add(indicies.back().second + 1, indicies.back().second + m);
				indicies.push_back(add);
			}
        }

     	// look through all indicies
        for (size_t i = 0; i < indicies.size(); i++) {
        	// if it's at the minimum size -- less than k elements -- sort the fragment
        	if (indicies[i].second - indicies[i].first  + 1 < k) {
        		selectionSort(myArray, indicies[i].first, indicies[i].second, comp);
        	}
        	// keep calling function until small enough to use selectionSort
        	else {
        		multMergeSort(myArray, k, indicies[i].first, indicies[i].second, comp);
        	}
        }
        // call merge on partitions
        merge(myArray, indicies, comp);
	}
}

template <class T, class Comparator>
void mergeSort (std::vector<T>& myArray, int k, Comparator comp) {
    int low = 0;
    int high = myArray.size() - 1;
    multMergeSort(myArray, k, low, high, comp);
}
