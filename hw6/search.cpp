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

    std::pair<int, int> add(0, 0);
    search.push(add);
    isVisited.insert(add);

    // min to compare to;
    int largestCountry = -1;
    int currCountry = 0;

    bool nextFound = false;
    int nextRow = 0;
    int nextCol = 0;

    while (!search.empty()) {
        int currRow = search.back().first;
        int currCol = search.back().second;
        char comp = graph[currRow][currCol];
        search.pop();

        if (currRow - 1 > 0) {
            std::pair<int, int> add(currRow - 1, currCol);
            if (graph[currRow - 1][currCol] == comp && isVisited.find(add) == isVisited.end()) {
                search.push(add);
                isVisited.insert(add);
                currCountry++;
            }
            else if (graph[currRow - 1][currCol] != comp && (isVisited.find(add) == isVisited.end()) && !nextFound) {
                nextFound = true;
                nextRow = currRow - 1;
                nextCol = currCol;
            }
        }

        if (currRow + 1 > 0) {
            std::pair<int, int> add(currRow + 1, currCol);
            if (graph[currRow + 1][currCol] == comp && isVisited.find(add) == isVisited.end()) {
                search.push(add);
                isVisited.insert(add);
                currCountry++;
            }
            else if (graph[currRow + 1][currCol] != comp && (isVisited.find(add) == isVisited.end()) && !nextFound) {
                nextFound = true;
                nextRow = currRow + 1;
                nextCol = currCol;
            }
        }

         if (currCol - 1 > 0) {
            std::pair<int, int> add(currRow, currCol + 1);
            if (graph[currRow][currCol - 1] == comp && isVisited.find(add) == isVisited.end()) {
                search.push(add);
                isVisited.insert(add);
                currCountry++;
            }
            else if (graph[currRow][currCol - 1] != comp && (isVisited.find(add) == isVisited.end()) && !nextFound) {
                nextFound = true;
                nextRow = currRow;
                nextCol = currCol - 1;
            }
        } 

        if (currCol + 1 > 0) {
            std::pair<int, int> add(currRow, currCol + 1);
            if (graph[currRow][currCol + 1] == comp && isVisited.find(add) == isVisited.end()) {
                search.push(add);
                isVisited.insert(add);
                currCountry++;
            }
            else if (graph[currRow][currCol + 1] != comp && (isVisited.find(add) == isVisited.end()) && !nextFound) {
                nextFound = true;
                nextRow = currRow;
                nextCol = currCol + 1;
            }
        }

        if (search.empty() && next) {
            // push that next to the queue
            std::pair<int, int> add(nextRow, nextCol);
            search.push(add);
            isVisited.insert(add);

            if (currCountry > largestCountry) largestCountry = currCountry;

            nextFound = false;

            currCountry = 0;
            currRow = nextRow;
            currCol = nextCol;
        }
    }

    std::cout << largestCountry << std::endl;
    return 0;
}