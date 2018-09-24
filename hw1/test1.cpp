#include <iostream>
#include <stdlib.h>
#include "simpleCharManager.h"

int main(int argc, char *argv[]) {
	simpleCharManager simplest_mem_manager;

	char* c1 = simplest_mem_manager.alloc_chars(2);
	c1[0] = 'h';
	c1[1] = 'i';
	char* c2 = simplest_mem_manager.alloc_chars(3);
	std::cout << c1[0] << c1[1] << std::endl;
	simplest_mem_manager.free_chars(c1);
}