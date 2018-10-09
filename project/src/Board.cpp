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
			delete scrabbleBoard[i-1][j-1];
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
		std::vector<Tile*> hand = m.getPlayer()->takeTiles(word, m.isWord());
		m.getPlayer()->eraseTilesFromHand(word);

		// concatanate all the vertical words
		size_t i = startColumn;
		size_t letters = word.size();
		size_t cnt = 0;
		while (cnt < letters) {
			unsigned int wMults = 1;
			unsigned int score = 0;
			size_t currRow = startRow - 1;
			if (currRow < 1) currRow = 1;

			// if there's already a square, you don't get points for the words formed above that
			if (getSquare(startRow, i)->isOccupied()) {
				i++;
				if (i > columns) break;
				continue;
			}
			
			// you are going to put down one of your tiles
			cnt++;	
			std::string currWord = "";
			while (getSquare(currRow, i)->isOccupied()) {
				currRow--;
				if (currRow < 1) break;
			}
			// start at occupied square
			currRow += 1;

			if (currRow != startRow) {
				while (getSquare(currRow, i)->isOccupied() || (currRow == startRow)) {
					size_t j = 0;
					if (getSquare(currRow, i)->isOccupied() && (currRow == startRow || currRow != startRow)) {
						currWord += getSquare(currRow, i)->getLetter();
						score += getSquare(currRow, i)->getScore();
					}

					// if currRow == startRow && it is not occupied
					else {
						unsigned int lMult = getSquare(currRow, i)->getLMult();
						wMults *= getSquare(currRow, i)->getWMult();
						score += lMult*(hand[j]->getPoints());
						currWord += word[j];
						j++; 
					}
				}
				score *= wMults;
				for (size_t i = 0; i < currWord.size(); i++) std::toupper(currWord[i]);
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
		while (k < word.size()) {
			if (getSquare(startRow, currCol)->isOccupied()) {
				mainWord += getSquare(startRow, currCol)->getLetter();
				mainScore += getSquare(startRow, currCol)->getScore();
			}

			else {
				unsigned int lMult = getSquare(startRow, currCol)->getLMult();
				wMult *= getSquare(startRow, currCol)->getWMult();
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
		std::vector<Tile*> hand = m.getPlayer()->takeTiles(word, m.isWord());
		m.getPlayer()->eraseTilesFromHand(word);

		// concatanate all the horizontal words
		size_t i = startRow;
		size_t letters = word.size();
		size_t cnt = 0;
		while (cnt < letters) {
			unsigned int wMults = 1;
			unsigned int score = 0;
			size_t currCol = startColumn - 1;
			if (currCol < 1) currCol = 1;

			// if already occupied, don't get points for words formed horizontally from it
			if (getSquare(i, startColumn)->isOccupied()) {
				i++;
				if (i > rows) break;
				continue;
			}

			cnt++;

			std::string currWord = "";
			while (getSquare(i, currCol)->isOccupied()) {
				currCol--;
				if (currCol < 1) break;
			}
			// start at occupied square
			currCol += 1;

			if (currCol != startColumn) {
				while (getSquare(i, currCol)->isOccupied() || (currCol == startColumn)) {
					size_t j = 0;
					if (getSquare(i, currCol)->isOccupied() && (currCol == startColumn || currCol != startColumn)) {
						currWord += getSquare(i, currCol)->getLetter();
						score += getSquare(i, currCol)->getScore();
					}

					// if currRow == startRow && it is not occupied
					else {
						unsigned int lMult = getSquare(i, currCol)->getLMult();
						wMults *= getSquare(i, currCol)->getWMult();
						score += lMult*(hand[j]->getPoints());
						currWord += word[j];
						j++; 
					}
				}
				score *= wMults;
				for (size_t i = 0; i < currWord.size(); i++) std::toupper(currWord[i]);
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
		while (k < word.size()) {
			if (getSquare(currRow, startColumn)->isOccupied()) {
				mainWord += getSquare(currRow, startColumn)->getLetter();
				mainScore += getSquare(currRow, startColumn)->getScore();
			}

			else {
				unsigned int lMult = getSquare(currRow, startColumn)->getLMult();
				wMult *= getSquare(currRow, startColumn)->getWMult();
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
			if (getSquare(row, col)->isOccupied()) {
				col++;
				continue;
			}
			// if you are at a blank space on the board
			else {
				if (place[cnt]->getLetter()=='?') {
					place[cnt]->useAs(place[cnt + 1]->getLetter());
					getSquare(row, col)->placeTile(place[cnt]);
					cnt+=2;
					continue;
					// go directly to next iteration, do not complete what is below
				}

				getSquare(row, col)->placeTile(place[cnt]);
				cnt++;
				col++;
			}
		}

		return;
	}

	else {
		while (cnt < letters) {
			// if you're at a square with a letter on it
			if (getSquare(row, col)->isOccupied()) {
				row++;
				continue;
			}
			// if you are at a blank space on the board
			else {
				if (place[cnt]->getLetter()=='?') {
					place[cnt]->useAs(place[cnt + 1]->getLetter());
					getSquare(row, col)->placeTile(place[cnt]);
					cnt+=2;
					continue;
					// go directly to next iteration, do not complete what is below
				}
				
				getSquare(row, col)->placeTile(place[cnt]);
				cnt++;
				row++;
			}
		}

		return;
	}

}

Square * Board::getSquare (size_t x, size_t y) const {
	return scrabbleBoard[y-1][x-1];
}

size_t Board::getRows() const {
	return rows;
}

size_t Board::getColumns() const {
	return columns;
}

bool Board::isFirstMove() const {
	if (scrabbleBoard[midy-1][midx-1]->isOccupied()) return false;

	else return true;
}

std::pair<size_t, size_t> Board::startPos() const {
	std::pair<size_t, size_t> middle (midx, midy);
	return middle;
}

/*std::vector<std::string> Board::noDuplicates(const PlaceMove &m) {
	std::vector<std::string> currTurnWords = m.getValidWords();

	// iterator for the vector of words formed from the play
	std::vector<std::string>::iterator wordIt;
	for (wordIt = currTurnWords.begin(); wordIt != currTurnWords.end(); ++wordIt) {

		std::set<std::string>::iterator it;
		for (it = wordsPlayed.begin(); it != wordsPlayed.end(); ++it) {

			// if there's a word that's already on the board in the list, delete it
			if ((*wordIt)==(*it)) {
				currTurnWords.erase(wordIt);
				break;
			}
		}
	}

	return currTurnWords;

}*/