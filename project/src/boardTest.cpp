#include <iostream>
#include <sstream>
#include "Board.h"
#include "Tile.h"
#include "Square.h"
#include "Player.h"
#include "ConsolePrinter.h"

int main(int argc, char *argv[]) {
    std::stringstream ss(argv[1]);
    std::string boardConfig;
    ss >> boardConfig;

    Board board(boardConfig);
    ConsolePrinter console;
    console.printBoard(board);

    return 0;
}