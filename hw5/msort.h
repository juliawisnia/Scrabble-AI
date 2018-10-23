#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <queue>
#include <functional>

// after split have a vector of vectors
// recursive calls
// still have vector of vectors, last vector has all remaining
// always need k pieces, call mergeSort on each subarray, now each subarray is sorted
// call merge, whole outer vector is sorted
template <class T, class Comparator>
void selectionSort(std::vector<T> sort, Comparator comp) { 
    int minIndex = 0; 
    for (int i = 0; i < sort.size() - 1; i++) { 
	    minIndex = i; 
	    for (int j = i + 1; j < sort.size(); j++) {
	    	if (comp(sort[j], sort[minIndex])) 
	        	minIndex = j; 
	    }
	   
	    swap(&sort[minIndex], &sort[i]); 
	} 
} 

template <class T, class Comparator>
void merge (std::vector<T>& myArray, std::vector<std::vector<T> >& subs, int m, Comparator comp) {
    std::vector<T> temp;
    for (size_t i = 0; i < subs.size(); i++) {
    	selectionSort(subs[i], comp);
    }
    // int low = index[0];
    // int high = index[index.size() - 1];

    // // priority queue acts as pointers, only stores myArray at each index
    // // & increments the index as we merge
    // std::priority_queue<T, std::vector<T>, std::greater<int>> pq;
    // for (size_t i = 0; i < index.size(); i++) {
    //     pq.emplace(myArray[index[i]]);
    // }

    // while (!pq.empty()) {
    //     T smallest = pq.top();
    //     std::cout << "smallest: " << smallest << std::endl;
    //     temp.push_back(smallest);
    //     pq.pop();
    //     for (size_t j = 0; j < index.size(); j++) {
    //         if (myArray[index[j]] == smallest) {
    //             index[j]++;
    //             // if one of the indicies reaches the end of that segment, break
    //             if (index[j] % m == 0) break;
    //             pq.emplace(myArray[index[j]]);
    //             std::cout << "break" << std::endl;
    //             break;
    //         }
    //     }

    // }
    // std::cout << std::endl;

    // // if (myArray.size() == temp.size()) myArray = temp;

    // //else {
    // 	for (int i = 0; i < high - low + 1; i++) myArray[i+low] = temp[i];
    // //}

}

template <class T, class Comparator>
void multMergeSort(std::vector<T>& myArray, std::vector<T>& array, int k, int low, int high, Comparator comp) {
	if (array.size() >= k) {
		std::vector<std::vector<T> > subArrays;
		int m = (array.size())/k;
		int rem = (array.size()) % k;

		for (int i = 0; i < k; i++) {
			std::vector<T> add;
			for (int j = m*i; j < m*(i+1); j++) {
				add.push_back(myArray[j]);
			}
			subArrays.push_back(add);
		}

		if (rem > 0) {
			std::vector<T> addLast = subArrays.top();
			subArrays.pop();
			for (int i = k*m; i < k*m + rem; i++) {
				addLast.push_back(myArray[i]);
			}
			subArrays.push_back(addLast);
		}

		for (size_t i = 0; i < subArrays.size(); i++) {
			multMergeSort(myArray, subArrays[i], k, low, high, comp);
		}
		merge(myArray, subArrays, k, m, comp);
	}
   //  if (low < high) {
   //      std::cout << "Low: " << low << " " << "High: " << high << std::endl;
   //      //int rem = (high - low + 1) % k;
   //      //if ((high - low + 1) % k != 0) rem = (high - low + 1) % k;
   //      //std::cout << "Rem: " << rem << std::endl;
        
   //      int m = (high - low + 1)/k;
   //      std::cout << "m: " << m << std::endl;
        
   //      std::vector<int> index;

   //      for (int i = 0; i < k; i++) {
   //          index.push_back(m*i + low);
   //      }

   //      std::cout << "Indicies: ";
   //      for (size_t i = 0; i < index.size(); i++) std::cout << index[i] << " ";
   //      	std::cout << std::endl;

   //      for (size_t i = 0; i < index.size() - 1; i++) {
			// multMergeSort(myArray, k, index[i], index[i + 1] - 1, comp);
   //      }
   //      multMergeSort(myArray, k, index[index.size() - 1], high, comp);
   //      merge(myArray, index, m, comp);
   //  }
}


template <class T, class Comparator>
void mergeSort (std::vector<T>& myArray, int k, Comparator comp) {
    int low = 0;
    int high = myArray.size() - 1;
    std::vector<T> array = myArray;
    multMergeSort(myArray, array, k, low, high, comp);
}