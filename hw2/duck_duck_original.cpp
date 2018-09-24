#include <iostream>
#include <ostream>
#include <fstream>
#include "duck_duck_goose.h"

void simulateDDGRound(GameData * gameData, std::ostream & output) {
	size_t players=data->playerList.size();
	size_t m=rand()%(4*(players-1)+1); //inclusive

	size_t gID=data->playerList.get(m);

	size_t gNum=0; //goose rand number
	size_t itNum=0; //it rand number

	for (size_t i=0; i<m; i++) {
		output<<data->playerList.get(i)<<" is a Duck."<<std::endl;
	}
	output<<data->playerList.get(m)<<" is a Goose!"<<std::endl;

	while (gNum==itNum) {
		gNum=rand()%50;
		itNum=rand()%50;	
	}

	//it takes the gooses spot, goose becomes it
	if (itNum>gNum) {
		//set goose's index to 'it's' index
		output<<data->itPlayerID<<" took "<<gID<<"'s spot!"<<std::endl;
		data->playerList.set(m, data->itPlayerID);
		data->itPlayerID=gID;
		//data->playerList.remove(m);
	}

	//goose keeps its spot in the circle, it player is not in the game
	else {
		output<<data->itPlayerID<<" is out!"<<std::endl;
		players=data->playerList.size();

		if (players<=1) {
			output<<"Winner is "<<gID<<"!"<<std::endl;
			data->itPlayerID=0;
			return;
		}

		size_t newIt=rand()%players-1;

		while(newIt==gID) {
			newIt=rand()%players-1;
		}

		output<<data->playerList.get(newIt)<<" was chosen as the new it."<<std::endl;
		data->playerList.remove(newIt);
	}
	
}

int main(int argc, char *argv[]) {
	std::ifstream ifile;
	if (!ifile.fail()) return -1;

	unsigned int seed;
	size_t players;
	size_t it_id;
	size_t id;

	ifile.open(argv[1]);

	ifile>>seed;
	ifile>>players;
	ifile>>it_id;

	ifile.close();

	std::filebuf fb;
	std::ostream output(&fb);

	GameData* list;
	list->itPlayerID=it_id;
	//create a linked list of values for players (let first it be player 0)
	for (size_t i=0; i<players-1; i++) {
		ifile>>id;
		list->playerList.push_back(id);
	}

	srand(seed);

	while (list->itPlayerID!=0) {
		simulateDDGRound(list, output);
	}

	return 0;
}