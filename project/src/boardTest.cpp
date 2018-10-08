#include <iostream>
#include <sstream>
#include "Board.h"
#include "Tile.h"
#include "Square.h"
#include "ConsolePrinter.h"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "No file specified" << std::endl;
        return -1;
    }
    
    std::stringstream ss(argv[1]);
    std::string boardConfig;
    ss >> boardConfig;

    Board board(boardConfig);
    ConsolePrinter console;
    console.printBoard(board);

    return 0;
}