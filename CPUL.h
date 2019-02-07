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
#include "Trie.h"
#include "Util.h"

// comparator sorting by length/tiles PLAYED for priority_queue
struct lengthCompare {
	bool operator()(std::pair<size_t, std::string> a, std::pair<size_t, std::string> b) {
		return (a.first < b.first);
	}
};

// priority queue used to store all VALID move strings
typedef std::priority_queue <std::pair<size_t,std::string>, std::vector<std::pair<size_t, std::string>>, lengthCompare> CPULQueue;

// a wrapper for CPULStrategy, runs helper and then chooses top element from priority queue to play
std::string CPULStrategy(Board & board, Dictionary & dictionary, Player & player);

// a helper that determines all valid moves and pushes them to the priority queue
void CPULHelper(CPULQueue & pq, Board & board, Player & player, Dictionary & dictionary, size_t col, size_t row, bool horizontal, 
	std::string word, std::string move, std::string unused);