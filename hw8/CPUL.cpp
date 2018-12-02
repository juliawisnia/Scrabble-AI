
#include "CPUL.h"

// FROM THE BUY CODE SOLUTION
bool checkAllWords(Board & board, Dictionary & dictionary, Player & player, PlaceMove & move) {
	std::cout << "do u hear me bish" << std::endl;
	// first, try this move on the board and see what words are generated
	std::vector<std::pair<std::string, unsigned int>> sequencesFormed = board.getPlaceMoveResults(move);
	std::cout << "do u hear me bish" << std::endl;

	// check that each sequence of tiles in in fact a word
	for(size_t sequenceIndex = 0; sequenceIndex < sequencesFormed.size(); ++sequenceIndex)
	{
		if(!dictionary.isLegalWord(sequencesFormed[sequenceIndex].first))
		{
		// 	throw MoveException("INVALIDWORD:" + sequencesFormed[sequenceIndex].first);
			std::cout << "do u hear me bish" << std::endl;
			player.addTiles(move._tiles);
			return false;
		}
	}

	return true;
}

Move* CPULStrategy(Board & board, Dictionary & dictionary, Player & player) {
	std::vector<char> unused;
	std::set<Tile*>::iterator it;
	for (it = player.getHandTiles().begin(); it != player.getHandTiles().end(); ++it) {
		std::cout << " " << (*it)->getLetter();
		unused.push_back((*it)->getLetter());
	}
	std::cout << std::endl;

	std::priority_queue <std::pair<size_t, Move*>, std::vector<std::pair<size_t, Move*>>, compare> verticalResults;
	std::priority_queue <std::pair<size_t, Move*>, std::vector<std::pair<size_t, Move*>>, compare> horizontalResults;

	for (size_t i = 1; i <= (size_t)board.getColumns(); i++) {
		for (size_t j = 1; j <= (size_t)board.getRows(); j++) {
			helper(verticalResults, i, j, board, dictionary, "", "", unused, player, false);
			helper(horizontalResults, i, j, board, dictionary, "", "", unused, player, true);
		}
	}
	// std::cout << "VERTICAL MOVE: " << verticalResults.top().first << std::endl;
	// std::cout << "HORIZONTAL MOVE: " << horizontalResults.top().first << std::endl;

	if (verticalResults.empty() && horizontalResults.empty()) {
		PassMove* pass = new PassMove(&player);
		return pass;
	}
	// the vertical move is the best
	if (verticalResults.top().first > horizontalResults.top().first) {
		return verticalResults.top().second;
	}
	else return horizontalResults.top().second;


	// first we are going to try and place all words that play the max tiles in hand, then max - 1, etc
	// start by placing at square - n, then square - n + 1, until valid move
	// use prefix to get a TrieNode* to first letter in the trie, and then traverse yourself instead of calling it to save on runtime
	// once we have determined that there are no words made from there, we can quit and backtrack
	// if we find one that works, we make it a place move. If it throws no exceptions, we can quit
	// try and place all of them, then i - 1, until 1 tile
}

void helper(std::priority_queue <std::pair<size_t, Move*>, std::vector<std::pair<size_t, Move*>>, compare>& results, 
	size_t col, size_t row, Board & board, Dictionary & dictionary, std::string currWord, std::string tiles, std::vector<char> unusedTiles,
	 Player & player, bool horizontal) {
	// std::cout << "CURRWORD: " << currWord << std::endl;
	if (unusedTiles.empty() || col > board.getColumns() || row > board.getRows() || col < 1 || row < 1) return;

	char currLetter = '$';
	// there's a tile on this square that we need to account for in our word
	if (board.getSquare(col, row)->isOccupied()) {
		currLetter = board.getSquare(col, row)->getLetter();
	}
	else {
		currLetter = unusedTiles.back();
		// unusedTiles.pop_back();
		// tiles += currLetter;
	}

	std::string temp = currWord + currLetter;
	PlaceMove* tempMove = nullptr;
	try {
		PlaceMove* tempMove = new PlaceMove(col, row, horizontal, tiles, &player);
		board.getPlaceMoveResults(*tempMove);
	}
	catch (MoveException & m) {
		// should only be throwing NONEIGHBORS
		std::cout << m.what() << std::endl;
		// the move execution failed, but the tiles in _tiles have still been removed from
		// the player's hand.  So, we need to put them back.
		// note to self: add unit tests for this mistake

		player.addTiles(tempMove->tileVector());

		// now, you can get on with your exception
		//throw moveException;

		if (horizontal) helper(results, col, row + 1, board, dictionary, "", "", unusedTiles, player, horizontal);
		else helper(results, col + 1, row, board, dictionary, "", "", unusedTiles, player, horizontal);
	}

	// no out of bounds errors, but we have to check if the words are valid
	TrieNode* check = dictionary.words.prefix(temp);

	// not a valid prefix, so we need to backtrack and move onto the next letter
	if (check == nullptr) {
		std::cout << "FOUND ONE" << std::endl;
		//std::string temp;
		// take out the last letter that we added
		// for (size_t i = 0; i < (size_t)tiles.size() - 1; i++) temp += tiles[i];
		//unusedTiles.insert(unusedTiles.begin(), temp[temp.size() - 1]);
		if (horizontal) helper(results, col, row, board, dictionary, currWord, currWord, unusedTiles, player, horizontal);
		else helper(results, col, row, board, dictionary, currWord, currWord, unusedTiles, player, horizontal);
	}

	// valid prefix, check it it's a valid word
	if (check != nullptr && check->inSet) {
		std::cout << "FOUND ONEa" << std::endl;
		// this word was good to use
		currWord = temp;
		// check that all words were valid, if so add to set, otherwise backtrack
		if (checkAllWords(board, dictionary, player, *tempMove)) {
			unusedTiles.pop_back();
			std::cout << "FOUND ONEb" << std::endl;
			// add to list
			size_t size = tiles.size();
			results.emplace(std::make_pair(size, tempMove));
			// backtrack to see if I can make a longer word
			if (horizontal) helper(results, col + 1, row, board, dictionary, currWord, tiles, unusedTiles, player, horizontal);
			else helper(results, col, row + 1, board, dictionary, currWord, tiles, unusedTiles, player, horizontal);
		}
	}

	if (check != nullptr && !check->inSet) {
		unusedTiles.pop_back();
		std::cout << "FOUND ONEd" << std::endl;
		// this prefix was good to use
		currWord = temp;
		if (horizontal) helper(results, col + 1, row, board, dictionary, currWord, tiles, unusedTiles, player, horizontal);
		else helper(results, col, row + 1, board, dictionary, currWord, tiles, unusedTiles, player, horizontal);
	}
}