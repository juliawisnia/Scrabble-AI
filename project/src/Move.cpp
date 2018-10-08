#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "Move.h"

Move * Move::parseMove(std::string moveString, Player &p) {
	std::stringstream ss(moveString);
	std::string moveType;

	ss >> moveType;

	if (moveType == "PASS") {
		PassMove &pass(*p);
		return pass;
	}

	else if (moveType == "EXCHANGE") {
		std::string tileString;
		ss >> tileString;

		ExchangeMove &exchange(tileString, *p);
		return exchange;

	}

	// place move
	else {
		char dir;
		bool horizontal;
		size_t row, column;
		std::string word;

		ss >> dir >> row >> column >> word;

		if (dir == '-') horizontal = true;
		else horizontal = false;

		PlaceMove place(row, column, horizontal, word, p);
		return place;
	}
}