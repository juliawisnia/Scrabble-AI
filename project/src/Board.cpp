#include <string>
#include <set>
#include <map>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include "Board.h"
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

	scrabbleBoard.resize(rows, std::vector<Square*>(columns));
	
	for (size_t i=1; i<=rows; i++) {
		for (size_t j=1; j<=columns; j++) {
			
			char mult;
			ifile >> mult;

			unsigned int LMult = 1;
			unsigned int WMult = 1;

			if (mult == 't') WMult = 3;
			else if (mult == '2') LMult = 2;
			else if (mult == 'd') WMult = 2;
			else if (mult == '3') LMult = 3;

			if (i == x && j == y) {
				scrabbleBoard[i-1][j-1] = new Square(LMult, WMult, true);
			}
			else {
				scrabbleBoard[i-1][j-1] = new Square(LMult, WMult, false);
			}
		}
	}
}

Board::~Board () {
	for (size_t i = 1; i <= rows; i++) {
		for (size_t j = 1; j <= columns; j++) {
			delete scrabbleBoard[j-1][i-1];
		}
	}
}

std::vector<std::pair<std::string, unsigned int>> Board::getPlaceMoveResults(const PlaceMove m) const {
	std::vector<std::pair<std::string, unsigned int>> allWords;
	size_t rows = getRows();
	size_t columns = getColumns();

	bool horizontal = m.getOrientation();

	if (horizontal) {
		size_t startColumn = m.getColumn();
		std::string word = m.getString();
		size_t startRow = m.getRow();

		std::string mainWord = "";
		bool flag = true;
		std::vector<Tile*> hand = m.getPlayer()->takeTiles(word, flag);

		// concatanate all the vertical words
		size_t i = startColumn;
		size_t letters = word.size();
		size_t cnt = 0;
		while (cnt < letters) {
			unsigned int wMults = 1;
			unsigned int score = 0;
			size_t currRow = startRow - 1;
			if (currRow < 1) currRow = 1;

			std::string currWord = "";
			while (getSquare(i, currRow)->isOccupied()) {
				currRow--;
				if (currRow < 1) break;
			}
			// start at occupied square
			currRow += 1;

			if ((getSquare(i, currRow + 1)->isOccupied()) || ((currRow + 1) == startRow)) {
				while (getSquare(i, currRow)->isOccupied() || (currRow == startRow)) {
					if (getSquare(i, currRow)->isOccupied()) {
						currWord += getSquare(i, currRow)->getLetter();
						score += getSquare(i, currRow)->getScore();
					}

					// if currRow == startRow && it is not occupied
					else if (currRow == startRow) {
						unsigned int lMult = getSquare(i, currRow)->getLMult();
						wMults *= getSquare(i, currRow)->getWMult();
						score += lMult*(hand[cnt]->getPoints());
						currWord += word[cnt];
						cnt++;
					}

					currRow++;
				}
				score *= wMults;
				for (size_t k = 0; k < currWord.size(); k++) std::toupper(currWord[k]);
				std::pair<std::string, unsigned int> add(currWord, score);
				allWords.push_back(add);
			}

			i++;
			if (i > columns) break;
		}

		// concatanate main horizontal word
		unsigned int wMult = 1;
		size_t k = 0;
		unsigned int mainScore = 0;
		size_t currCol = startColumn;

		while (getSquare(currCol, startRow)->isOccupied()) {
			currCol--;
			if (currCol < 1) break;
		}
		currCol += 1;

		while (k < letters) {
			if (getSquare(currCol, startRow)->isOccupied()) {
				mainWord += getSquare(currCol, startRow)->getLetter();
				mainScore += getSquare(currCol, startRow)->getScore();
			}

			else {
				unsigned int lMult = getSquare(currCol, startRow)->getLMult();
				wMult *= getSquare(currCol, startRow)->getWMult();
				mainScore += lMult*(hand[k]->getPoints());
				mainWord += word[k];
				k++;
			}

			currCol++;
			if (currCol > columns) break;
		}

		mainScore *= wMult;
		for (size_t i = 0; i < mainWord.size(); i++) std::toupper(mainWord[i]);
		std::pair<std::string, unsigned int> add(mainWord, mainScore);
		allWords.push_back(add);

	}

	// vertical
	else {
		size_t startColumn = m.getColumn();
		std::string word = m.getString();
		size_t startRow = m.getRow();

		std::string mainWord = "";
		bool flag = true;
		std::vector<Tile*> hand = m.getPlayer()->takeTiles(word, flag);

		// concatanate all the vertical words
		size_t i = startRow;
		size_t letters = word.size();
		size_t cnt = 0;
		while (cnt < letters) {
			unsigned int wMults = 1;
			unsigned int score = 0;
			size_t currCol = startColumn - 1;
			if (currCol < 1) currCol = 1;

			std::string currWord = "";
			while (getSquare(currCol, i)->isOccupied()) {
				currCol--;
				if (currCol < 1) break;
			}
			// start at occupied square
			currCol += 1;

			if (getSquare(currCol + 1, i)->isOccupied() || ((currCol + 1) == startColumn)) {
				while (getSquare(currCol, i)->isOccupied() || (currCol == startColumn)) {
					if (getSquare(currCol, i)->isOccupied()) {
						currWord += getSquare(currCol, i)->getLetter();
						score += getSquare(currCol, i)->getScore();
					}

					// if currRow == startRow && it is not occupied
					else if (currCol == startColumn) {
						unsigned int lMult = getSquare(currCol, i)->getLMult();
						wMults *= getSquare(currCol, i)->getWMult();
						score += lMult*(hand[cnt]->getPoints());
						currWord += word[cnt];
						cnt++;
					}

					currCol++;
				}
				score *= wMults;
				for (size_t k = 0; k < currWord.size(); k++) std::toupper(currWord[k]);
					std::pair<std::string, unsigned int> add(currWord, score);
					allWords.push_back(add);
			}

			i++;
			if (i > rows) break;
		}

		// concatanate main vertical word
		unsigned int wMult = 1;
		size_t k = 0;
		unsigned int mainScore = 0;
		size_t currRow = startRow;

		while (getSquare(startColumn, currRow)->isOccupied()) {
			currRow--;
			if (currRow < 1) break;
		}
		currRow += 1;

		while (k < letters) {
			if (getSquare(startColumn, currRow)->isOccupied()) {
				mainWord += getSquare(startColumn, currRow)->getLetter();
				mainScore += getSquare(startColumn, currRow)->getScore();
			}

			else {
				unsigned int lMult = getSquare(startColumn, currRow)->getLMult();
				wMult *= getSquare(startColumn, currRow)->getWMult();
				if (hand[k]->getLetter() == '?') {
					k += 2;
					mainWord += word[k];
					continue;
				}
				mainScore += lMult*(hand[k]->getPoints());
				mainWord += word[k];
				k++;
			}

			currRow++;
			if (currRow > rows) break;
		}

		mainScore *= wMult;
		for (size_t i = 0; i < mainWord.size(); i++) std::toupper(mainWord[i]);
		std::pair<std::string, unsigned int> add(mainWord, mainScore);
		allWords.push_back(add);
	}

	return allWords;
}

