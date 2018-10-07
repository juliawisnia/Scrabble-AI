#include <vector>
#include <string>
#include "Move.h"

PlaceMove::PlaceMove (size_t x, size_t y, bool horizontal, std::string tileString, Player * p) {
	startRow = y;
	startColumn = x;
	word = tileString;
	player = p;
}

std::vector<Tile*> const & PlaceMove::tileVector () const {

}

void PlaceMove::execute(Board & board, Bag & bag, Dictionary & dictionary) {
	
}

void PlaceMove::isValidMove (Board & board, Dictionary & dictionary, Player * p) {
	size_t cols = board.getColumns();
	size_t rows = board.getRows();

	// player has necessary tiles
	while (!p->hasTiles()) {
		std::cout << "Error: you don't have the necessary tiles." << std::endl;
		enterNewMove();
	}

	// make sure that the first move is valid
	if (isFirstMove()) {
		std::pair<size_t, size_t> middle = board.startPos();

		// check that the move will take middle tile
		while ((horizontal && (middle[0] < startColumn || middle[0] > startColumn + word.size())) ||
				(!horizontal && (middle[1] < startRow || middle[1] > startRow + word.size()))) {

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
			if (startColumn > 0 && startColumn + word.size() - 1 <= cols && startRow > 0 && startRow <= rows) inbounds = true;
		}
		
		else {
			if (startRow > 0 && startRow + word.size() - 1 <= rows && startColumn > 0 && startColumn <= cols) inbounds = true;
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
			if (startColumn - 1 > 0 && board.getSquare(startColumn - 1, startRow).isOccupied()) adjacent = true;
			if (startColumn + word.size() + 1 <= cols && board.getSquare(startColumn + word.size() + 1,startRow).isOccupied()) adjacent = true;

			for (size_t i = startColumn; i < startColumn + word.size(); i++) {
				if (board.getSquare(i, startRow + 1).isOccupied() || board.getSquare(i, startRow - 1).isOccupied()) adjacent = true;
			}
		}

		else {
			// if it's coming before or after a word
			if (startRow - 1 > 0 && board.getSquare(startColumn, startRow - 1).isOccupied()) adjacent = true;
			if (startRow + 1 + word.size() <= rows && board.getSquare(startColumn, startRow + 1 + word.size()).isOccupied()) adjacent = true;

			for (size_t j = startColumn; j < startColumn + word.size(); j++) {
				if (board.getSquare(startColumn + 1, j).isOccupied() || board.getSquare(startColumn - 1, j).isOccupied()) adjacent = true;
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
				if (board.getSquare(i][startRow].isOccupied() || board.getSquare(i][startRow].isOccupied()) {

					std::cout << "Error: cannot overlap another word." << std::endl;
					enterNewMove();
					continue;
				}
			}

		}

		else {
			for (size_t j = startColumn; j < startColumn + word.size(); j++) {
				if (board.getSquare(startColumn][j].isOccupied() || board.getSquare(startColumn][j].isOccupied()) {

					std::cout << "Error: cannot overlap another word." << std::endl;
					enterNewMove();
					continue;
				}
			}
		}

		overlap = false;	
	}

	allWordsValid (board, dictionary);


	return;
}

void PlaceMove::allWordsValid(Board & board, Dictionary & dictionary) {
	std::vector<std::string> allWords;

	if (horizontal) {
		std::string horizontalWord = "";

		size_t horizontalLen = 1;
		currCol = startColumn + 1;

		while (board.getSquare(currCol][startRow].isOccupied()) {
			horizontalLen++;
			currCol++;
		}

		currCol = startColumn - 1;

		while (board.getSquare(currCol][startRow].isOccupied()) {
			horizontalLen++;
			currCol--;
		} 
		// make sure to start on occupied square
		currCol += 1;

		if (horizontalLen > 1) {
			for (size_t j = currCol; j < currCol + horizontalLen; j++) {
				horizontalWord += board.getSquare(j][startRow].getLetter();
			}

			allWords.push_back(horizontalWord);
		}

		// concatanate all the vertical words
		for (size_t i = startColumn; i < startColumn + word.size(); i++) {
			std::string currWord = "";

			size_t len = 1;
			currRow = startRow + 1;

			while (board.getSquare(i][currRow].isOccupied()) {
				len++;
				currRow++;
			}

			size_t currRow = startRow - 1;

			while (board.getSquare(i][currRow].isOccupied()) {
				len++;
				currRow--;
			}

			// make sure to start on an occupied square
			currRow += 1;

			if (len > 1) {
				for (size_t j = currRow; j < currRow + len; j++) {
					currWord += board.getSquare(i][j].getLetter();
				}

				allWords.push_back(currWord);
			}
		}

	}

	// concatanate all the horizontal words
	else {
		std::string verticalWord = "";

		size_t verticalLen = 1;
		currRow = startRow + 1;

		while (board.getSquare(startCol][currRow].isOccupied()) {
			verticalLen++;
			currRow++;
		}

		currRow = startRow - 1;

		while (board.getSquare(startCol][currRow].isOccupied()) {
			verticalLen++;
			currRow--;
		} 
		// make sure to start on occupied square
		currRow += 1;

		if (verticalLen > 1) {
			for (size_t j = currRow; j < currRow + verticalLen; j++) {
				verticalWord += board.getSquare(startCol][j].getLetter();
			}

			allWords.push_back(verticalWord);
		}

		for (size_t i = startRow i < startRow + word.size(); i++) {
			std::string currWord = "";

			size_t len = 1;
			currCol = startColumn + 1;
			while (board.getSquare(currCol][i].isOccupied()) {
				len++;
				currCol++;
			}

			size_t currCol = startColumn - 1;
			while (board.getSquare(currCol][i].isOccupied()) {
				len++;
				currCol--;
			}

			if (len > 1) {
				for (size_t j = 0; j < len; j++) {
					currWord += board.getSquare(currCol][j].getLetter();
					currRow++;
				}

				allWords.push_back(currWord);
			}
		}
	}

	bool legalWords = true;
	std::vector<string>::iterator it;

	for (it = allWords.begin(); it != allWords.end(); ++it) {
		if (!dictionary.isLegalWord(*it)) {
			std::cout << "Error: " << (*it) << " is not a legal word." << std::endl;
			legalWords = false;
		}
	}

	if (!legalWords) enterNewMove();
}

void PlaceMove::enterNewMove() {
	std::cout << "Enter new move: " << std::endl;

	char dir;
	std::cin >> dir >> startRow >> startColumn >> word;
firs
	if (dir == '-') horizontal = true;
	else horizontal = false;
}