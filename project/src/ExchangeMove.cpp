#include <vector>
#include <string>
#include "Move.h"

ExchangeMove::ExchangeMove(std::string tileString, Player * p) {
	exchangeTiles = tileString;
}

void ExchangeMove::execute(Board & board, Bag & bag, Dictionary & dictionary) {
	// will query user until the move is valid
	isValidMove(bag, dictionary);

}

void ExchangeMove::isValidMove (Bag & bag, Dictionary & dictionary, Player * p) {
	while (!p->hasTiles()) {
		std::cout << "Error: you don't have the necessary tiles." << std::endl;
		std::cout << "Enter new tiles to exchange: " << std::endl;

		std::cin >> exchangeTiles;
	}

}