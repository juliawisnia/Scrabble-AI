#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Game.h"

int main (int argc, char *argv[]) {
    if (argc < 3) return -1;

    // read configuration file
    size_t maxTiles;
    std::string bagConfig;
    std::string dictionaryConfig;
    std::string boardConfig;
    size_t seed;
    
    std::stringstream ss(argv[1]);
    std::string line;

    while (getline(ss, line)) {
        std::stringstream read(line);
        std::string type;
        ss >> type;

        if (type == "HANDSIZE:") read >> maxTiles;
        else if (type == "TILES:") read >> bagConfig;
        else if (type == "DICTIONARY:") read >> dictionaryConfig;
        else if (type == "BOARD:") read >> boardConfig;
        else if (type == "SEED:") read >> seed;
    }

    Dictionary dictionary(dictionaryConfig);
    Board scrabbleBoard(boardConfig);
    Bag bag(bagConfig, seed);

    size_t numPlayers = 0;
    std::cout << "Please enter the number of players (1-8): ";
    std::cin >> numPlayers;

    while (numPlayers > 8 || numPlayers < 1) {
        std::cout << "Enter a valid number of players (1-8): ";
        std::cin >> numPlayers;
    }

    std::vector<Player> players;
    for (size_t i = 1; i <= numPlayers; i++) {
        std::string name;
        std::cout << "Enter player " << i << "'s name: ";
        std::cin >> name;
        players.push_back(Player(name, maxTiles));
    }

    size_t passes = 0;

    // game loop
    while (passes != numPlayers && bag.tilesRemaining() > 0) {
        std::vector<Player>::iterator it;
        for (it = players.begin(); it != players.end(); ++it) {
            std::string moveString;
            std::cout << it->getName() << " enter a move: ";
            std::cin >> moveString;

            std::stringstream ss(moveString);
            std::string moveType;
            ss >> moveType;

            if (moveType == "PLACE") {
                char dir;
                
            }
        }
    } 
}