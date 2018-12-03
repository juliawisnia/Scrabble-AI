#include "CPUL.h"

Move* CPULStrategy(Board & board, Dictionary & dictionary, Player & player) {
	PlaceMoveQueue vertical;
	PlaceMoveQueue horizontal;

	std::string unused;
	std::set<Tile*>::iterator it;
	// say that every tile hasn't been used at first
	for (it = player.getHandTiles().begin(); it != player.getHandTiles().end(); ++it) {
		unused += (*it)->getLetter();
	}

	for (size_t i = 1; i <= board.getColumns(); i++) {
		for (size_t j = 1; j <= board.getRows(); j++) {
			helper(vertical, board, player, dictionary, i, j, false, "", "", unused);
			helper(horizontal, board, player, dictionary, i, j, true, "", "", unused);
		}
	}

	if (vertical.empty() && horizontal.empty()) {
		PassMove* pass = new PassMove(&player);
		return pass;
	}

	if (vertical.top().first > horizontal.top().first) return vertical.top().second;
	return horizontal.top().second;

}

// bool allUsed(std::vector<std::pair<char, bool>> vect) {
// 	std::vector<std::pair<char, bool>>::iterator it;
// 	for (it = vect.begin(); it != vect.end(); ++it) {
// 		// if there's one that hasn't been used, then not "empty"
// 		if ((*it).second == false) return false;
// 	}
// 	return true;
// }

// void resetToUnused(std::vector<std::pair<char, bool>>& vect) {
// 	std::vector<std::pair<char, bool>>::iterator it;
// 	for (it = vect.begin(); it != vect.end(); ++it) {
// 		// reset all bool values
// 		(*it).second = false;
// 	}	
// 	return;
// }

void helper(PlaceMoveQueue & pq, Board & board, Player & player, Dictionary & dictionary, size_t col, size_t row, bool horizontal, 
	std::string word, std::string move, std::string unused) {
	//std::cout << "WORD: " << word << std::endl;

	if (row > board.getRows() || col > board.getColumns()) return;

	TrieNode* check = dictionary.words.prefix(word);
	// not even a prefix, and string is not empty
	if (check == nullptr) {
		if (word.size() > 0) return;
	}

	// it's a prefix
	else {
		// it's a word
		if (check->inSet) {
			PlaceMove* tempMove = nullptr;
			try {
				if (horizontal) tempMove = new PlaceMove(col - word.size(), row, horizontal, move, &player);
				else tempMove = new PlaceMove(col, row - word.size(), horizontal, move, &player);
			}
			catch (MoveException & m) {
				std::cout << m.what() << std::endl;
				player.addTiles(tempMove->tileVector());
				//delete tempMove;
			}

			try {
				board.getPlaceMoveResults(*tempMove);
			}
			catch (MoveException & m) {
				std::cout << m.what() << std::endl;
				player.addTiles(tempMove->tileVector());
				//delete tempMove;
			}

			// no exceptions thrown, it's a word
			pq.emplace(std::make_pair(move.size(), tempMove));
			//delete tempMove;
			// resetToUnused(unused);
			// if (horizontal) helper(pq, board, player, col + 1, row, horizontal, "", "", unused);
			// else helper(pq, board, player, col, row + 1, horizontal, "", "", unused);
		}
	}
	if (unused.empty()) return;
	for (size_t i = 0; i < unused.size(); i++) {
		// this letter is already in use
		char c = unused[i];

		word += c;
		unused.erase(i, 1);
		// only add it to the move if it's a letter from our hand
		if (!board.getSquare(col, row)->isOccupied()) move += c;

		if (horizontal) helper(pq, board, player, dictionary, col + 1, row, horizontal, word, move, unused);
		else helper(pq, board, player, dictionary, col, row + 1, horizontal, word, move, unused);

		// backtrack, look for new solution
		unused.insert(i, 1, c);
		if (!board.getSquare(col, row)->isOccupied()) move.erase(move.length() - 1, 1);
		word.erase(word.length() - 1, 1);

	}
}

// void helper(std::string word, std::string unused) {
// 	TrieNode* check = dictionary.words.prefix(word);
// 	// not even a prefix, and string is not empty
// 	if (check == nullptr) {
// 		if (word.size() > 0) return;
// 	}

