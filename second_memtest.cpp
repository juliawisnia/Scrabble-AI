#include <iostream>
#include <stdlib.h>
#include "flexCharManager.h"

int main(int argc, char *argv[])
{
	flexCharManager simplest_mem_manager;
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

	/*char* buf=simplest_mem_manager.alloc_chars(3);
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
	f[0]='h', f[1]='a', f[2]='t';*/

	return 0;
}