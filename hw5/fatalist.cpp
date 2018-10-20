#include "fatalist.h"
#include "msort.h"
#include <utility>
#include <bits/stdc++.h>

bool sortSecond (std::pair<int, int> a, std::pair<int, int> b) {
    return (a.second < b.second);
}

bool FatalistHypothesis(std::vector<std::pair<int,int> > grades) {
    // compares CS104 grades
    FirstComp compA;
    // compares CS170 grades 
    SecondComp compB;

    // first sort by CS104 grades, now check that CS170 grades are strictly greater
    sort(grades, 2, compA);
    for (size_t i = 0; i < grades.size() - 1; i++) {
        if (grades[i].second >= grades[i + 1].second) return false;
    }

    // now sort by CS170 grades, and check that CS104 grades are strictly greater
    sortSecond(grades, 2, compB);
    for (size_t j = 0; j < grades.size() - 1; j++) {
        if (grades[j].first >= grades[j + 1].second) return false;
    }

    // if neither function has returned, the hypothesis is true
    return true;
}

int main() {
    std::vector<std::pair<int, int> > grades;
    std::pair<int, int> add (90, 90);
    grades.push_back(add);
    std::pair<int, int> add1 (80, 80);
    grades.push_back(add1);
    std::pair<int, int> add2 (60, 60);
    grades.push_back(add2);
    std::pair<int, int> add3 (50, 50);
    grades.push_back(add3);
    std::pair<int, int> add4 (70, 70);
    grades.push_back(add4);

    bool a = FatalistHypothesis (grades);
    std::cout << a << std::endl;
    return 0;

}
