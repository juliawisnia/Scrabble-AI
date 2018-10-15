#include "msort.h"

int main() {
    NumStrComp comp;
    std::vector<std::string> array;
    array.push_back("ghi");
    array.push_back("pqr");
    array.push_back("def");
    array.push_back("abc");
    array.push_back("mno");
    array.push_back("jkl");
    mergeSort(array, 3, comp);
    for (size_t i = 0; i < array.size(); i++) std::cout << array[i] << std::endl;
}