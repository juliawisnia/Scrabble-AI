#include "msort.h"
#include "functor.h"

bool comp(int a, int b) {
	return (a < b);
}

int main() {
    //NumStrComp comp;
    std::vector<int> array;
    array.push_back(6);
    array.push_back(3);
    array.push_back(4);
    array.push_back(1);
    array.push_back(2);
    array.push_back(7);
    array.push_back(5);
    // array.push_back("mno");
    // array.push_back("jkl");
    // array.push_back("stu");
    // array.push_back("mno");
    mergeSort(array, 2, comp);
    //selectionSort(array, 0, 6, comp);
    for (size_t i = 0; i < array.size(); i++) std::cout << array[i] << std::endl;
}