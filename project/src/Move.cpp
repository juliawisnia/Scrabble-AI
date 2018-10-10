#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "Move.h"

Move * Move::parseMove(std::string moveString, Player &p) {
    if (moveString == "PLACE") {
        char dir = 0;
        bool horizontal = false;
        size_t row = 0;
        size_t column = 0;
        std::string tileString = "";

        std::cin >> dir >> row >> column >> tileString;
        // flipped bc changing
        if (dir == '-') horizontal = false;
        else horizontal = true;

        PlaceMove* place = new PlaceMove(row, column, horizontal, tileString, &p);
        return place;
    }

    else if (moveString == "EXCHANGE") {
        std::string tileString;
        std::cin >> tileString;
        ExchangeMove* exchange = new ExchangeMove(tileString, &p);
        return exchange;
    }

    else  {
        PassMove* pass = new PassMove(&p);
        return pass;
    }

}