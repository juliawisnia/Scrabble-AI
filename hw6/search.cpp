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

    // char to create adjacency matrix
    char next;

    std::vector<std::vector<char> > adjacencyMatrix;
    adjacencyMatrix.resize(rows, std::vector<char> (cols));
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            ifile >> next;
            adjacencyMatrix[i][j] = next;
        }
    }
   
    // min to compare to;
    size_t largestCountry = -1;
    size_t currCountry = 0;

    std::queue<int> queue; 
    std::set<int> isVisited;

    char currLetter = adjacencyMatrix[0][0];

    queue.push(currLetter);
    isVisited.insert(currLetter);

    while (!queue.empty()) {
        char compLetter = queue.front();
        queue.pop();

        if (compLetter == currLetter) {
            
        }
    }

    std::cout << largestCountry << std::endl;
    return 0;
}



bool BFS(vector<vector<int> > adjacency_matrix, int start, int end) {
    if (start == end) return true;

    std::queue<int> queue; 
    std::set<int> isVisited;

    queue.push(start);
    isVisited.insert(start);

    while (!queue.empty()) {
        int search = queue.front();
        queue.pop();

        // found it!
        if (search == end) return true;

        for (size_t i = 0; i < adjacency_matrix.size(); i++) {
            if (adjacency_matrix[start][i] && isVisited.find(i) == isVisited.end()) {
                queue.push(i);
                isVisited.insert(i);
            }
        }
    }
    return false;
}