#include <iostream>
#include <ostream>
#include <fstream>
#include "duck_duck_goose.h"

void simulateDDGRound(GameData * gameData, std::ostream & output) {
	size_t n=gameData->playerList.size();
	size_t m=rand()%(4*(n-1)+1); // choose rand index

	for (size_t i=0; i<m; i++) {
		output<<gameData->playerList.get(i)<<" is a Duck."<<std::endl;
	}
	output<<gameData->playerList.get(m)<<" is a Goose!"<<std::endl;

	size_t gooseNum=rand()%50;
	size_t itNum=rand()%50;

	//repick in case of tie
	while (gooseNum==itNum) {
		gooseNum=rand()%50;
		itNum=rand()%50;
	}

	if (itNum>gooseNum) {
		output<<gameData->itPlayerID<<" took "<<gameData->playerList.get(m)<<"'s spot!"<<std::endl;
		gameData->playerList.set(m, gameData->itPlayerID);
		gameData->itPlayerID=gameData->playerList.get(m);
	}

	else {
		output<<gameData->itPlayerID<<" is out!"<<std::endl;
		//if goose is the only player left
		if (gameData->playerList.size()==1) {
			output<<"Winner is "<<gameData->playerList.get(m)<<"!"<<std::endl;
			gameData->itPlayerID=0;
		}
		//more players left!
		else {
			n=gameData->playerList.size();
			size_t newIt=rand()%(n+1);

			while (newIt==m) {
				newIt=rand()%(n+1);
			}
			output<<gameData->playerList.get(newIt)<<" was chosen as the new it."<<std::endl;
			gameData->playerList.remove(newIt);
		}
	}
}

int main(int argc, char *argv[]) {
	std::ifstream ifile;
	if (argc<3) {
		return -1;
	}

	unsigned int seed;
	size_t players;
	size_t itID;
	size_t id;

	ifile.open(argv[1]);
	if (ifile.fail()) {
		return -1;
	}

	ifile>>seed;
	ifile>>players;
	ifile>>itID;

	GameData* list;
	list->itPlayerID=itID;
	//create a linked list of values for players (let first it be player 0)
	for (size_t i=0; i<players-1; i++) {
		ifile>>id;
		list->playerList.push_back(id);
	}

	ifile.close();

	srand(seed);
	//output.open(argv[2]);
	std::filebuf fb;
	std::ostream output(&fb);

	while (list->itPlayerID!=0) {
		simulateDDGRound(list, output);
	}

	return 0;
}