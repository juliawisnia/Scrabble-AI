#include <string>
#include <set>
#include <vector>
#include "Tile.h"

Player::Player (std::string const & playerName, size_t maxTiles) {
	name = playerName
	score = 0;
}

Player::~Player() {

}

std::set<Tile*> Player::getHandTiles() const {
	return Hand;
}

bool Player::hasTiles(std::string const & move, bool resolveBlanks) const {
	std::set<Tile*> temp = getHandTiles();

	for (size_t i = 0; i < move->word.size(); i++) {
		std::set<Tile*>::iterator it;
		it = find.temp(move->word[i]);

		if (it != temp.end()) {
			temp.erase(it);
		}

		else return false;

	}

	return true;
}

std::vector<Tile*> Player::takeTiles (std::string const & move, bool resolveBlanks) {

}

void Player::addTiles (std::vector<Tile*> const & tilesToAdd) {

}