#include <iostream>
#include <stdlib.h>
#include "flexCharManager.h"

int main(int argc, char *argv[])
{
	flexCharManager simplest_mem_manager;

	char* buf=simplest_mem_manager.alloc_chars(3);
	buf[0]='i', buf[1]='n', buf[2]=' ';

	char* b=simplest_mem_manager.alloc_chars(7);
	b[0]='F', b[1]='r', b[2]='e', b[3]='n',
	b[4]='c', b[5]='h', b[6]=' ';

	char* c=simplest_mem_manager.alloc_chars(7);
	c[0]='c', c[1]='h', c[2]='a', c[3]='p', c[4]='e', c[5]='a', c[6]='u';

	simplest_mem_manager.free_chars(buf);

	char* d=simplest_mem_manager.alloc_chars(3);
	d[0]='t', d[1]='o', d[2]='p';

	simplest_mem_manager.free_chars(b);
	char* e=simplest_mem_manager.alloc_chars(8);
	e[0]='s', e[1]='o', e[2]='m', e[3]='b', e[4]='r', e[5]='e', e[6]='r', e[7]='o';
	char* f=simplest_mem_manager.alloc_chars(3);
	f[0]='h', f[1]='a', f[2]='t';

	char* g=simplest_mem_manager.alloc_chars(1);

	

	return 0;
}