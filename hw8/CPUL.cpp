#include <iostream>
#include <set>
#include <utility>
#include <string>
#include <algorithm>
#include <queue>
#include <vector>
#include <functional>
#include <bits/stdc++.h>

// function that finds valid places to start from, returns coordinates of an occupied square that something can be placed at
std::set<std::pair<size_t, size_t> > findAllValidSquares(Board & board) {
	std::set<std::pair<size_t, size_t> > validSquares;
	size_t row = board->getRows();
	size_t col = board->getColumns();
	for (size_t i = 1; i <= col; i++) {
		for (size_t j = 1; j <= row; j++) {
			// there is a square here, look up/down, left/right to see if we can place there
			// break when one of them returns true, cuts down on rutime maybe just a bit
			if (board->getSquare(i, j)->isOccupied()) {
				char curr = board->getSquare(i, j)->getLetter();
				if (i - 1 > 0) {
					if {
						(!board->getSquare(i-1, j)->isOccupied()) set.insert(std::make_pair(i, j));
						break;
					}
				}
				if (i + 1 < col) {
					if {
						(!board->getSquare(i-1, j)->isOccupied()) set.insert(std::make_pair(i, j));
						break;
					}
				}
				if (j - 1 > 0) {
					if {
						(!board->getSquare(i-1, j)->isOccupied()) set.insert(std::make_pair(i, j));
						break;
					}
				}
				if (j + 1 < row) {
					if {
						(!board->getSquare(i-1, j)->isOccupied()) set.insert(std::make_pair(i, j));
						break;
					}
				}
			}
		}
	}
	return validSquares;
}

CPULStrategy(Board & board, Dictionary & words, Player & player) {
	// we have a hand, look at it and everywhere to start
	std::set<std::pair<size_t, size_t> > validSquares = findAllValidSquares(board);
	std::set<std::pair<size_t, size_t> >::iterator it;

	// first we are going to try and place all words that play the max tiles in hand, then max - 1, etc
	// start by placing at square - n, then square - n + 1, until valid move
	// use prefix to get a TrieNode* to first letter in the trie, and then traverse yourself instead of calling it to save on runtime
	// once we have determined that there are no words made from there, we can quit and backtrack
	// if we find one that works, we make it a place move. If it throws no exceptions, we can quit
	// try and place all of them, then i - 1, until 1 tile


}

verticalHelper(std::set<std::pair<size_t, size_t> > validSquares, Board & board, Dictionary & words, Player & player) {
	// try to place word going up/down
	for (it = validSquares.begin(); it != validSquares.end(); ++it) {
		size_t currRow = (*it).second - player->getHandTiles().size();
		size_t col = (*it).first;
		std::vector<char> hand;
		std::vector<char> unused;
		std::set<Tile*>::iterator i;
		for (i = player->getHandTiles().begin(); i != player->getHandTiles().end(); ++i) {
			hand.push_back((*i)->getLetter());
			unused.push_back((*i)->getLetter());
		}

		std::string temp = "";
		// there's a square here, we need to add this to our move
		if (board->getSquare(col, currRow)->isOccupied()) {
			temp.push_back(board->getSquare(col, currRow)->getLetter());
			currRow++;
		}
		else {
			temp.push_back(unused.back());
			unused.pop_back();
		}
	}
}
	// for (size_t i = player->getHandTiles.size(); i > 0; i--) {
	// 	for (it = validSquares.begin(); it != validSquares.end(); ++it) {
	// 		std::string temp = "";
	// 		std::pair coor = (*it);
	// 		// first try to make a word above
	// 		size_t startRow = coor.second - i;
	// 		std::set<Tile*>::iterator tileIt;
	// 		for (tileIt = player->getHandTiles.begin(); tileIt != player->getHandTiles.end(); ++tileIt) {
	// 			temp += (*tileIt)->getLetter();
	// 			TrieNode* curr = prefix(temp);
	// 			if (curr == nullptr) continue;
	// 			else {

	// 			}
	// 		}
	// 	}
	// }

void search() {

}

