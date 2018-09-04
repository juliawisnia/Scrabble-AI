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
	bool start=false;
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
			if (array[i]==false) {
				start=true;
				index=i;
				for (int j=index; j<index+n-1; j++) {
					if (index+n>BUF_SIZE-1) {
						break;
					}
					if (array[j]!=false) {
						start=false;
						break;
					}
				}
				complete=true;
			}
		}

		if (start&&complete) {
			start=false;
			complete=false;
			Mem_Block* a=new Mem_Block(n, &buffer[index]);

			active_requests++;

			resize(used_memory, active_requests, used_mem_size);
			used_memory[active_requests-1]=a;

			for (int i=index; i<index+n-1; i++) {
				array[i]=true;
			}
			std::cout<<"Index: "<<index<<std::endl;
			return a->physical_location;
		}
	}

	return NULL;
}

void flexCharManager::free_chars(char* p) {
	int index=0;
	int space=0;
	for (int i=0; i<active_requests; i++) {
		if (p==used_memory[i]->physical_location) {
			std::cout<<active_requests<<std::endl;
			std::cout<<i<<std::endl;
			space=used_memory[i]->size;
			index=(used_memory[i]->physical_location-&buffer[0])/sizeof(char);
			delete used_memory[index];
			used_memory[index]=NULL;
			break;
		}
	}

	for (int i=index; i<index+space-1; i++) {
		buffer[i]='\n';
		array[i]=false;
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

/*int space=0;
	if (active_requests==0) { //no mem blocks created yet
		Mem_Block* a=new Mem_Block(n, buffer);

		active_requests++;
		free_mem-=n;

		resize(used_memory, active_requests, used_mem_size);
		used_memory[active_requests-1]=a;

		return a->physical_location;
	}

	else {
		if (active_requests==1) {
	//this gives index		
	space=&(used_memory[0]->physical_location)-&buffer[0]; //space between first mem block and beginning of buffer

			if (space>=n) {
				Mem_Block* a=new Mem_Block(n, buffer);

				active_requests++;
				free_mem-=n;

				resize(used_memory, active_requests, used_mem_size);
				used_memory[active_requests-1]=a;

				return a->physical_location;
			}

			else {
				space=&buffer[BUF_SIZE-1]-&(*used_memory[0]->physical_location)+used_memory[0]->size;
				if (space>=n) {
					Mem_Block* a=new Mem_Block(n, buffer);

					active_requests++;
					free_mem-=n;

					resize(used_memory, active_requests, used_mem_size);
					used_memory[active_requests-1]=a;

					return a->physical_location;
				}
			}
		}

		else {
			for (int i=0; i<active_requests-1; i++) {
				space=&(*used_memory[i+1]->physical_location)-&(*used_memory[i]->physical_location)
				-used_memory[i]->size; //size of gaps between adjacent mem blocks

				if (space>=n) {
					Mem_Block* a=new Mem_Block(n, used_memory[i]->physical_location);
	
					active_requests++;
					free_mem-=n;

					resize(used_memory, active_requests, used_mem_size);
					used_memory[active_requests-1]=a;

					return a->physical_location;
				}
			}

			space=&buffer[BUF_SIZE-1]-&(*used_memory[active_requests-1]->physical_location)
			-used_memory[active_requests-1]->size; //gap from last element in buffer to end

			if (space>=n) {
				Mem_Block* a=new Mem_Block(n, used_memory[active_requests-1]->physical_location);

				active_requests++;
				free_mem-=n;

				resize(used_memory, active_requests, used_mem_size);
				used_memory[active_requests-1]=a;

				return a->physical_location;
			}

		}
	}*/