#include <iostream>
#include <vector>
#include <stack>
#include <cmath>

void Merge(std::vector<std::pair<int, int> >* a, int l, int r, int m) {
    int i = 1, j = m + 1, k = 0;
    std::vector<std::pair<int, int> > temp;
    while (i <=m && (j > r || a->at(i).first <= a->at(j).first)) {
        if (i <= m || j <= r) {
            temp[k] = a->at(i);
            i++;
            k++;
        }
        else {
            temp.at(k).first = a->at(j).first;
            temp.at(k).second = a->at(j).second;
        }
        for (k = 0; k < r + l - 1; k++) {
           // if (temp.at(k).second > temp.at(k + 1).second) return false;
            a->at(k + 1) = temp.at(k);
        }
    }
}

void MergeSort(std::vector<std::pair<int, int> >& a, int l, int r) {
    if (l < r) {
        int m = floor((l+r)/2);
        MergeSort(a, l, m);
        MergeSort(a, m+1, r);
        Merge(&a, l, r, m);
    }
}

//bool FatalistHypothesis(std::vector<std::pair<int,int> > grades) {}
int main() {
    std::vector<std::pair<int, int> > grades;

    std::pair<int, int> add(80, 90);
    grades.push_back(add);

    std::pair<int, int> add1(70, 90);
    grades.push_back(add1);

    std::pair<int, int> add2(75, 90);
    grades.push_back(add2);

    MergeSort(grades, 0, 2);

   // for (int i = 0; i < 3; i++) std::cout << grades.at(i).first << std::endl;

}