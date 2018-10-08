#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Game.h"

int main (int argc, char *argv[]) {
    if (argc < 2) return -1;

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

    // game loop
    size_t passes = 0;
    bool endPass = false;
    bool playerOutTiles = false;
    ConsolePrinter console;
    Player* finish;

    while (passes != numPlayers && bag.tilesRemaining() > 0) {
        passes = 0;
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
                bool horizontal;
                size_t row;
                size_t column;
                std::string tileString;

                ss >> dir >> row >> column >> tileString;
                if (dir == '-') horizontal = true;
                else horizontal = false;

                PlaceMove place(row, column, horizontal, tileString, &(*it));

                place.execute(scrabbleBoard, bag, dictionary);
                console.printBoard(scrabbleBoard);
            }

            else if (moveType == "EXCHANGE") {
                std::string tileString;
                ss >> tileString;

                ExchangeMove exchange(tileString, &(*it));
                exchange.execute(scrabbleBoard, bag, dictionary);
                console.printBoard(scrabbleBoard);
            }

            else {
                passes++;
                PassMove pass(&(*it));
                pass.execute(scrabbleBoard, bag, dictionary);
                console.printBoard(scrabbleBoard);
            }
        }
        if (it->getHandTiles().size() == 0) {
            playerOutTiles = true;
            finish = &(*it);
            break;
        }

        if (passes >= numPlayers) {
            endPass = true;
            break;
        }
    } 

    unsigned int sumTilesRemaining;
    std::vector<Player>::iterator it;
    for (it = players.begin(); it != players.end(); ++it) {
        std::set<Tile*> remaining = it->getHandTiles();
        std::set<Tile*>::iterator scoreIt;
        for (scoreIt = remaining.begin(); scoreIt != remaining.end(); ++scoreIt) {
            sumTilesRemaining += (*scoreIt)->getPoints();
        }
    }

    if (playerOutTiles) {
        unsigned int finishScore;
        std::set<std::pair<std::string, unsigned int>> finalScores;

        std::vector<Player>::iterator it;
        for (it = players.begin(); it != players.end(); ++it) {
            unsigned int finalScore = it->getScore();
            std::set<Tile*> remaining = it->getHandTiles();
            std::set<Tile*>::iterator scoreIt;

            for (scoreIt = remaining.begin(); scoreIt != remaining.end(); ++scoreIt) {
                sumTilesRemaining += (*scoreIt)->getPoints();
            }

            finishScore += sumTilesRemaining;
            finalScore -= sumTilesRemaining;
            std::string name = it->getName();
            std::pair add(name, finalScore);
            if (&(*it) != finish) finalScores.insert(add);
            else finishScore -= sumTilesRemaining;
        }

        std::pair addFinal(finish->getName(), finishScore);
        finalScores.insert(addFinal);

        std::set<std::pair<std::string, unsigned int>>::iterator it2;
        std::cout << "Winner: ";
        for (it2 = finalScores.begin(); it2 != finalScores.end(); ++it2) {
            std::cout << it2->first << " with " << it2->second << "points." << std::endl;
        }
    }

    if (endPass) {
        std::vector<Player>::iterator it;
        std::set<std::pair<std::string, unsigned int>> results;
        for (it = players.begin(); it != players.end(); ++it) {
            std::pair add (it->getName(), it->getScore());
            results.insert(add);
        }

        std::set<std::pair<std::string, unsigned int>> finalScores;
        std::set<std::pair<std::string, unsigned int>>::iterator it2;
        std::cout << "Winner: ";
        for (it2 = finalScores.begin(); it2 != finalScores.end(); ++it2) {
            std::cout << it2->first << " with " << it2->second << "points." << std::endl;
        }

    }

    else std::cout << "More cases to take care of" <<std::endl;
    return 0;
}