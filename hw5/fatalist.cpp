#include "fatalist.h"
#include "msort.h"

bool FatalistHypothesis(std::vector<std::pair<int,int> > grades) {
    // compares CS104 grades
    FirstComp compA;
    // compares CS170 grades 
    SecondComp compB;

    // first sort by CS104 grades, now check that CS170 grades are strictly greater
    mergeSort(grades, 2, compA);
    for (size_t i = 0; i < grades.size() - 1; i++) {
        if (grades[i].second >= grades[i + 1].second) return false;
    }

    // now sort by CS170 grades, and check that CS104 grades are strictly greater
    mergeSort(grades, 2, compB);
    for (size_t j = 0; j < grades.size() - 1; j++) {
        if (grades[j].first >= grades[j + 1].second) return false;
    }

    // if neither function has returned, the hypothesis is true
    return true;
}
