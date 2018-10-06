#include <vector>
#include <string>
#include "Tile.h"
#include "Player.h"
#include "Bag.h"
#include "Dictionary.h"

PlaceMove::PlaceMove (size_t x, size_t y, bool horizontal, std::string tileString, Player * p) {
	startRow = x;
	startColumn = y;
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
		std::cout << "Enter new move: " << std::endl;

		char dir;
		std::cin >> dir >> startRow >> startColumn >> word;

		if (dir == '-') horizontal = true;
		else horizontal = false;
	}

	// make sure that the first move is valid
	if (isFirstMove()) {
		std::pair<size_t, size_t> middle = board.startPos();

		// check that the move will take middle tile
		while ((horizontal && (middle[0] < startRow || middle[0] > startRow + word.size())) ||
				(!horizontal && (middle[1] < startColumn || middle[1] > startColumn + word.size()))) {

			std::cout << "Error: must place tile on first square for starting turn" << std::endl;
			std::cout << "Enter new move: " << std::endl;

			char dir;
			std::cin >> dir >> startRow >> startColumn >> word;

			if (dir == '-') horizontal = true;
			else horizontal = false;
		}
		
		// check that user is putting down more than one tile
		while (word.size() < 2) {
			std::cout << "Error: must use more than one letter on your first turn." << std::endl;
			std::cout << "Enter new move: " << std::endl;

			char dir;
			std::cin >> dir >> startRow >> startColumn >> word;

			if (dir == '-') horizontal = true;
			else horizontal = false;
		}

		return;
	}

	bool inbounds = false;
	// check that it's in bounds
	while (!inbounds) {
		if (horizontal) {
			if (startColumn > 0 && startColumn + word.size() - 1 <= cols && startRow > 0) inbounds = true;
		}
		
		else {
			if (startRow > 0 && startRow + word.size() - 1 <= rows && startColumn > 0) inbounds = true;
		}

		if (!inbounds) {
			std::cout << "Error: word is out of bounds." << std::endl;
			std::cout << "Enter new move: " << std::endl;

			char dir;
			std::cin >> dir >> startRow >> startColumn >> word;

			if (dir == '-') horizontal = true;
			else horizontal = false;
		}

	}

	bool adjacent = false;
	// must be touching another square 
	while (!adjacent) {
		if (horizontal) {
			// if it's coming before or after a word
			if (startColumn - 1 > 0 && board[startRow][startColumn - 1].isOccupied) adjacent = true;
			if (startColumn + word.size() + 1 <= cols && board[startRow][startColumn + word.size() + 1].isOccupied()) adjacent = true;

			for (size_t i = startColumn; i < startColumn + word.size(); i++) {
				if (board[startRow + 1][i].isOccupied() || board[startRow - 1][i].isOccupied()) adjacent = true;
			}
		}

		else {
			// if it's coming before or after a word
			if (startRow - 1 > 0 && board[startRow - 1][startColumn].isOccupied()) adjacent = true;
			if (startRow + 1 + word.size() <= rows && board[startRow + 1 + word.size()][startColumn].isOccupied()) adjacent = true;

			for (size_t j = startColumn; j < startColumn + word.size(); j++) {
				if (board[j][startColumn + 1].isOccupied() || board[j][startColumn - 1].isOccupied()) adjacent = true;
			}

		}

		if (!adjacent) {
			std::cout << "Error: your word must touch another tile." << std::endl;
			std::cout << "Enter new move: " << std::endl;

			char dir;
			std::cin >> dir >> startRow >> startColumn >> word;

			if (dir == '-') horizontal = true;
			else horizontal = false;
		}
	}

	bool overlap = true;
	// cannot overlap other words
	while (overlap) {
		if (horizontal) {
			for (size_t i = startColumn; i < startColumn + word.size(); i++) {
				// if there is an overlap
				if (board[startRow][i].isOccupied() || board[startRow][i].isOccupied()) {

					std::cout << "Error: cannot overlap another word." << std::endl;
					std::cout << "Enter new move: " << std::endl;

					char dir;
					std::cin >> dir >> startRow >> startColumn >> word;

					if (dir == '-') horizontal = true;
					else horizontal = false;

					continue;
				}
			}

		}

		else {
			for (size_t j = startColumn; j < startColumn + word.size(); j++) {
				if (board[j][startColumn].isOccupied() || board[j][startColumn].isOccupied()) {

					std::cout << "Error: cannot overlap another word." << std::endl;
					std::cout << "Enter new move: " << std::endl;

					char dir;
					std::cin >> dir >> startRow >> startColumn >> word;

					if (dir == '-') horizontal = true;
					else horizontal = false;

					continue;
				}
			}
		}

		overlap = false;	
	}

	return;
}