#include <vector>
#include <string>
#include <iostream>
#include "Tile.h"
#include "Player.h"
#include "Bag.h"
#include "Dictionary.h"
#include "Move.h"

PassMove::PassMove(Player * player) {
    p = player;
}

void PassMove::execute(Board & board, Bag & bag, Dictionary & dictionary) {
    std::cout << "You have these tiles: ";
    p->showHand();
	std::cout << "Press enter to continue" << std::endl;
    std::cin.ignore();
}