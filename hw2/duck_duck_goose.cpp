#include <iostream>
#include <ostream>
#include <fstream>
#include "duck_duck_goose.h"

void simulateDDGRound(GameData * gameData, std::ostream & output) {
	size_t n=gameData->playerList.size();
	size_t m=rand()%(4*n); // choose goose index

	//print all the ducks
	for (size_t i=0; i<m; i++) {
		output<<gameData->playerList.get(i)<<" is a Duck.\n";
	}
	//player m is the goose
	output<<gameData->playerList.get(m)<<" is a Goose!\n";

	size_t gooseNum=rand()%50;
	size_t itNum=rand()%50;

	//repick in case of tie until no longer a tie
	while (gooseNum==itNum) {
		gooseNum=rand()%50;
		itNum=rand()%50;
	}

	//it picks a bigger number
	if (itNum>gooseNum) {
		output<<gameData->itPlayerID<<" took "<<gameData->playerList.get(m)
			<<"'s spot!\n";
		//goose now becomes it, set goose ID to old itPlayerID
		gameData->playerList.set(m, gameData->itPlayerID);
		//set itPlayerID to goose ID
		gameData->itPlayerID=gameData->playerList.get(m);
	}

	//goose picks a bigger number
	else {
		output<<gameData->itPlayerID<<" is out!\n";
		//if goose is the only player left
		if (gameData->playerList.size()==1) {
			output<<"Winner is "<<gameData->playerList.get(m)<<"!\n";
			gameData->itPlayerID=0;
		}
		//more players left
		else {
			n=gameData->playerList.size();
			size_t newIt=rand()%n;

			//get random numbers until it is not the goose
			while (newIt==m) {
				newIt=rand()%n;
			}
			//set itPlayerID to the new it's ID
			gameData->itPlayerID=gameData->playerList.get(newIt);
			output<<gameData->itPlayerID<<" was chosen as the new it.\n";
			//remove the item from the linked list
			gameData->playerList.remove(newIt);
		}
	}
}

int main(int argc, char *argv[]) {
	//not correct amount of arguments
	if (argc!=3) {
		return -1;
	}
	std::ifstream ifile;

	unsigned int seed;
	size_t players;
	size_t itID;
	size_t id;

	ifile.open(argv[1]);
	//cannot open
	if (ifile.fail()) {
		return -1;
	}

	ifile>>seed;
	ifile>>players;
	ifile>>itID;

	GameData* list=new GameData();
	list->itPlayerID=itID;
	//create a linked list of values for players (let first it be player 0)
	for (size_t i=0; i<players-1; i++) {
		ifile>>id;
		list->playerList.push_back(id);
	}

	ifile.close();

	//sent seed for rand()
	srand(seed);
	
	//create output, open to start writing to it
	std::ofstream output;
	output.open(argv[2]);

	//only true when someone wins
	while (list->itPlayerID!=0) {
		simulateDDGRound(list, output);
	}

	//deallocate heap memory
	delete list;

	return 0;
}