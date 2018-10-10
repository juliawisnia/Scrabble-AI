#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Game.h"
#include "Move.h"

int main (int argc, char *argv[]) {
    if (argc < 2) return -1;
    std::ifstream ifile;

    ifile.open(argv[1]);
    if (ifile.fail()) return -1;

    // read configuration file
    size_t maxTiles = 0;
    std::string bagConfig;
    std::string dictionaryConfig;
    std::string boardConfig;
    size_t seed = 0;
    std::string line;

    while (getline(ifile, line)) {
        std::stringstream read(line);
        std::string type;
        read >> type;

        if (type == "HANDSIZE:") read >> maxTiles;
        else if (type == "TILES:") read >> bagConfig;
        else if (type == "DICTIONARY:") read >> dictionaryConfig;
        else if (type == "BOARD:") read >> boardConfig;
        else if (type == "SEED:") read >> seed;
    }

    std::cout << dictionaryConfig << std::endl;
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
        players.push_back(Player(name, maxTiles, bag));
    }

    // game loop
    //size_t passes = 0;
    //bool endPass = false;
    //bool playerOutTiles = false;
    ConsolePrinter console;
    //Player* finish;

   // while (passes != numPlayers && bag.tilesRemaining() > 0) {
        //passes = 0;
        for (size_t i = 0; i < 10; i++) {
        std::vector<Player>::iterator it;
        for (it = players.begin(); it != players.end(); ++it) {
            console.printBoard(scrabbleBoard);
            console.printHand(*it);

            std::cout << (*it).getName() << " enter a move: ";
            std::string move;
            std::cin >> move;

            std::string moveType = "";
            for (size_t i = 0; i < move.size(); i++) {
                moveType += std::toupper(move[i]);
            }

            Move * playerMove = Move::parseMove(moveType, (*it));
            playerMove->execute(scrabbleBoard, bag, dictionary);
            console.printBoard(scrabbleBoard);
            console.printHand(*it);
            std::cout << "Press enter to continue" << std::endl;
            std::cin.clear();
            std::cin.ignore();
            continue;
        }
    }
    return 0;
}

 /*       if ((*it).getHandTiles().size() == 0) {
            playerOutTiles = true;
            finish = &(*it);
            break;
        }

        if (passes >= numPlayers) {
            endPass = true;
            break;
        }*/
/*
    unsigned int sumTilesRemaining = 0;
    std::vector<Player>::iterator it;
    for (it = players.begin(); it != players.end(); ++it) {
        std::set<Tile*> remaining = (*it).getHandTiles();
        std::set<Tile*>::iterator scoreIt;
        for (scoreIt = remaining.begin(); scoreIt != remaining.end(); ++scoreIt) {
            sumTilesRemaining += (*scoreIt)->getPoints();
        }
    }

    if (playerOutTiles) {
        std::cout << "Player out of tiles" << std::endl;*/
      /*  unsigned int finishScore = 0;
        std::set<std::pair<std::string, unsigned int>> finalScores;

        std::vector<Player>::iterator it;
        for (it = players.begin(); it != players.end(); ++it) {
            unsigned int finalScore = (*it).getScore();
            std::set<Tile*> remaining = (*it).getHandTiles();
            std::set<Tile*>::iterator scoreIt;

            for (scoreIt = remaining.begin(); scoreIt != remaining.end(); ++scoreIt) {
                sumTilesRemaining += (*scoreIt)->getPoints();
            }

            finishScore += sumTilesRemaining;
            finalScore -= sumTilesRemaining;
            std::string name = (*it).getName();
            std::pair <std::string, unsigned int> add;
            add.first = name;
            add.second = finalScore;
            if (&(*it) != finish) finalScores.insert(add);
            else finishScore -= sumTilesRemaining;
        }

        std::pair <std::string, unsigned int> addFinal;
        addFinal.first = finish->getName();
        addFinal.second = finishScore;
        finalScores.insert(addFinal);

        std::set<std::pair<std::string, unsigned int>>::iterator it2;
        std::cout << "Winner: ";
        for (it2 = finalScores.begin(); it2 != finalScores.end(); ++it2) {
            std::cout << it2->first << " with " << it2->second << "points." << std::endl;
        }*/
  /*  }

    if (endPass) {*/
      /*  std::vector<Player>::iterator it;
        std::set<std::pair<std::string, unsigned int>> results;
        for (it = players.begin(); it != players.end(); ++it) {
            std::pair<std::string, unsigned int> add;
            add.first = it->getName();
            add.second = it->getScore();
            results.insert(add);
        }

        std::set<std::pair<std::string, unsigned int>> finalScores;
        std::set<std::pair<std::string, unsigned int>>::iterator it2;
        std::cout << "Winner: ";
        for (it2 = finalScores.begin(); it2 != finalScores.end(); ++it2) {
            std::cout << it2->first << " with " << it2->second << "points." << std::endl;
        }*/
     /*   std::cout << "Passes" << std::endl;

    }

    else std::cout << "More cases to take care of" <<std::endl;*/