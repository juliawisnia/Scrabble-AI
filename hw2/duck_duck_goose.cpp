#include <iostream>
#include <ostream>
#include <fstream>
#include "duck_duck_goose.h"

void simulateDDGRound(GameData * data, std::ostream & output) {
	size_t players=data->playerList.size();
	size_t m=rand()%4*(players-1);
	size_t g_id=data->playerList.get(m);
	size_t g_num=0; //goose rand number
	size_t it_num=0; //it rand number

	for (size_t i=0; i<m; i++) {
		output<<data->playerList.get(i)<<" is a Duck."<<std::endl;
	}
	output<<data->playerList.get(m+1)<<" is a Goose!"<<std::endl;

	while (g_num==it_num) {
		g_num=rand()%50;
		it_num=rand()%50;	
	}

	if (it_num>g_num) {
		//set goose's index to 'it's' index
		data->playerList.set(m, data->itPlayerID);
		output<<data->itPlayerID<<" took "<<g_id<<"'s spot!"<<std::endl;
		data->itPlayerID=g_id;
	}

	else {
		output<<data->itPlayerID<<" is out!"<<std::endl;
		if (players==1) {
			output<<"Winner is "<<g_id<<"!"<<std::endl;
			data->itPlayerID=0;
		}
		players=data->playerList.size();

		int new_it=rand()%players;
		output<<data->playerList.get(new_it)<<" was chosen as the new it."<<std::endl;
		data->playerList.remove(new_it);
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
	//list->playerList.push_back(it_id);
	//create a linked list of values for players (let first it be player 0)
	for (size_t i=0; i<players+3; i++) {
		ifile>>id;
		list->playerList.push_back(id);
	}

	srand(seed);

	simulateDDGRound(list, output);

	return 0;
}