// void DFS(Tile* start) {
// 	std::set<Tile*> isVisited;
// 	std::stack<std::string> stk;

// 	isVisited.insert(start);
// 	stk.push(start->getLetter());

// 	while (!stk.empty()) {
// 		std::string curr = stk.top();
// 		stk.pop();
// 		TrieNode* start = prefix(curr[curr.size() - 1]);

// 		std::set<std::pair<size_t, size_t> >::iterator it;
// 		for (it = hand.begin(); it != hand.end(); ++it) {
// 			if (isVisited.find((*it) == isVisited.end())) {
// 				int index = (*it)->getLetter() - 97;
// 				// not a word
// 				if (start->children[index] == nullptr) {
// 					continue;
// 				}
// 				else {
// 					curr += (*it)->getLetter;
// 					stk.push(curr);
// 					start = start->children[index];
// 					isVisited.insert((*it));
// 					DFS((*it));
// 					isVisited.erase(it);
// 				}
// 			}
// 		}

// 		if (hand.size() == isVisited.size()) {

// 		}
// 	}
// }

bool DFS(Node* start, Node* end) {

	std::set<Node*> isVisited;
	isVisited.insert(start);
	stack<Node*>stack;
	stack.push(start);
	while(!stack.empty())
	{
		Node*other=stack.top();
		stack.pop();
		if(other==end)
		{
			return true;
		}

		for(size_t i=0;i<other->neighbors.size();i++)
		{
			if(isVisited.find(other->neighbors[i])==isVisited.end())
			{
				isVisited.insert(other->neighbors[i]);
				stack.push(other->neighbors[i]);
			}
		}

	}
	return false;
}

// recursive backtracking function
strategyHelper(Board & board, Dictionary & words, Player & player, std::pair<size_t, size_t> coor) {
	// number of tiles in player's hand
	std::set<Tile*> hand = player->getHandTiles();
	size_t handSize = hand.size();

	std::set<Tile*>::iterator it;

	size_t cnt = -1;
	while (cnt < handSize + 1) {
		// cnt++;
		// size_t startUp = coor.second - handSize + cnt;

		// for (it = hand.begin(); it != hand.end(); ++it) {
		// 	std::string currWord = "";
		// 	TrieNode* start = prefix((*it)->getLetter());
		// 	// there is no word that starts with this letter... unlikely, but what we want is the pointer to the letter
		// 	if (start == nullptr) continue;
		// 	currWord += start->getLetter();

		// 	if (board->getTile(coor.first, startUp)->isOccupied) {
		// 		size_t index = board->getTile(coor.first, startUp)->getLetter() - 97;
		// 		if (start->children[index] != nullptr) {
		// 			startUp++;
		// 			currWord += board->getTile(coor.first, startUp)->getLetter();
		// 			start = start->children[index];
		// 		}
		// 		else {
		// 			break;
		// 		}
		// 	}
		// 	startUp++;

		// 	std::set<Tile*>::iterator restIt;
		// 	for (restIt = hand.begin(); restIt != hand.end(); ++restIt) {
		// 		// don't consider the same tile you have
		// 		if ((*it) == (*restIt)) continue;

		// 		size_t index = (*restIt)->getLetter() - 97;
		// 		if (start->children[index] != nullptr) {
		// 			startUp++;
		// 			currWord += (*restIt)->getLetter();
		// 			start = start->children[index];
		// 		}
		// 		else break;
		// 	}
		// }
	}
}

struct sortByLength {
	bool operator()(std::string a, std::string b) {
		return (a.size() < b.size());
	}
};

void permute(std::set<std::string>& hand, std::string input, size_t n) {
	if (n == 0) return;
	do {
		hand.emplace(input.substr(0, input.size()));
	} while (std::next_permutation(input.begin(), input.begin() + input.size()));

	for (size_t i = 0; i < n; i++) {
		std::string temp = "";
		for (size_t j = 0; j < input.size(); j++) {
			if (i == j) continue;
			temp += input[j];
		}
		permute(hand, temp, n - 1);
	}
}

