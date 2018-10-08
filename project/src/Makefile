CXX = g++
CPPFLAGS = -g -Wall -std=c++11 -I$(LIB_DIR)
BIN_DIR = bin
LIB_DIR = lib
SRC_DIR = src

all: PlayerTest

PlayerTest: PlayerTest.cpp Board.cpp Board.h ConsolePrinter.cpp ConsolePrinter.h Player.cpp Player.h Move.cpp Move.h Bag.cpp Bag.h PlaceMove.cpp ExchangeMove.cpp Tile.h
	$(CXX) $(CPPFLAGS) $^ -o PlayerTest

.PHONY: clean
clean:
	rm -rf $(BIN_DIR)