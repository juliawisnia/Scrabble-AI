#include "CPUL.h"

std::string CPULStrategy(Board & board, Dictionary & dictionary, Player & player) {
	CPULQueue vertical;
	CPULQueue horizontal;

	std::string unused;
	std::set<Tile*>::iterator it;
	// say that every tile hasn't been used at first
	for (it = player.getHandTiles().begin(); it != player.getHandTiles().end(); ++it) {
		unused += (*it)->getLetter();
	}

	for (size_t i = 1; i <= board.getColumns(); i++) {
		for (size_t j = 1; j <= board.getRows(); j++) {
			CPULHelper(vertical, board, player, dictionary, i, j, false, "", "", unused);
			CPULHelper(horizontal, board, player, dictionary, i, j, true, "", "", unused);
		}
	}

	if (vertical.empty() && horizontal.empty()) {
		return "PASS";
	}

	if (vertical.empty() && !horizontal.empty()) return horizontal.top().second;
	if (!vertical.empty() && horizontal.empty()) return vertical.top().second;

	if (vertical.top().first > horizontal.top().first) return vertical.top().second;
	return horizontal.top().second;

}

void CPULHelper(CPULQueue & pq, Board & board, Player & player, Dictionary & dictionary, size_t col, size_t row, bool horizontal, 
	std::string word, std::string move, std::string unused) {

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
			try {
				if (horizontal) tempMove = new PlaceMove(col - word.size(), row, horizontal, move, &player);
				else tempMove = new PlaceMove(col, row - word.size(), horizontal, move, &player);
			}
			catch (MoveException & m) {
				if (tempMove != nullptr) player.addTiles(tempMove->tileVector());
				delete tempMove;
				return;
			}

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

			if (allLegalWords) pq.emplace(std::make_pair(move.size(), val));
			player.addTiles(tempMove->tileVector());
		}
	}
	if (unused.empty()) return;
	// we have no choice here, we must use it if it's on the board
	if (board.getSquare(col, row)->isOccupied()) {
		char c = board.getSquare(col, row)->getLetter();
		word += c;
		if (horizontal) CPULHelper(pq, board, player, dictionary, col + 1, row, horizontal, word, move, unused);
		else CPULHelper(pq, board, player, dictionary, col, row + 1, horizontal, word, move, unused);
		//word.erase(word.length() - 1);
	}

	else {
		for (size_t i = 0; i < unused.size(); i++) {
			// this letter is already in use
			char c = unused[i];

			if (c == '?') {
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

