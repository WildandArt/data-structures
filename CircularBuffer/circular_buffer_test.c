#include "circular_buffer.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
int main()
{

	cbuff_t *cbuffer = CircularBufferCreate(11);
	char str[] = "wrklooooooo";
	char dest[100]="kkkkkkkkkk";
	puts("\n-------------------Writing---------------------------------\n");
	printf("\nhow many was written:%lu\n",CircularBufferWrite(cbuffer, &str, 6));
	
	printf("\nFreeSpace to write %lu \n",CircularBufferFreeSpace(cbuffer));
	puts("\n-------------------Reading---------------------------------\n");
	printf("\nhow many read : %lu ", CircularBufferRead(cbuffer, dest, 1));
	puts("\n-------------------Writing---------------------------------\n");
	printf("\nhow many was written:%lu\n",CircularBufferWrite(cbuffer, &str, 6));
	printf("\nFreeSpace to write %lu \n",CircularBufferFreeSpace(cbuffer));
	puts("\n-------------------Reading---------------------------------\n");
	printf("\nhow many read : %lu ", CircularBufferRead(cbuffer, dest, 11));
	printf("\nFreeSpace to write %lu \n",CircularBufferFreeSpace(cbuffer));
	CircularBufferDestroy(cbuffer);
	return 0;
}
