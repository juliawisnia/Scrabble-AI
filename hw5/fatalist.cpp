#include <utility>
#include <functional>
#include <bits/stdc++.h>

bool sortSecond (std::pair<int, int> a, std::pair<int, int> b) {
    return (a.second < b.second);
}

bool FatalistHypothesis(std::vector<std::pair<int,int> > grades) {
    // if there are 0 or one grades, automatically true
    if (grades.size() == 0 || grades.size() == 1) return true;
    // first sort by CS104 grades, now check that CS170 grades are strictly greater
    sort(grades.begin(), grades.end());
    for (size_t i = 0; i < grades.size() - 1; i++) {
        if (grades[i].second > grades[i + 1].second) return false;
    }

    // now sort by CS170 grades, and check that CS104 grades are strictly greater
    sort(grades.begin(), grades.end(), sortSecond);
    for (size_t j = 0; j < grades.size() - 1; j++) {
        if (grades[j].first > grades[j + 1].first) return false;
    }

    // if neither function has returned, the hypothesis is true
    return true;
}