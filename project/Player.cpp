#include <string>
#include <set>
#include <vector>
#include <sstream>
#include <iostream>
#include "Tile.h"
#include "Player.h"
#include "Move.h"
#include "Bag.h"

Player::Player (std::string const & playerName, size_t maxTiles, Bag & bag) {
	name = playerName;
	score = 0;
	maxHand = maxTiles;

	std::vector<Tile*> newTiles = bag.drawTiles(maxTiles);
	std::vector<Tile*>::iterator it;

	for (it = newTiles.begin(); it != newTiles.end(); ++it) {
		Hand.insert(*it);
	}
}

Player::~Player() {
	std::set<Tile*>::iterator it;
	//for (it = Hand.begin(); it != Hand.end(); ++it) delete (*it);
}

std::set<Tile*> Player::getHandTiles() const {
	return Hand;
}

size_t Player::getMaxTiles() const {
	return maxHand;
}

// NOTE: move expected to be only string of letters
bool Player::hasTiles(std::string const & move, bool resolveBlanks) const {
	// make everything uppercase, just in case
	for (size_t i = 0; i < move.size(); i++) {
		if (move[i] != '?') std::toupper(move[i]);
	}

	std::stringstream ss(move);
	std::string tileString;

	ss >> tileString;

	std::set<Tile*> copy = Hand;

	for (size_t i = 0; i < tileString.size(); i++) {
		if (tileString[i] != '?') std::toupper(tileString[i]);
		std::set<Tile*>::iterator it;
		for (it = copy.begin(); it != copy.end(); ++it) {
			// if it's a PLACEMOVE and you encounter a blank, don't look for next letter in copy
			if ((*it)->getLetter() == tileString[i]) {
				if (resolveBlanks && tileString[i] == '?') i += 1;
				copy.erase(it);
				break;
			}
		}
		if (it == copy.end()) return false;
	}

	return true;

}

// NOTE: move expected to be only string of letters
std::vector<Tile*> Player::takeTiles (std::string const & move, bool resolveBlanks) {
	std::vector<Tile*> take;

	// make everything uppercase, just in case
	for (size_t i = 0; i < move.size(); i++) {
		if (move[i] != '?') std::toupper(move[i]);
	}

	std::stringstream ss(move);
	std::string tileString;
	ss >> tileString;

	if (!hasTiles(move, resolveBlanks)) return take;

	for (size_t i = 0; i < move.size(); i++) {
		std::set<Tile*>::iterator it;
		for (it = Hand.begin(); it != Hand.end(); ++it) {
			if ((*it)->getLetter() == tileString[i]) {
				// if it's a PLACEMOVE and you encounter a blank, don't look for next letter in Hand
				if (resolveBlanks && tileString[i] == '?') {
					i += 1;
					break;
				}
				take.push_back((*it));
				break;
			}
		}
	}

	return take;
}

void Player::eraseTilesFromHand(std::string const & move, bool resolveBlanks) {
	std::vector<Tile*> erase = takeTiles(move, true);
	std::vector<Tile*>::iterator outerIt;

	if (resolveBlanks) {
		bool afterBlank = false;
		for (outerIt = erase.begin(); outerIt != erase.end(); ++outerIt) {
			std::set<Tile*>::iterator it;
			for (it = Hand.begin(); it != Hand.end(); ++it) {
				if (afterBlank) {
					continue;
				}
				if ((*outerIt)->getLetter() == '?') afterBlank = true;
				
				if ((*outerIt) == (*it)) {
					Hand.erase(it);
					break;
				}
			}
		}
	}

	else {
		erase = takeTiles(move, false);
		for (outerIt = erase.begin(); outerIt != erase.end(); ++outerIt) {
			std::set<Tile*>::iterator it;
			for (it = Hand.begin(); it != Hand.end(); ++it) {
				if ((*outerIt) == (*it))
				Hand.erase(it);
				break;
			}
		}
	}

}

size_t Player::getScore() const {
	return score;
}

std::string Player::getName() const {
	return name;
}