void Board::executePlaceMove (const PlaceMove & m) {
	std::string inputWord = m.getString();
	std::vector<Tile*> place = m.tileVector();
	std::vector<Tile*>::iterator it;

	size_t row = m.getRow();
	size_t col = m.getColumn();
	bool horizontal = m.getOrientation();

	size_t cnt = 0;
	size_t letters = place.size();
	if (horizontal) {
		while (cnt < letters) {
			// if you're at a square with a letter on it
			if (getSquare(col, row)->isOccupied()) {
				col++;
				continue;
			}
			// if you are at a blank space on the board
			else {
				if (place[cnt]->getLetter()=='?') {
					place[cnt]->useAs(inputWord[cnt + 1]);
					getSquare(col, row)->placeTile(place[cnt]);
					cnt+=1;
					continue;
					// go directly to next iteration, do not complete what is below
				}

				getSquare(col, row)->placeTile(place[cnt]);
				cnt++;
				col++;
			}
		}

		return;
	}

	else {
		while (cnt < letters) {
			// if you're at a square with a letter on it
			if (getSquare(col, row)->isOccupied()) {
				row++;
				continue;
			} 
			// if you are at a blank space on the board
			else {
				if (place[cnt]->getLetter()=='?') {
					place[cnt]->useAs(inputWord[cnt + 1]);
					getSquare(col, row)->placeTile(place[cnt]);
					cnt+=2;
					continue;
					// go directly to next iteration, do not complete what is below
				}
				
				getSquare(col, row)->placeTile(place[cnt]);
				cnt++;
				row++;
			}
		}

		return;
	}

}

Square * Board::getSquare (size_t x, size_t y) const {
	return scrabbleBoard[x-1][y-1];
}

size_t Board::getRows() const {
	return rows;
}

size_t Board::getColumns() const {
	return columns;
}

bool Board::isFirstMove() const {
	if (scrabbleBoard[midx-1][midy-1]->isOccupied()) return false;

	else return true;
}

std::pair<size_t, size_t> Board::startPos() const {
	std::pair<size_t, size_t> middle (midx, midy);
	return middle;
}