// 	// it's a prefix and a word
// 	if (check != nullptr && check->inSet) {
// 		PlaceMove* tempMove = nullptr;
// 		try {
// 			if (horizontal) tempMove = new PlaceMove(col - word.size(), row, horizontal, move, &player);
// 			else tempMove = new PlaceMove(col, row - word.size(), horizontal, move, &player);
// 		}
// 		catch (MoveException & m) {
// 			std::cout << m.what() << std::endl;
// 			player.addTiles(tempMove->tileVector());
// 			delete tempMove;
// 		}

// 		try {
// 			board.getPlaceMoveResults(*tempMove);
// 		}
// 		catch (MoveException & m) {
// 			std::cout << m.what();
// 			player.addTiles(tempMove->tileVector());
// 			delete tempMove;
// 		}

// 		// no exceptions thrown, it's a word
// 		pq.emplace(std::make_pair(move.size(), tempMove));
// 		delete tempMove;
// 		// resetToUnused(unused);
// 		// if (horizontal) helper(pq, board, player, col + 1, row, horizontal, "", "", unused);
// 		// else helper(pq, board, player, col, row + 1, horizontal, "", "", unused);
// 	}

// 	else {
// 		for (size_t i = 0; i < word.length(); i++) {
// 			char c = word[i];
// 			unused += c;
// 			word.erase(i, 1)

// 			helper(word, unused);

// 			word.insert(i, 1, c);
// 			unused.erase(chosen, length() - 1, 1);
// 		}
// 	}
// }


// #include "CPUL.h"

// // FROM THE BUY CODE SOLUTION
// bool checkAllWords(Board & board, Dictionary & dictionary, Player & player, PlaceMove & move) {
// 	std::cout << "do u hear me bish" << std::endl;
// 	// first, try this move on the board and see what words are generated
// 	std::vector<std::pair<std::string, unsigned int>> sequencesFormed = board.getPlaceMoveResults(move);
// 	std::cout << "do u hear me bish" << std::endl;

// 	// check that each sequence of tiles in in fact a word
// 	for(size_t sequenceIndex = 0; sequenceIndex < sequencesFormed.size(); ++sequenceIndex)
// 	{
// 		if(!dictionary.isLegalWord(sequencesFormed[sequenceIndex].first))
// 		{
// 		// 	throw MoveException("INVALIDWORD:" + sequencesFormed[sequenceIndex].first);
// 			std::cout << "do u hear me bish" << std::endl;
// 			player.addTiles(move._tiles);
// 			return false;
// 		}
// 	}

// 	return true;
// }

// Move* CPULStrategy(Board & board, Dictionary & dictionary, Player & player) {
// 	//std::vector<char> unused;
// 	std::string unusedTiles = "";
// 	std::set<Tile*>::iterator it;
// 	for (it = player.getHandTiles().begin(); it != player.getHandTiles().end(); ++it) {
// 		unusedTiles += (*it)->getLetter();
// 	}
// 	//std::cout << std::endl;

// 	std::priority_queue <std::pair<size_t, Move*>, std::vector<std::pair<size_t, Move*>>, compare> verticalResults;
// 	std::priority_queue <std::pair<size_t, Move*>, std::vector<std::pair<size_t, Move*>>, compare> horizontalResults;

// 	for (size_t i = 1; i <= (size_t)board.getColumns(); i++) {
// 		for (size_t j = 1; j <= (size_t)board.getRows(); j++) {
// 			helper(verticalResults, i, j, board, dictionary, "", unusedTiles, "", player, false);
// 			helper(horizontalResults, i, j, board, dictionary, "", unusedTiles, "", player, true);
// 		}
// 	}
// 	std::cout << "VERTICAL MOVE: " << verticalResults.top().first << std::endl;
// 	std::cout << "HORIZONTAL MOVE: " << horizontalResults.top().first << std::endl;

// 	if (verticalResults.empty() && horizontalResults.empty()) {
// 		PassMove* pass = new PassMove(&player);
// 		return pass;
// 	}
// 	// the vertical move is the best
// 	if (verticalResults.top().first > horizontalResults.top().first) {
// 		return verticalResults.top().second;
// 	}
// 	else return horizontalResults.top().second;
// }

// void helper(std::priority_queue <std::pair<size_t, Move*>, std::vector<std::pair<size_t, Move*>>, compare>& results, 
// 	size_t col, size_t row, Board & board, Dictionary & dictionary, std::string currWord, std::string unusedTiles, std::string moveString,
// 	 Player & player, bool horizontal) {
// 	// std::cout << "CURRWORD: " << currWord << std::endl;
// 	if (col > board.getColumns() || row > board.getRows() || col < 1 || row < 1) return;

