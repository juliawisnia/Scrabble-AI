#include <iostream>
#include <fstream>
#include <vector>
#include <set>

int main(int argc, char *argv[]) {
    // not enough arguments
    if (argc < 2) return -1;

    std::ifstream ifile;
    ifile.open(argv[1]);

    // cannot open file
    if (ifile.fail()) return -1;

    // read in parameters from file
    int countries, rows, cols;
    ifile >> countries >> rows >> cols;

    if (countries > 15) return -1;
    if (rows > 80 || cols > 80) return -1;

    // character to read in graph
    char next;
    // graph of our input
    std::vector<std::vector<char> > graph;
    // set of the "names" of each country
    std::set<char> countryNames;
    graph.resize(rows, std::vector<char> (cols));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            ifile >> next;
            if (countryNames.find(next) == countryNames.end()) countryNames.insert(next);
            graph[i][j] = next;
        }
    }

    if (countries < 5) {
        std::set<char>::iterator it;
        int color = 1;
        for (it = countryNames.begin(); it != countryNames.end(); ++it) {
            std::cout << *it << " " << color;
            color++;
        }
        return 0;
    }
    return 0;
}