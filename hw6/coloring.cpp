#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <queue>
#include <map>

struct country {
    char name;
    int color;
    std::set<country*> neighbors;
};

void findAllNeighbors(std::vector<country>& countries, std::vector<std::vector<char> > graph, int cols, int rows) {
    std::queue<std::pair<int, int> > search;
    std::set<std::pair<int, int> > isVisited;

    std::pair<int, int> first(0, 0);
    search.push(first);
    isVisited.insert(first);

    int nextRow = 0;
    int nextCol = 0;

    bool nextFound = false;
    std::vector<country>::iterator it;
    for (it = countries.begin(); it != countries.end(); ++it) {
        if (nextFound) {
            std::pair<int, int> again(nextRow, nextCol);
            search.push(again);
            isVisited.insert(again);
        }
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
                }
                else if (graph[currRow - 1][currCol] != comp && (isVisited.find(rowMinus) == isVisited.end())) {
                    std::vector<country>::iterator countryIt;
                    for (countryIt = countries.begin(); countryIt != countries.end(); ++countryIt) {
                        if (graph[currRow - 1][currCol] == countryIt->name) {
                            it->neighbors.insert(&(*countryIt));
                            break;
                        }
                    }
                    nextRow = currRow - 1;
                    nextCol = currCol;
                    nextFound = true;
                }
            }

            if (currRow + 1 < rows) {
                std::pair<int, int> rowPlus(currRow + 1, currCol);
                if (graph[currRow + 1][currCol] == comp && isVisited.find(rowPlus) == isVisited.end()) {
                    search.push(rowPlus);
                    isVisited.insert(rowPlus);
                }
                else if (graph[currRow + 1][currCol] != comp && (isVisited.find(rowPlus) == isVisited.end())) {
                   std::vector<country>::iterator countryIt;
                    for (countryIt = countries.begin(); countryIt != countries.end(); ++countryIt) {
                        if (graph[currRow + 1][currCol] == countryIt->name) {
                            it->neighbors.insert(&(*countryIt));
                            break;
                        }
                    }
                    nextRow = currRow + 1;
                    nextCol = currCol;
                    nextFound = true;
                }
            }

            if (currCol - 1 >= 0) {
                std::pair<int, int> colMinus(currRow, currCol - 1);
                if (graph[currRow][currCol - 1] == comp && isVisited.find(colMinus) == isVisited.end()) {
                    search.push(colMinus);
                    isVisited.insert(colMinus);
                }
                else if (graph[currRow][currCol - 1] != comp && (isVisited.find(colMinus) == isVisited.end())) {
                   std::vector<country>::iterator countryIt;
                    for (countryIt = countries.begin(); countryIt != countries.end(); ++countryIt) {
                        if (graph[currRow][currCol - 1] == countryIt->name) {
                            it->neighbors.insert(&(*countryIt));
                            break;
                        }
                    }
                    nextRow = currRow;
                    nextCol = currCol - 1;
                    nextFound = true;
                }
            } 

            if (currCol + 1 < cols) {
                std::pair<int, int> colPlus(currRow, currCol + 1);
                if (graph[currRow][currCol + 1] == comp && isVisited.find(colPlus) == isVisited.end()) {
                    search.push(colPlus);
                    isVisited.insert(colPlus);
                }
                else if (graph[currRow][currCol + 1] != comp && (isVisited.find(colPlus) == isVisited.end())) {
                    std::vector<country>::iterator countryIt;
                    for (countryIt = countries.begin(); countryIt != countries.end(); ++countryIt) {
                        if (graph[currRow][currCol + 1] == countryIt->name) {
                            it->neighbors.insert(&(*countryIt));
                            break;
                        }
                    }
                    nextRow = currRow;
                    nextCol = currCol + 1;
                    nextFound = true;
                }
            }
        }
    }
}

int main(int argc, char *argv[]) {
    // not enough arguments
    if (argc < 2) return -1;

    std::ifstream ifile;
    ifile.open(argv[1]);

    // cannot open file
    if (ifile.fail()) return -1;

    // read in parameters from file
    int numCountries, rows, cols;
    ifile >> numCountries >> rows >> cols;

    if (numCountries > 15) return -1;
    if (rows > 80 || cols > 80) return -1;

    // character to read in graph
    char next;
    // graph of our input
    std::vector<std::vector<char> > graph;
    graph.resize(rows, std::vector<char> (cols));
    std::vector<country> countries;
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            ifile >> next;
            graph[i][j] = next;

            std::vector<country>::iterator it;
            bool newCountry = true;
            for (it = countries.begin(); it != countries.end(); it++) {
                if (graph[i][j] == it->name) {
                    newCountry = false;
                    break;
                }
            }

            if (newCountry) {
                country add;
                add.name = graph[i][j];
                add.color = 1;
                countries.push_back(add);
            }
        }
    }

    findAllNeighbors(countries, graph, cols, rows);
    std::set<country*>::iterator it;
    for (size_t i = 0; i < countries.size(); i++) {
        for (it = countries[i].neighbors.begin(); it != countries[i].neighbors.end(); ++it) {
            if (countries[i].color == (*it)->color) {
                ((*it)->color)++;
            }
        }
    }

    for (size_t i = 0; i < countries.size(); i++) {
        std::cout << countries[i].name << " " << countries[i].color << std::endl;
    }
    
    return 0;
}