// 	std::vector<std::pair<std::string, unsigned int>> tempResult;
// 	char currLetter = '$';
// 	// there's a tile on this square that we need to account for in our word, and now we can check PlaceMove
// 	// if (board.getSquare(col, row)->isOccupied()) {
// 	// 	currLetter = board.getSquare(col, row)->getLetter();
// 	// 	std::string temp = currWord + currLetter;

// 	// 	TrieNode* check = dictionary.words.prefix(temp);
// 	// 	// not a valid prefix, we need to backtrack and change the previous letter because we can't change what's on the board
// 	// 	if (check == nullptr) {
// 	// 		if (horizontal) helper(results, col - 1, row, board, dictionary, currWord, unusedTiles, moveString, player, horizontal);
// 	// 		else helper(results, col, row - 1, board, dictionary, currWord, unusedTiles, moveString, player, horizontal);
// 	// 	}

// 	// 	// valid prefix, but not valid word so we can go on to the next iteration
// 	// 	if (check != nullptr && !check->inSet) {			
// 	// 		// advance to the next row or column
// 	// 		if (horizontal) helper(results, col + 1, row, board, dictionary, temp, unusedTiles, moveString, player, horizontal);
// 	// 		else helper(results, col, row + 1, board, dictionary, temp, unusedTiles, moveString, player, horizontal);
// 	// 	}

// 	// 	// valid prefix and valid word
// 	// 	if (check != nullptr && check->inSet) {
// 	// 		// create a PlaceMove to check if valid
// 	// 		PlaceMove* tempMove = nullptr;
// 	// 		if (horizontal) tempMove = new PlaceMove(col - currWord.size() + 1, row, horizontal, moveString, &player);
// 	// 		else tempMove = new PlaceMove(col, row - currWord.size() + 1, horizontal, moveString, &player);

// 	// 		try {
// 	// 			tempResult = board.getPlaceMoveResults(*tempMove);
// 	// 		}
// 	// 		// can catch OUTOFBOUNDS, which we shouldn't acheive, OCCUPIED, which shouldn't acheive, 
// 	// 		// NONEIGHBOR, which we shouldn't achieve, or NOSTART, which we can also achieve
// 	// 		// we need to put tiles back if it doesn't work
// 	// 		catch (MoveException & m) {
// 	// 			std::cout << m.what() << std::endl;
// 	// 			// add tiles back to the hand
// 	// 			
// 	// 			delete tempMove;
// 	// 			// reset unused tiles, we are completely starting over
// 	// 			unusedTiles = "";
// 	// 			std::set<Tile*>::iterator it;
// 	// 			for (it = player.getHandTiles().begin(); it != player.getHandTiles().end(); ++it) {
// 	// 				unusedTiles += (*it)->getLetter();
// 	// 			}
// 	// 			// go to next round to iterate
// 	// 			if (horizontal) helper(results, col + 1, row, board, dictionary, "", unusedTiles, "", player, horizontal);
// 	// 			else helper(results, col, row + 1, board, dictionary, "", unusedTiles, "", player, horizontal);				
// 	// 		}

// 	// 		// congratulations, we have found a real word! now, are all of them real?
// 	// 		std::vector<std::pair<std::string, unsigned int>>::iterator it;
// 	// 		for (it = tempResult.begin(); it != tempResult.end(); ++it) {
// 	// 			// we have found an invalid word, backtrack
// 	// 			if (!dictionary.isLegalWord((*it).first)) {
// 	// 				if (horizontal) {
// 	// 					helper(results, col - 1, row, board, dictionary, currWord, unusedTiles, moveString, player, horizontal);
// 	// 					break;
// 	// 				}
// 	// 				else {
// 	// 					helper(results, col, row - 1, board, dictionary, currWord, unusedTiles, moveString, player, horizontal);
// 	// 					break;
// 	// 				}
// 	// 			}
// 	// 		}

// 	// 		// we got through all the iterations, way to go. We can add this move to our priority queue now
// 	// 		results.emplace(std::make_pair(moveString.size(), tempMove));

// 	// 		// try to find a longer word
// 	// 		if (horizontal) helper(results, col + 1, row, board, dictionary, currWord, unusedTiles, moveString, player, horizontal);
// 	// 		else helper(results, col, row + 1, board, dictionary, currWord, unusedTiles, moveString, player, horizontal);			
// 	// 	}
// 	// }

