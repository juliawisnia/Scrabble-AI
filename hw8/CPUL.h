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

struct compare {
	bool operator()(std::pair<size_t, Move*> a, std::pair<size_t, Move*> b) {
		return (a.first > b.first);
	}
};

typedef std::priority_queue <std::pair<size_t, Move*>, std::vector<std::pair<size_t, Move*>>, compare> PlaceMoveQueue;

bool checkAllWords(Board & board, Dictionary & dictionary, Player & player, PlaceMove & move);

Move* CPULStrategy(Board & board, Dictionary & dictionary, Player & player);

// void helper(PlaceMoveQueue& results, size_t col, size_t row, Board & board, Dictionary & dictionary, std::string currWord, std::string unusedTiles, std::string moveString,
// 	 Player & player, bool horizontal);
void helper(PlaceMoveQueue & pq, Board & board, Player & player, Dictionary & dictionary, size_t col, size_t row, bool horizontal, 
	std::string word, std::string move, std::string unused);

bool allUsed(std::vector<std::pair<char, bool>> vect);

void resetToUnused(std::vector<std::pair<char, bool>>& vect);