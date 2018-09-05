#include <iostream>
#include <stdlib.h>
#include "simpleCharManager.h"

int main(int argc, char *argv[])
{
	simpleCharManager simplest_mem_manager;

	char* buf=simplest_mem_manager.alloc_chars(13);

	buf[0]='H', buf[1]='e', buf[2]='l'; buf[3]='l', buf[4]='o',
	buf[5]=' ', buf[6]='w', buf[7]='o', buf[8]='r', buf[9]='l',
	buf[10]='d', buf[11]='!', buf[12]='\n';

	simplest_mem_manager.free_chars(&buf[6]);
	char* buf2=simplest_mem_manager.alloc_chars(11);

	buf2[0]='m', buf2[1]='o', buf2[2]='o'; buf2[3]='n', buf2[4]='!',
	buf2[5]=' ', buf2[6]='B', buf2[7]='y', buf2[8]='e', buf2[9]='.',
	buf2[10]='\n';

	char* buf3=simplest_mem_manager.alloc_chars(1);

	return 0;
}

