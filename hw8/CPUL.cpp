
#include "CPUL.h"

// FROM THE BUY CODE SOLUTION
bool checkAllWords(Board & board, Dictionary & dictionary, Player & player, PlaceMove & move) {
	// first, try this move on the board and see what words are generated
	std::vector<std::pair<std::string, unsigned int>> sequencesFormed = board.getPlaceMoveResults(move);

	// check that each sequence of tiles in in fact a word
	for(size_t sequenceIndex = 0; sequenceIndex < sequencesFormed.size(); ++sequenceIndex)
	{
		if(!dictionary.isLegalWord(sequencesFormed[sequenceIndex].first))
		{
		// 	throw MoveException("INVALIDWORD:" + sequencesFormed[sequenceIndex].first);
			player->addTiles(move._tiles);
			return false;
		}
	}

	return true;
}

Move* CPULStrategy(Board & board, Dictionary & dictionary, Player & player) {
	//std::vector<char> hand;
	std::vector<char> unused;
	std::set<Tile*>::iterator it;
	for (it = player.getHandTiles().begin(); it != player.getHandTiles().end(); ++it) {
		unused.push_back((*it)->getLetter());
	}

	std::priority_queue <std::pair<size_t, Move*>, std::vector<std::pair<size_t, Move*>>, std::greater> verticalResults;
	std::priority_queue <std::pair<size_t, Move*>, std::vector<std::pair<size_t, Move*>>, std::greater> horizontalResults;

	for (size_t i = 0; i < board.getColumns(); i++) {
		for (size_t j = 0; j < board.getRows(); j++) {
			verticalHelper(verticalResults, i, j, board, dictionary, "", unused, player);
			horizontalHelper(horizontalResults, i, j, board, dictionary, "", unused, player);
		}
	}

	if (verticalResults.empty() && horizontalResults.empty()) {
		PassMove pass = new PassMove(*player);
		return &pass;
	}
	// the vertical move is the best
	if (verticalResults.top() > horizontalResults.top()) {
		return &verticalResults.top().second;
	}
	else return &horizontalResults.top().second;


	// first we are going to try and place all words that play the max tiles in hand, then max - 1, etc
	// start by placing at square - n, then square - n + 1, until valid move
	// use prefix to get a TrieNode* to first letter in the trie, and then traverse yourself instead of calling it to save on runtime
	// once we have determined that there are no words made from there, we can quit and backtrack
	// if we find one that works, we make it a place move. If it throws no exceptions, we can quit
	// try and place all of them, then i - 1, until 1 tile
}

void verticalHelper(std::priority_queue <std::pair<size_t, Move*>, std::vector<std::pair<size_t, Move*>>, std::greater>& results, 
	size_t col, size_t row, Board & board, Dictionary & dictionary, std::string currWord, std::vector<char> unusedTiles, Player & player) {

	if (unusedTiles.empty()) return;

	char currLetter = '$';
	// there's a tile on this square that we need to account for in our word
	if (board.getSquare(col, row)->isOccupied()) {
		currLetter = board.getSquare(col, row)->getLetter();
	}
	else {
		currLetter = unusedTiles.back();
		unusedTiles.pop_back();
	}

	std::string temp = currWord + currLetter;

	try {
		PlaceMove tempMove = new PlaceMove(col, row, false, temp, tilePlayed, player);
	}
	catch {
		// backtrack in this case, beacuse we have gone out of bounds
		verticalHelper(col, row - 1, board, dictionary, currWord, unusedTiles, player);
	}

	// no out of bounds errors, but we have to check if the words are valid
	TrieNode* check = prefix(temp);

	// not a valid prefix, so we need to backtrack and move onto the next letter
	if (check == nullptr) {
		verticalHelper(col, row, board, dictionary, currWord, tilePlayed, unusedTiles, player);
	}

	// valid prefix, check it it's a valid word
	if (check != nullptr && check->inSet) {
		// this word was good to use
		currWord = temp;
		// check that all words were valid, if so add to set, otherwise backtrack
		if (checkAllWords(board, dictionary, player, tempMove)) {
			// add to list
			results.emplace(std::make_pair(tempMove->_tiles.size(), &tempMove));
			// backtrack to see if I can make a longer word
			verticalHelper(col, row + 1, board, dictionary, currWord, unusedTiles, player)
		}
	}

	if (check != nullptr && !check->inSet) {
		// this prefix was good to use
		currWord = temp;
		verticalHelper(col, row + 1, board, dictionary, currWord, unusedTiles, player);
	}
}

void horizontalHelper(std::priority_queue <std::pair<size_t, Move*>, std::vector<std::pair<size_t, Move*>>, std::greater>& results, 
	size_t col, size_t row, Board & board, Dictionary & dictionary, std::string currWord, std::vector<char> unusedTiles, Player & player) {

	if (unusedTiles.empty()) return;

	char currLetter = '$';
	// there's a tile on this square that we need to account for in our word
	if (board->getSquare(col, row)->isOccupied()) {
		onBoard = true;
		currLetter = board->getSquare(col, row)->getLetter();
	}
	else {
		currLetter = unusedTiles.pop_back();
	}

	std::string temp = currWord + currLetter

	try {
		PlaceMove tempMove = new PlaceMove(col, row, true, temp, tilePlayed, player);
	}
	catch {
		// backtrack in this case, beacuse we have gone out of bounds
		horizontalHelper(col - 1, row, board, dictionary, currWord, unusedTiles, player);
	}

	// no out of bounds errors, but we have to check if the words are valid
	TrieNode* check = prefix(temp);

	// not a valid prefix, so we need to backtrack and move onto the next letter
	if (check == nullptr) {
		horizontalHelper(results, col, row, board, dictionary, currWord, tilePlayed, unusedTiles, player);
	}

	// valid prefix, check it it's a valid word
	if (check != nullptr && check->inSet) {
		// this word was good to use
		currWord = temp;
		// check that all words were valid, if so add to set, otherwise backtrack
		if (tempMove.checkAllWords(board, dictionary, player, tempMove)) {
			// add to list
			results.emplace(std::make_pair(tempMove->_tiles.size(), &tempMove));
			// backtrack to see if I can make a longer word
			horizontalHelper(results, col + 1, row, board, dictionary, currWord, unusedTiles, player)
		}
	}

	if (check != nullptr && !check->inSet) {
		// this prefix was good to use
		currWord = temp;
		verticalHelper(col + 1, row, board, dictionary, currWord, unusedTiles, player);
	}
}