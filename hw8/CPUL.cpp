#include <iostream>
#include <set>
#include <utility>
#include <string>
#include <algorithm>
#include <queue>
#include <functional>
#include <bits/stdc++.h>

// function that finds valid places to start from
std::set<std::pair<size_t, size_t>, char> findAllValidSquares(Board & board) {
	std::set<std::pair<size_t, size_t> > validSquares;
	size_t row = board->getRows();
	size_t col = board->getColumns();
	for (size_t i = 1; i <= col; i++) {
		for (size_t j = 1; j <= row; j++) {
			// there is a square here, look up/down, left/right to see if we can place there
			if (board->getSquare(i, j)->isOccupied()) {
				char curr = board->getSquare(i, j)->getLetter();
				if (i - 1 > 0) {
					if (!board->getSquare(i-1, j)->isOccupied()) set.insert(std::make_pair(i - 1, j), curr);
				}
				if (i + 1 < col) {
					if (!board->getSquare(i-1, j)->isOccupied()) set.insert(std::make_pair(i + 1, j), curr);
				}
				if (j - 1 > 0) {
					if (!board->getSquare(i-1, j)->isOccupied()) set.insert(std::make_pair(i, j - 1), curr);
				}
				if (j + 1 < row) {
					if (!board->getSquare(i-1, j)->isOccupied()) set.insert(std::make_pair(i, j + 1), curr);
				}
			}
		}
	}
	return validSquares;
}

CPULStrategy(Board & board) {
	// we have a hand, look at it and everywhere to start
	std::set<std::pair<size_t, size_t>, char> validSquares = findAllValidSquares(board);
	std::set<std::pair<size_t, size_t>, char>::iterator it;

	for (it = validSquares.begin(); it != validSquares.end(); ++it) {
		
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

