#include "CPUL.h"

std::string CPULStrategy(Board & board, Dictionary & dictionary, Player & player) {
	// priority queue sorting by score, type defined in CPUL.h
	CPULQueue vertical;
	CPULQueue horizontal;

	// given string of unused words from hand at any time
	std::string unused;
	std::set<Tile*>::iterator it;
	// say that every tile hasn't been used at first
	for (it = player.getHandTiles().begin(); it != player.getHandTiles().end(); ++it) {
		unused += (*it)->getLetter();
	}

	// iterate over ever square on the board, and call helper going in both directions of the board
	for (size_t i = 1; i <= board.getColumns(); i++) {
		for (size_t j = 1; j <= board.getRows(); j++) {
			CPULHelper(vertical, board, player, dictionary, i, j, false, "", "", unused);
			CPULHelper(horizontal, board, player, dictionary, i, j, true, "", "", unused);
		}
	}

	// if there were no moves for the AI to make, PASS
	if (vertical.empty() && horizontal.empty()) {
		return "PASS";
	}

	// only a move in the horizontal direction
	if (vertical.empty() && !horizontal.empty()) return horizontal.top().second;
	// only a move in the vertical direction
	if (!vertical.empty() && horizontal.empty()) return vertical.top().second;

	// moves going in both directions, choose the largest
	if (vertical.top().first > horizontal.top().first) return vertical.top().second;
	return horizontal.top().second;

}

void CPULHelper(CPULQueue & pq, Board & board, Player & player, Dictionary & dictionary, size_t col, size_t row, bool horizontal, 
	std::string word, std::string move, std::string unused) {

	// check to go out of bounds
	if (row > board.getRows() || col > board.getColumns()) return;

	TrieNode* check = dictionary.words.prefix(word);
	// not even a prefix, and string is not empty
	if (check == nullptr) {
		if (!word.empty()) return;
	}

	// it's a prefix
	else {
		// it's a word
		if (check->inSet) {
			std::vector<std::pair<std::string, unsigned int>> result;
			PlaceMove* tempMove = nullptr;
			// try to make a PlaceMove from current string of moves
			try {
				if (horizontal) tempMove = new PlaceMove(col - word.size(), row, horizontal, move, &player);
				else tempMove = new PlaceMove(col, row - word.size(), horizontal, move, &player);
			}
			catch (MoveException & m) {
				if (tempMove != nullptr) player.addTiles(tempMove->tileVector());
				delete tempMove;
				return;
			}
			// try and get results from move
			try {
				if (tempMove != nullptr) result = board.getPlaceMoveResults(*tempMove);
			}
			catch (MoveException & m) {
				if (tempMove != nullptr) player.addTiles(tempMove->tileVector());
				delete tempMove;
				return;
			}

			bool allLegalWords = true;
			std::vector<std::pair<std::string, unsigned int>>::iterator it;
			// make sure that all the words that have been created are valid
			for (it = result.begin(); it != result.end(); it++) {
				if (!dictionary.isLegalWord((*it).first)) {
					allLegalWords = false;
				}
			}
			// no exceptions thrown, it's a word
			std::string val;
			size_t startCol, startRow;
			if (horizontal) {
				startCol = col - word.size();
				startRow = row;
			}
			else {
				startCol = col;
				startRow = row - word.size();
			}
			val += "PLACE ";
			if (horizontal) val += "- ";
			else val += "| ";

			val += std::to_string(startRow);
			val += " ";
			val += std::to_string(startCol);
			val += " ";
			val += move;

			// only push to the queue if ALL words are valid
			if (allLegalWords) pq.emplace(std::make_pair(move.size(), val));
			player.addTiles(tempMove->tileVector());
			// no memory leaks
			delete tempMove;
		}
	}

	// we have no choice here, we must use it if it's on the board
	if (board.getSquare(col, row)->isOccupied()) {
		char c = board.getSquare(col, row)->getLetter();
		word += c;
		// we are not going to backtrack here, because we cannot opt out of using the letter on the board
		if (horizontal) CPULHelper(pq, board, player, dictionary, col + 1, row, horizontal, word, move, unused);
		else CPULHelper(pq, board, player, dictionary, col, row + 1, horizontal, word, move, unused);
	}

	else {
		for (size_t i = 0; i < unused.size(); i++) {
			// this letter is already in use
			char c = unused[i];

			if (c == '?') {
				// iterate over every letter, and backtrack to find every combination
				for (size_t j = 'a'; j <= 'z'; j++) {
					c = static_cast<char>(j);
					word += c;
					unused.erase(i, 1);
					// put the blank in front so the PlaceMove will know
					move += '?';
					move += c;

					if (horizontal) CPULHelper(pq, board, player, dictionary, col + 1, row, horizontal, word, move, unused);
					else CPULHelper(pq, board, player, dictionary, col, row + 1, horizontal, word, move, unused);

					// backtrack, look for new solution
					unused.insert(i, 1, c);
					move.erase(move.length() - 2, 2);
					word.erase(word.length() - 1, 1);				 
				}
			}

			else {
				word += c;
				unused.erase(i, 1);
				move += c;

				if (horizontal) CPULHelper(pq, board, player, dictionary, col + 1, row, horizontal, word, move, unused);
				else CPULHelper(pq, board, player, dictionary, col, row + 1, horizontal, word, move, unused);

				// backtrack, look for new solution
				unused.insert(i, 1, c);
				move.erase(move.length() - 1, 1);
				word.erase(word.length() - 1, 1);
			}

		}
	}
}

