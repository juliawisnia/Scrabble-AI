#include <vector>
#include <string>
#include <iostream>
#include "Move.h"

ExchangeMove::ExchangeMove(std::string tileString, Player * p) {
	for (size_t i = 0; i < tileString.size(); i++) {
		exchangeTiles += std::toupper(tileString[i]);
	}
	player = p;
}

void ExchangeMove::execute(Board & board, Bag & bag, Dictionary & dictionary) {
	// will query user until the move is valid
	while (!isValidMove(bag)) {}
	bool move = false;
	std::vector<Tile*> bagTiles;
	bagTiles = player->takeTiles(exchangeTiles, move);
	bag.addTiles(bagTiles);
	player->eraseTilesFromHand(exchangeTiles, false);

	size_t i = exchangeTiles.size();
	std::vector<Tile*> newTiles = bag.drawTiles(i);
	std::vector<Tile*>::iterator tileIt;

	for (tileIt = newTiles.begin(); tileIt != newTiles.end(); ++tileIt) {
		player->Hand.insert(*tileIt);
	}

}

bool ExchangeMove::isValidMove (Bag & bag) {
	if (!player->hasTiles(exchangeTiles, false)) {
		std::cout << "Error: you don't have the necessary tiles." << std::endl;
		std::cout << "Enter new tiles to exchange: " << std::endl;

		std::cin.clear();
		std::cin >> exchangeTiles;
		return false;
	}
	return true;
}

std::string ExchangeMove::getString() const {
	return exchangeTiles;
}