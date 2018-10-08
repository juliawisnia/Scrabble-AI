#include <iostream>
#include <sstream>
#include "Dictionary.h"
//#include "Board.h"
//#include "Bag.h"

int main(int argc, char *argv[]) {

    std::stringstream ss(argv[1]);
    std::string dictionaryConfig;
    ss >> dictionaryConfig;

    Dictionary dictionary(dictionaryConfig);
    //Board scrabbleBoard(boardConfig);
    //Bag bag(bagConfig, seed);

    std::string validWord = "HELLO";
    std::string invalidWord = "helllooo";

    if (dictionary.isLegalWord(validWord)) {
        std::cout << "Test Passed: valid test" << std::endl;

    }

    else  {
        std::cout << "read as invalid" <<std::endl;
    }

    if (!dictionary.isLegalWord(invalidWord)) {
        std::cout << "Test Passed invalidWord" << std::endl;
    }

    else std::cout << "read as valid";

    return 0;



}