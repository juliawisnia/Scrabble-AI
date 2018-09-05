#include "flexCharManager.h"
#include <iostream>

flexCharManager::flexCharManager(){
	for (int i=0; i<BUF_SIZE; i++) {
		buffer[i]='\0';
	}

	for (int i=0; i<BUF_SIZE; i++) {
		array[i]=false;
	}

	used_memory=new Mem_Block*[2];
	active_requests=0; //this is going to be the size of used_memory
	used_mem_size=2; //initally 2 empty mem_blocks
}

flexCharManager::~flexCharManager(){
	for (int i=0; i<active_requests; i++) {
		delete used_memory[i];
	}
	delete[] used_memory;
}

char* flexCharManager::alloc_chars(int n) {
	bool complete=false;
	int index=0;

	if (active_requests==0) {
		Mem_Block* a=new Mem_Block(n, buffer);
		active_requests++;

		resize(used_memory, active_requests, used_mem_size);
		used_memory[0]=a;

		for (int i=0; i<n; i++) {
			array[i]=true; //these elements are filled
		}
		 
		return a->physical_location;
	}

	else {
		for (int i=0; i<BUF_SIZE; i++) {
			if (!array[i]) {
				for (int j=0; j<n; j++) {
					if (buffer[i+j]) {
						break;
					}
				}
				index=i;
				complete=true;
				break;
			}
		}

		if (complete) {
			complete=false;
			Mem_Block* a=new Mem_Block(n, &buffer[index]);

			active_requests++;

			resize(used_memory, active_requests, used_mem_size);
			used_memory[active_requests-1]=a;

			for (int i=index; i<index+n; i++) {
				array[i]=true;
			} 
			return a->physical_location;
		}
	}
	return NULL;
}

void flexCharManager::free_chars(char* p) {
					for (int i=0; i<30; i++) {
		std::cout<<i<<"  "<<buffer[i]<<std::endl;
	} 
	int index=0;
	int space=0;
	int c=0;
	for (int i=0; i<active_requests; i++) {
		if (p==used_memory[i]->physical_location) {
			space=used_memory[i]->size;
			index=(used_memory[i]->physical_location-&buffer[0])/sizeof(char);
			delete used_memory[i];
			used_memory[i]='\0';
			c=i;
			break;
		}
	}

	for (int i=index; i<index+space; i++) {
		buffer[i]='\0';
		array[i]=false;
	}

	for (int i=c; i<active_requests-c-1; i++) {
		used_memory[i]=used_memory[i+1];
	}

	active_requests--;
	resize(used_memory, active_requests, used_mem_size);

		for (int i=0; i<30; i++) {
		std::cout<<i<<"  "<<buffer[i]<<std::endl;
	} 
}

void flexCharManager::resize(Mem_Block** &used_memory, int active_requests, int &used_mem_size) {
	if (active_requests>used_mem_size) {
		Mem_Block** temp=new Mem_Block*[used_mem_size*2];
		for (int i=0; i<used_mem_size; i++) {
			temp[i]=used_memory[i];
		}

		used_mem_size=used_mem_size*2;
		delete[] used_memory;
		used_memory=temp;
	}

	else if (used_mem_size/4>active_requests && used_mem_size!=2) {
		Mem_Block** temp=new Mem_Block*[used_mem_size/2];
		for (int i=0; i<used_mem_size; i++) {
			temp[i]=used_memory[i];
		}

		used_mem_size=used_mem_size/2;
		delete[] used_memory;
		used_memory=temp;
	}
}