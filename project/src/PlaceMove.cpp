#include <vector>
#include <string>
#include <iostream>
#include "Move.h"
#include "Board.h"

PlaceMove::PlaceMove (size_t x, size_t y, bool horizontal, std::string tileString, Player * p) {
	startRow = x;
	startColumn = y;
	word = tileString;
	player = p;
	this->horizontal = horizontal;
	take = player->takeTiles(tileString, true);
}

Player * PlaceMove::getPlayer() const {
	return player;
}

size_t PlaceMove::getRow() const {
	return startRow;
}

size_t PlaceMove::getColumn() const {
	return startColumn;
}

bool PlaceMove::getOrientation() const {
	return horizontal;
}

std::string PlaceMove::getString() const {
	return word;
}

std::vector<Tile*> const & PlaceMove::tileVector () const {
	return take;
}

void PlaceMove::execute(Board & board, Bag & bag, Dictionary & dictionary) {
	//isValidMove(board, dictionary);
	std::vector<std::pair<std::string, unsigned int>> result = board.getPlaceMoveResults(*this);
	board.executePlaceMove(*this);

	std::vector<std::pair<std::string, unsigned int>>::iterator it;
	
	size_t moveScore = 0;

	std::cout << "You have made the following words: ";
	for (it = result.begin(); it != result.end(); ++it) {
		std::cout << it->first << " ";
		moveScore += it->second;
	}
	std::cout << std::endl;

	if (word.size() == player->getMaxTiles()) player->score += 50;
	player->score += moveScore;

	std::cout << "You earned " << moveScore << " points on this turn." << std::endl;
	std::cout << "Your total score is now: " << player->score << std::endl;

	player->eraseTilesFromHand(word);

	std::vector<Tile*> newTiles = bag.drawTiles(word.size());
	std::vector<Tile*>::iterator tileIt;

	for (tileIt = newTiles.begin(); tileIt != newTiles.end(); ++tileIt) {
		player->Hand.insert(*tileIt);
	}
}

void PlaceMove::isValidMove (Board & board, Dictionary & dictionary) {
	size_t cols = board.getColumns();
	size_t rows = board.getRows();

	// player has necessary tiles
	bool flag = true;
	while (!(player->hasTiles(word, flag))) {
		std::cout << "Error: you don't have the necessary tiles." << std::endl;
		enterNewMove();
	}

	// make sure that the first move is valid
	if (board.isFirstMove()) {
		std::pair<size_t, size_t> middle = board.startPos();
		size_t xPos = std::get<0>(middle);
		size_t yPos = std::get<1>(middle);

		// check that the move will take middle tile
		while ((horizontal && (xPos < startColumn || xPos > startColumn + word.size())) ||
				(!horizontal && (yPos < startRow || yPos > startRow + word.size()))) {

			std::cout << "Error: must place tile on first square for starting turn" << std::endl;
			enterNewMove();
		}
		
		// check that user is putting down more than one tile
		while (word.size() < 2) {
			std::cout << "Error: must use more than one letter on your first turn." << std::endl;
			enterNewMove();
		}

		return;
	}

	bool inbounds = false;
	// check that it's in bounds
	while (!inbounds) {
		if (horizontal) {
			if (startColumn > 0 && (startColumn + word.size() - 1 <= cols) && startRow > 0 && startRow <= rows) inbounds = true;
		}
		
		else {
			if (startRow > 0 && (startRow + word.size() - 1 <= rows) && startColumn > 0 && startColumn <= cols) inbounds = true;
		}

		if (!inbounds) {
			std::cout << "Error: word is out of bounds." << std::endl;
			enterNewMove();
		}

	}

	bool adjacent = false;
	// must be touching another square 
	while (!adjacent) {
		if (horizontal) {
			// if it's coming before or after a word
			if (startColumn - 1 > 0 && board.getSquare(startRow, startColumn - 1)->isOccupied()) adjacent = true;
			if (startColumn + word.size() + 1 <= cols && board.getSquare(startRow, startColumn + word.size() + 1)->isOccupied()) adjacent = true;

			for (size_t i = startColumn; i < startColumn + word.size(); i++) {
				if (board.getSquare(startRow + 1, i)->isOccupied() || board.getSquare(startRow - 1, i)->isOccupied()) adjacent = true;
			}
		}

		else {
			// if it's coming before or after a word
			if (startRow - 1 > 0 && board.getSquare(startRow - 1, startColumn)->isOccupied()) adjacent = true;
			if (startRow + 1 + word.size() <= rows && board.getSquare(startRow + 1 + word.size(), startColumn)->isOccupied()) adjacent = true;

			for (size_t j = startColumn; j < startColumn + word.size(); j++) {
				if (board.getSquare(j, startColumn + 1)->isOccupied() || board.getSquare(j, startColumn - 1)->isOccupied()) adjacent = true;
			}

		}

		if (!adjacent) {
			std::cout << "Error: your word must touch another tile." << std::endl;
			enterNewMove();
		}
	}

	bool overlap = true;
	// cannot overlap other words
	while (overlap) {
		if (horizontal) {
			for (size_t i = startColumn; i < startColumn + word.size(); i++) {
				// if there is an overlap
				if (board.getSquare(startRow, i)->isOccupied() || board.getSquare(startRow, i)->isOccupied()) {

					std::cout << "Error: cannot overlap another word." << std::endl;
					enterNewMove();
					continue;
				}
			}

		}

		else {
			for (size_t j = startColumn; j < startColumn + word.size(); j++) {
				if (board.getSquare(j, startColumn)->isOccupied() || board.getSquare(j, startColumn)->isOccupied()) {

					std::cout << "Error: cannot overlap another word." << std::endl;
					enterNewMove();
					continue;
				}
			}
		}

		overlap = false;	
	}

	while(!allWordsValid (board, dictionary)) {}

	return;
}

bool PlaceMove::allWordsValid(Board & board, Dictionary & dictionary) {
	std::vector<std::pair<std::string, unsigned int>> wordAndScore = board.getPlaceMoveResults(*this);
	std::vector<std::string> allWords;

	std::vector<std::pair<std::string, unsigned int>>::iterator scoreIt;
	for (scoreIt = wordAndScore.begin(); scoreIt != wordAndScore.end(); ++scoreIt) {
		allWords.push_back(scoreIt->first);
	}

	bool legalWords = true;
	std::vector<std::string>::iterator it;

	for (it = allWords.begin(); it != allWords.end(); ++it) {
		if (!dictionary.isLegalWord(*it)) {
			std::cout << "Error: " << (*it) << " is not a legal word." << std::endl;
			legalWords = false;
		}
	}

	if (!legalWords) {
		enterNewMove();
		return false;
	}

	else {
		std::vector<std::string>::iterator it;
		size_t cnt = 0;
		for (it = allWords.begin(); it != allWords.end(); ++it) {
			allValidWords[cnt] = *it;
		}
		return true;
	}
}

std::vector<std::string> PlaceMove::getValidWords() const {
	return allValidWords;
}

void PlaceMove::enterNewMove() {
	std::cout << "Enter new move: " << std::endl;

	char dir;
	std::cin.clear();
	std::cin >> dir >> startRow >> startColumn >> word;

	if (dir == '-') horizontal = true;
	else horizontal = false;
}