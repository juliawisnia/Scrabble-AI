#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>

struct country {
    char name;
    int color;
    std::set<country*> neighbors;
    std::pair<int, int> start;
};

bool compare(country lhs, country rhs) {
    return (lhs.name < rhs.name);
}

bool goodNeighbors(country* curr) {
    // iterate through curr's neighbors and check against its own color
    std::set<country*>::iterator it;
    for (it = curr->neighbors.begin(); it != curr->neighbors.end(); ++it) {
        if ((*it)->color == curr->color) return false;
    }
    return true;
}

bool backtrack(country* curr, std::vector<country> &countries) {
    // base case, we've checked all the countries and neighbors
    if (curr == nullptr) return true;

    for (int i = 1; i < 5; i++) {
        // check if this will be a valid coloring
        curr->color = i;
        // create a search to look for all valid colors
        country* search = nullptr;
        // this coloring works for this country and its neighbors
        if (goodNeighbors(curr)) {
            for(int j = 0; j < (int) countries.size(); j++) {
                // we have not checked this country yet, search it next
                if(countries[j].color == -1) {
                    search = &countries[j];
                    break;
                }
            }
            
            if (backtrack(search, countries)) return true;
            else search->color = -1;
        }
    }

    return false;
}

void findAllNeighbors(std::vector<country>& countries, std::vector<std::vector<char> > graph, int cols, int rows) {
    // iterate through each country to find its neighbors
    std::vector<country>::iterator it;
    for (it = countries.begin(); it != countries.end(); ++it) {
        // create an individual stack and queue for each country
        std::queue<std::pair<int, int> > search;
        std::set<std::pair<int, int> > isVisited;

        search.push(it->start);
        isVisited.insert(it->start);

        char currCountry = it->name;

        while (!search.empty()) {
            int currRow = search.front().first;
            int currCol = search.front().second;

            search.pop();

            if (currRow - 1 >= 0) {
                std::pair<int, int> rowMinus(currRow - 1, currCol);
                // if its part of the same country, push it
                if (graph[currRow - 1][currCol] == currCountry && isVisited.find(rowMinus) == isVisited.end()) {
                    search.push(rowMinus);
                    isVisited.insert(rowMinus);
                }
                // it's a different country and adjacent, make it a neighbor
                else if (graph[currRow - 1][currCol] != currCountry && (isVisited.find(rowMinus) == isVisited.end())) {
                    std::vector<country>::iterator countryIt;
                    // find which country it's a part of, and push a pointer to that country
                    for (countryIt = countries.begin(); countryIt != countries.end(); ++countryIt) {
                        if (graph[currRow - 1][currCol] == countryIt->name) {
                            it->neighbors.insert(&(*countryIt));
                            break;
                        }
                    }
                }
            }

            if (currRow + 1 < rows) {
                std::pair<int, int> rowPlus(currRow + 1, currCol);
                if (graph[currRow + 1][currCol] == currCountry && isVisited.find(rowPlus) == isVisited.end()) {
                    search.push(rowPlus);
                    isVisited.insert(rowPlus);
                }
                else if (graph[currRow + 1][currCol] != currCountry && (isVisited.find(rowPlus) == isVisited.end())) {
                   std::vector<country>::iterator countryIt;
                    for (countryIt = countries.begin(); countryIt != countries.end(); ++countryIt) {
                        if (graph[currRow + 1][currCol] == countryIt->name) {
                            it->neighbors.insert(&(*countryIt));
                            break;
                        }
                    }
                }
            }

            if (currCol - 1 >= 0) {
                std::pair<int, int> colMinus(currRow, currCol - 1);
                if (graph[currRow][currCol - 1] == currCountry && isVisited.find(colMinus) == isVisited.end()) {
                    search.push(colMinus);
                    isVisited.insert(colMinus);
                }
                else if (graph[currRow][currCol - 1] != currCountry && (isVisited.find(colMinus) == isVisited.end())) {
                   std::vector<country>::iterator countryIt;
                    for (countryIt = countries.begin(); countryIt != countries.end(); ++countryIt) {
                        if (graph[currRow][currCol - 1] == countryIt->name) {
                            it->neighbors.insert(&(*countryIt));
                            break;
                        }
                    }
                }
            } 

            if (currCol + 1 < cols) {
                std::pair<int, int> colPlus(currRow, currCol + 1);
                if (graph[currRow][currCol + 1] == currCountry && isVisited.find(colPlus) == isVisited.end()) {
                    search.push(colPlus);
                    isVisited.insert(colPlus);
                }
                else if (graph[currRow][currCol + 1] != currCountry && (isVisited.find(colPlus) == isVisited.end())) {
                    std::vector<country>::iterator countryIt;
                    for (countryIt = countries.begin(); countryIt != countries.end(); ++countryIt) {
                        if (graph[currRow][currCol + 1] == countryIt->name) {
                            it->neighbors.insert(&(*countryIt));
                            break;
                        }
                    }
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
    
    // fill the graph, and add new countries to our vector as discovered
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
                add.color = -1;
                add.start.first = i;
                add.start.second = j;
                countries.push_back(add);
            }
        }
    }
    // fill each country struct with the neighbors
    findAllNeighbors(countries, graph, cols, rows);
    // std::set<country*>::iterator it2;
    // std::vector<country>::iterator it;
    // for (it = countries.begin(); it != countries.end(); ++it) {
    //     std::cout << (*it).name << ":";
    //     for (it2 = (*it).neighbors.begin(); it2 != (*it).neighbors.end(); ++it2) std::cout << " " << (*it2)->name;
    //     std::cout << std::endl;
    // }
    // check all valid colorings
    backtrack(&countries[0], countries);
    
    // sort countries by letter so it prints in alphabetical order
    std::sort(countries.begin(), countries.end(), compare);
    for (size_t i = 0; i < countries.size(); i++) {
        std::cout << countries[i].name << " " << countries[i].color << std::endl;
    }

    return 0;
}