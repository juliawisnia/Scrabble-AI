#include "CPUS.h"

std::string CPUSStrategy(Board & board, Dictionary & dictionary, Player & player) {
	CPUSQueue vertical;
	CPUSQueue horizontal;

	std::string unused;
	std::set<Tile*>::iterator it;
	// say that every tile hasn't been used at first
	for (it = player.getHandTiles().begin(); it != player.getHandTiles().end(); ++it) {
		unused += (*it)->getLetter();
	}

	// iterates over every square on board calling the helper in both directions
	for (size_t i = 1; i <= board.getColumns(); i++) {
		for (size_t j = 1; j <= board.getRows(); j++) {
			CPUSHelper(vertical, board, player, dictionary, i, j, false, "", "", unused);
			CPUSHelper(horizontal, board, player, dictionary, i, j, true, "", "", unused);
		}
	}

	// no valid moves, so PASS
	if (vertical.empty() && horizontal.empty()) {
		return "PASS";
	}

	// no vertical moves
	if (vertical.empty() && !horizontal.empty()) return horizontal.top().second;
	// no horizontal moves
	if (!vertical.empty() && horizontal.empty()) return vertical.top().second;

	// moves in both direction, choose higher scoring one
	if (vertical.top().first > horizontal.top().first) return vertical.top().second;
	return horizontal.top().second;

}

void CPUSHelper(CPUSQueue & pq, Board & board, Player & player, Dictionary & dictionary, size_t col, size_t row, bool horizontal, 
	std::string word, std::string move, std::string unused) {

	// return if we are out of bounds
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
			// create a string that ParseMove can read
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

			size_t points = getTotalScore(result);
			size_t numLetters = 0;
			for (size_t i = 0; i < move.size(); i++) if (move[i] != '?') numLetters++;
			// 50 point bonus if they use maximum number of tiles
			if (player.getHandTiles().size() == 0 && numLetters == player.getMaxTiles()) points += 50;
			if (allLegalWords) pq.emplace(std::make_pair(points, val));
			player.addTiles(tempMove->tileVector());
			delete tempMove;
		}
	}
	if (unused.empty()) return;
	// we have no choice here, we must use it if it's on the board
	if (board.getSquare(col, row)->isOccupied()) {
		char c = board.getSquare(col, row)->getLetter();
		word += c;
		if (horizontal) CPUSHelper(pq, board, player, dictionary, col + 1, row, horizontal, word, move, unused);
		else CPUSHelper(pq, board, player, dictionary, col, row + 1, horizontal, word, move, unused);
	}

	else {
		for (size_t i = 0; i < unused.size(); i++) {
			// this letter is already in use
			char c = unused[i];

			if (c == '?') {
				// iterate over every possible letter that it could be to determine best move
				for (size_t j = 'a'; j <= 'z'; j++) {
					c = static_cast<char>(j);
					word += c;
					unused.erase(i, 1);
					// put the blank in front so the PlaceMove will know
					move += '?';
					move += c;

					if (horizontal) CPUSHelper(pq, board, player, dictionary, col + 1, row, horizontal, word, move, unused);
					else CPUSHelper(pq, board, player, dictionary, col, row + 1, horizontal, word, move, unused);

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

				if (horizontal) CPUSHelper(pq, board, player, dictionary, col + 1, row, horizontal, word, move, unused);
				else CPUSHelper(pq, board, player, dictionary, col, row + 1, horizontal, word, move, unused);

				// backtrack, look for new solution
				unused.insert(i, 1, c);
				move.erase(move.length() - 1, 1);
				word.erase(word.length() - 1, 1);
			}

		}
	}
}

size_t getTotalScore(std::vector<std::pair<std::string, unsigned int>> vect) {
	size_t score = 0;
	std::vector<std::pair<std::string, unsigned int>>::iterator it;
	for (it = vect.begin(); it != vect.end(); ++it) {
		score += (*it).second;
	}
	return score;
}