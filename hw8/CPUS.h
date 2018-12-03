#include <iostream>
#include <set>
#include <queue>
#include <utility>
#include <string>
#include <algorithm>
#include <vector>
#include <functional>
#include <bits/stdc++.h>

#include "Board.h"
#include "Bag.h"
#include "Dictionary.h"
#include "ConsolePrinter.h"
#include "Player.h"
#include "ConfigFile.h"
#include "Exceptions.h"
#include "rang.h"
#include "Util.h"
#include "Trie.h"

// comparator sorting by score for priority_queue
struct scoreCompare {
	bool operator()(std::pair<size_t, std::string> a, std::pair<size_t, std::string> b) {
		return (a.first < b.first);
	}
};

// priority queue used to store all VALID move strings
typedef std::priority_queue <std::pair<size_t, std::string>, std::vector<std::pair<size_t, std::string>>, scoreCompare> CPUSQueue;

// a wrapper for CPUSHelper, runs helper and then chooses top element from priority queue to play
std::string CPUSStrategy(Board & board, Dictionary & dictionary, Player & player);

// a helper that determines all valid moves and pushes them to the priority queue
void CPUSHelper(CPUSQueue & pq, Board & board, Player & player, Dictionary & dictionary, size_t col, size_t row, bool horizontal, 
	std::string word, std::string move, std::string unused);

// gets score from the results vector returned by getPlaceMoveResults from board
size_t getTotalScore(std::vector<std::pair<std::string, unsigned int>> vect);