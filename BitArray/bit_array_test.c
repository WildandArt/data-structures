#include "bit_array.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <ctype.h>

void BitArrFlipBitTest1();
void BitArrGetBitTest1();
void BitArrSetBitTest();
void BitArrSetOffBitTest();
void BitArrToStringTest();
void BitArrMirrorTest();
void BitArrCountOnBitsTest();

int main()
{

return 0;
}

void BitArrFlipBitTest1()
{
	size_t b = 0x8000000000000000;
	size_t c = 0x80000000;
	size_t result;
	result = BitArrFlipBit(b, 63);
	printf(" %lu ", result);
}
void BitArrGetBitTest1()
{
	size_t result;
	size_t b = 2;
	result = BitArrGetBit( b, 0);
	printf(" %lu ", result);
}

void BitArrSetBitTest()
{
size_t result;
size_t a = 0;
result = BitArrSetBit(a, 3, 1);
printf(" %lu ", result);
}


void BitArrSetOffBitTest()
{
size_t result;
size_t a = 3;
result =  BitArrSetOffBit(a, 0);
printf(" %lu ", result);
}

void BitArrToStringTest()
{
char buffer[70];
size_t a = 32000;
BitArrToString(a, buffer);
puts(buffer);
}

void BitArrMirrorTest()
{
	size_t a = 2;
	size_t result;
	char buffer[70];
	printf(" %lu ", a);
	result = BitArrMirror(a);
	printf(" %lu ", result);
	BitArrToString(result, buffer);
	puts(buffer);
}
void BitArrCountOnBitsTest()
{
	size_t result;
	result =  BitArrCountOnBits(32000);
	printf(" %lu ", result);

}



