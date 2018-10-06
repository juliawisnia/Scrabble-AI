#include <vector>
#include <string>
#include "Tile.h"
#include "Player.h"
#include "Bag.h"
#include "Dictionary.h"

ExchangeMove::ExchangeMove(std::string tileString, Player * p) {

}

void ExchangeMove::execute(Board & board, Bag & bag, Dictionary & dictionary) {
	// will query user until the move is valid
	isValidMove(bag, dictionary);

}

bool ExchangeMove::isValidMove (Bag & bag, Dictionary & dictionary) {
	
}