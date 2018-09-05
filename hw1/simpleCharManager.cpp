#include <cstddef>
#include "simpleCharManager.h"
#include <iostream>

simpleCharManager::simpleCharManager() {
	for (int i=0; i<BUF_SIZE; i++) {
		buffer[i]='\0';
	}

	free_place=buffer;
}

simpleCharManager::~simpleCharManager(){}
             
char* simpleCharManager::alloc_chars(int n) {
	bool start=false; //mark true when a free spot has been found, thus entering the for loop
	bool complete=false; /*mark true when the for loop is completed, meaning there
							is enough room for the whole input*/
	for (int i=0; i<BUF_SIZE; i++) {
		if (buffer[i]=='\0') {
			for (int j=i; j<i+n; j++) {
				free_place=&buffer[i];
				start=true;
				if (buffer[j]!='\0') {
					start=false;
					break;
				}
			}
			complete=true; // all the necessary spots have been checked and are free

			if (start&&complete) {
				start=false;
				complete=false;

				return free_place;
			}
		}
	}
	return NULL;
}

void simpleCharManager::free_chars(char* p) {
	char* beg=buffer; //make a pointer to the beginning of buffer
	int index=(int)(p-beg); //subtracting the pointers gives you index p
		for (int i=0; i<30; i++) {
		std::cout<<i<<"  "<<buffer[i]<<std::endl;
	} 
}