#include <iostream>
#include <ostream>
#include <fstream>
#include <queue>
#include <set>
#include <vector>

int main(int argc, char *argv[]) {
    // not enough arguments
    if (argc < 2) return -1;

    std::ifstream ifile;
    ifile.open(argv[1]);

    // cannot open file
    if (ifile.fail()) return -1;

    // read in parameters from file
    int letters, rows, cols;
    ifile >> letters >> rows >> cols;

    // char to create graph
    char next;

    std::vector<std::vector<char> > graph;
    graph.resize(rows, std::vector<char> (cols));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            ifile >> next;
            graph[i][j] = next;
        }
    }

    std::queue<std::pair<int, int> > search;
    std::set<std::pair<int, int> > isVisited;

    std::pair<int, int> first(0, 0);
    search.push(first);
    isVisited.insert(first);

    // min to compare to;
    int largestCountry = -1;
    int currCountry = 1;

    bool nextFound = false;
    int nextRow = 0;
    int nextCol = 0;

    while (!search.empty()) {
        int currRow = search.front().first;
        int currCol = search.front().second;
        char comp = graph[currRow][currCol];
        search.pop();

        if (currRow - 1 >= 0) {
            std::pair<int, int> rowMinus(currRow - 1, currCol);
            if (graph[currRow - 1][currCol] == comp && isVisited.find(rowMinus) == isVisited.end()) {
                search.push(rowMinus);
                isVisited.insert(rowMinus);
                currCountry++;
            }
            else if (graph[currRow - 1][currCol] != comp && (isVisited.find(rowMinus) == isVisited.end()) && !nextFound) {
                nextFound = true;
                nextRow = currRow - 1;
                nextCol = currCol;
            }
        }

        if (currRow + 1 < rows) {
            std::pair<int, int> rowPlus(currRow + 1, currCol);
            if (graph[currRow + 1][currCol] == comp && isVisited.find(rowPlus) == isVisited.end()) {
                search.push(rowPlus);
                isVisited.insert(rowPlus);
                currCountry++;
            }
            else if (graph[currRow + 1][currCol] != comp && (isVisited.find(rowPlus) == isVisited.end()) && !nextFound) {
                nextFound = true;
                nextRow = currRow + 1;
                nextCol = currCol;
            }
        }

         if (currCol - 1 >= 0) {
            std::pair<int, int> colMinus(currRow, currCol - 1);
            if (graph[currRow][currCol - 1] == comp && isVisited.find(colMinus) == isVisited.end()) {
                search.push(colMinus);
                isVisited.insert(colMinus);
                currCountry++;
            }
            else if (graph[currRow][currCol - 1] != comp && (isVisited.find(colMinus) == isVisited.end()) && !nextFound) {
                nextFound = true;
                nextRow = currRow;
                nextCol = currCol - 1;
            }
        } 

        if (currCol + 1 < cols) {
            std::pair<int, int> colPlus(currRow, currCol + 1);
            if (graph[currRow][currCol + 1] == comp && isVisited.find(colPlus) == isVisited.end()) {
                search.push(colPlus);
                isVisited.insert(colPlus);
                currCountry++;
            }
            else if (graph[currRow][currCol + 1] != comp && (isVisited.find(colPlus) == isVisited.end()) && !nextFound) {
                nextFound = true;
                nextRow = currRow;
                nextCol = currCol + 1;
            }
        }

        if (search.empty() && nextFound) {
            // push that next to the queue
            std::pair<int, int> nextOne(nextRow, nextCol);
            search.push(nextOne);
            isVisited.insert(nextOne);

            if (currCountry > largestCountry) largestCountry = currCountry;

            nextFound = false;
            currCountry = 1;
            currRow = nextRow;
            currCol = nextCol;
        }
    }

    std::cout << largestCountry << std::endl;
    return 0;
}