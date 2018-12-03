#include "CPUS.h"

Move* CPUSStrategy(Board & board, Dictionary & dictionary, Player & player) {
	CPUSQueue vertical;
	CPUSQueue horizontal;

	std::string unused;
	std::set<Tile*>::iterator it;
	// say that every tile hasn't been used at first
	for (it = player.getHandTiles().begin(); it != player.getHandTiles().end(); ++it) {
		unused += (*it)->getLetter();
	}

	for (size_t i = 1; i <= board.getColumns(); i++) {
		for (size_t j = 1; j <= board.getRows(); j++) {
			CPUSHelper(vertical, board, player, dictionary, i, j, false, "", "", unused);
			CPUSHelper(horizontal, board, player, dictionary, i, j, true, "", "", unused);
		}
	}

	if (vertical.empty() && horizontal.empty()) {
		PassMove* pass = new PassMove(&player);
		return pass;
	}

	if (vertical.empty() && !horizontal.empty()) return horizontal.top().second;
	if (!vertical.empty() && horizontal.empty()) return vertical.top().second;

	if (vertical.top().first > horizontal.top().first) return vertical.top().second;
	return horizontal.top().second;

}

void CPUSHelper(CPUSQueue & pq, Board & board, Player & player, Dictionary & dictionary, size_t col, size_t row, bool horizontal, 
	std::string word, std::string move, std::string unused) {
	//std::cout << "WORD: " << word << std::endl;

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
			std::vector<std::pair<std::string, unsigned int>> score;
			PlaceMove* tempMove = nullptr;
			try {
				if (horizontal) tempMove = new PlaceMove(col - word.size(), row, horizontal, move, &player);
				else tempMove = new PlaceMove(col, row - word.size(), horizontal, move, &player);
			}
			catch (MoveException & m) {
				std::cout << m.what() << std::endl;
				if (tempMove != nullptr) player.addTiles(tempMove->tileVector());
				delete tempMove;
				return;
			}

			try {
				if (tempMove != nullptr) score = board.getPlaceMoveResults(*tempMove);
			}
			catch (MoveException & m) {
				std::cout << m.what() << std::endl;
				if (tempMove != nullptr) player.addTiles(tempMove->tileVector());
				delete tempMove;
				return;
			}

			// no exceptions thrown, it's a word
			pq.emplace(std::make_pair(move.size(), tempMove));
			//delete tempMove;
			// resetToUnused(unused);
			// if (horizontal) CPUSHelper(pq, board, player, col + 1, row, horizontal, "", "", unused);
			// else CPUSHelper(pq, board, player, col, row + 1, horizontal, "", "", unused);
		}
	}
	if (unused.empty()) return;
	for (size_t i = 0; i < unused.size(); i++) {
		// this letter is already in use
		char c = unused[i];

		if (c == '?') {
			
		}

		word += c;
		unused.erase(i, 1);
		// only add it to the move if it's a letter from our hand
		if (!board.getSquare(col, row)->isOccupied()) move += c;

		if (horizontal) CPUSHelper(pq, board, player, dictionary, col + 1, row, horizontal, word, move, unused);
		else CPUSHelper(pq, board, player, dictionary, col, row + 1, horizontal, word, move, unused);

		// backtrack, look for new solution
		unused.insert(i, 1, c);
		if (!board.getSquare(col, row)->isOccupied()) move.erase(move.length() - 1, 1);
		word.erase(word.length() - 1, 1);

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