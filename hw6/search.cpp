#include <iostream>
#include <ostream>
#include <fstream>
#include <stack>
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
    size_t letters, rows, cols;
    ifile >> letters >> rows >> cols;

    // min to compare to;
    //size_t largestCountry = -1;
    //size_t currCountry = 0;
    char next;
    std::vector<std::vector<char> > adjacencyMatrix;
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            ifile >> next;
            adjacencyMatrix[i][j] = next;
        }
    }
   
       for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            std::cout << adjacencyMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

    //std::cout << largestCountry << std::endl;
    return 0;
}