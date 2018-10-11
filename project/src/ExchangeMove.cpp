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
	//isValidMove(bag);
	bool move = false;
	std::vector<Tile*> bagTiles;
	bagTiles = player->takeTiles(exchangeTiles, move);
	bag.addTiles(bagTiles);
	//player->eraseTilesFromHand(exchangeTiles, false);

	std::vector<Tile*> newTiles = bag.drawTiles(exchangeTiles.size());
	std::vector<Tile*>::iterator tileIt;

	for (tileIt = newTiles.begin(); tileIt != newTiles.end(); ++tileIt) {
		player->Hand.insert(*tileIt);
	}

}

void ExchangeMove::isValidMove (Bag & bag) {
	while (!player->hasTiles(exchangeTiles, false)) {
		std::cout << "Error: you don't have the necessary tiles." << std::endl;
		std::cout << "Enter new tiles to exchange: " << std::endl;

		std::cin >> exchangeTiles;
	}
}

std::string ExchangeMove::getString() const {
	return exchangeTiles;
}