// 	// else {
// 		// cycle through our remaining letters to see what is going to work
// 		std::string temp = "";
// 		std::string tempMoveString = "";
// 		for (size_t i = 0; i < unusedTiles.size(); i++) {
// 			currLetter = unusedTiles[i];
// 			temp = currWord + currLetter;
// 			tempMoveString = moveString + currLetter;

// 			TrieNode* check = dictionary.words.prefix(temp);
// 			// not a valid prefix, try the next letter
// 			if (check == nullptr) {
// 				continue;
// 			}
// 			// valid prefix, not a word
// 			if (check != nullptr && !check->inSet) {
// 				// if you end up using the tile, erase if from unused
// 				unusedTiles.erase(i, 1);
// 				// advance to the next row or column
// 				if (horizontal) helper(results, col + 1, row, board, dictionary, temp, unusedTiles, tempMoveString, player, horizontal);
// 				else helper(results, col, row + 1, board, dictionary, temp, unusedTiles, tempMoveString, player, horizontal);
// 			}
// 			// it's a valid prefix and word
// 			if (check != nullptr && check->inSet) {
// 				// create a PlaceMove to check if valid
// 				PlaceMove* tempMove = nullptr;
// 				if (horizontal) tempMove = new PlaceMove(col - currWord.size() + 1, row, horizontal, tempMoveString, &player);
// 				else tempMove = new PlaceMove(col, row - currWord.size() + 1, horizontal, tempMoveString, &player);

// 				try {
// 					tempResult = board.getPlaceMoveResults(*tempMove);
// 				}
// 				// can catch OUTOFBOUNDS, which we shouldn't acheive, OCCUPIED, which shouldn't acheive, 
// 				// NONEIGHBOR, which we shouldn't achieve, or NOSTART, which we can also achieve
// 				// we need to put tiles back if it doesn't work
// 				catch (MoveException & m) {
// 					std::cout << m.what() << std::endl;
// 					std::cout << "LOOK HERE: " << tempMoveString << std::endl;
// 					// add tiles back to the hand
// 					player.addTiles(tempMove->tileVector());
// 					delete tempMove;
// 					// reset unused tiles, we are completely starting over
// 					// unusedTiles = "";
// 					// std::set<Tile*>::iterator it;
// 					// for (it = player.getHandTiles().begin(); it != player.getHandTiles().end(); ++it) {
// 					// 	unusedTiles += (*it)->getLetter();
// 					// }
// 					// // go to next round to iterate
// 					// if (horizontal) helper(results, col + 1, row, board, dictionary, "", unusedTiles, "", player, horizontal);
// 					// else helper(results, col, row + 1, board, dictionary, "", unusedTiles, "", player, horizontal);			
// 				}

// 				// congratulations, we have found a real word! now, are all of them real?
// 				std::vector<std::pair<std::string, unsigned int>>::iterator it;
// 				bool allLegalWords = true;
// 				for (it = tempResult.begin(); it != tempResult.end(); ++it) {
// 					// we have found an invalid word, backtrack
// 					if (!dictionary.isLegalWord((*it).first)) {
// 						allLegalWords = false;
// 						// if (horizontal) {
// 						// 	// we didn't use this tile afterall
// 						// 	unusedTiles += tempMoveString[tempMoveString.size() - 1];
// 						// 	helper(results, col - 1, row, board, dictionary, currWord, unusedTiles, moveString, player, horizontal);
// 						// 	break;
// 						// }
// 						// else {
// 						// 	unusedTiles.push_back(tempMoveString[tempMoveString.size() - 1]);
// 						// 	helper(results, col, row - 1, board, dictionary, currWord, unusedTiles, moveString, player, horizontal);
// 						// 	break;
// 						// }
// 					}
// 				}

// 				// we got through all the iterations, way to go. We can add this move to our priority queue now
// 				if (allLegalWords) results.emplace(std::make_pair(tempMoveString.size(), tempMove));
// 				// if you end up using the tile, erase if from unused
// 				unusedTiles.erase(i, 1);			
// 			}
// 		}
// 		// see if there's a longer word we can make now
// 		if (horizontal) helper(results, col + 1, row, board, dictionary, currWord, unusedTiles, tempMoveString, player, horizontal);
// 		else helper(results, col, row + 1, board, dictionary, currWord, unusedTiles, tempMoveString, player, horizontal);
// 	// }
// }