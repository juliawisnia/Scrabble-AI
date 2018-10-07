#include <string>
#include <set>
#include <map>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include "Tile.h"
#include "Square.h"
#include "Move.h"
#include "Dictionary.h"

Board::Board (std::string board_file_name) {
	std::ifstream ifile;
	ifile.open(board_file_name);

	if (ifile.fail()) {
		std::cout << "Error: Invalid board" << std::endl;
	}

	size_t x;
	size_t y;

	ifile >> rows >> columns >> x >> y;

	midx = x;
	midy = y;

	for (size_t i=1; i<=cols; i++) {
		for (size_t j=1; j<=rows; j++) {

			char mult;
			iifle >> mult;

			unsigned int LMult = 1;
			unsigned int WMult = 1;

			if (mult == 't') WMult = 3;
			else if (mult == '2') LMult = 2;
			else if (mult == 'd') WMult = 2;
			else if (mult == '3') LMult = 3;

			if (i == x && j == y) Square add(LMult, WMult, true);

			else Square add(LMult, WMult, false);

			scrabbleBoard[i][j]=add;
		}
	}
}

Board::~Board () {
}

std::vector<std::pair<std::string, unsigned int>> Board::getPlaceMoveResults(const PlaceMove &m) const {

}

void Board::executePlaceMove (const PlaceMove & m) {
	
}

Square * Board::getSquare (size_t x, size_t y) const {
	return board[y][x];
}

size_t Board::getRows() const {
	return rows;
}

size_t Board::getColumns() const {
	return columns;
}

bool Board::isFirstMove() const {
	if (scrabbleBoard[midy][midx].isOccupied()) return false;

	else return true;
}

std::pair<size_t, size_t> Board::startPos() const {
	std::pair<size_t, size_t> middle;
	middle(midy, midx);
}