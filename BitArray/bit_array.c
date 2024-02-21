

#include<stdio.h>        /* printf, size_t, NULL */	
#include <assert.h>      /*assert                */
#include "bit_array.h"   /* Api                  */





/*******************************************************************/
bitarr_t BitArrFlipBit(bitarr_t bitarr, size_t index)
{
	
	size_t num = (size_t) 1 << index;
	/* flip on first bit */
	bitarr = bitarr ^ num;
	return bitarr;
	
}
/*******************************************************************/
int BitArrGetBit(bitarr_t bitarr, size_t index)
{
	size_t num = (size_t)1 << index;
	num = bitarr & num;
	if (num > 0) 
	{
		return 1;
	}
	return 0;
}
/*******************************************************************/
bitarr_t BitArrSetBit(bitarr_t bitarr, size_t index, int value)
{
	int got_bit = BitArrGetBit(bitarr, index);
	if(got_bit == value)
	{
		return bitarr;
	}
	
	return bitarr ^ ((size_t)1 << index);
}
/*******************************************************************/
bitarr_t BitArrSetOnBit(bitarr_t bitarr,size_t index)
{
	return(bitarr | ((size_t)1 << index));
}
/*******************************************************************/
bitarr_t BitArrSetOffBit(bitarr_t bitarr,size_t index)
{
	int got_bit = BitArrGetBit(bitarr, index);
	if(got_bit)
	{
		return bitarr ^ ((size_t)1 << index);
	}
	return bitarr;
}
/*******************************************************************/
bitarr_t BitArrSetOnAll (bitarr_t bitarr)
{
	(void) bitarr;
	return 0xFFFFFFFFFFFFFFFF;
}
/*******************************************************************/
bitarr_t BitArrSetOffAll(bitarr_t bitarr)
{
	(void) bitarr;
	return 0;
}
/*******************************************************************/
size_t BitArrCountOnBits(bitarr_t bitarr)
{
	size_t counter;
	
	for(counter = 0; bitarr; counter++)
	{
		bitarr = bitarr & (bitarr - 1);
	}
	return counter;
}
/*******************************************************************/
size_t BitArrCountOffBits(bitarr_t bitarr)
{
	return (size_t)64 - BitArrCountOnBits(bitarr);
}
/*******************************************************************/
bitarr_t BitArrRotateLeft(bitarr_t bitarr, size_t num)
{
	return (bitarr << num)|(bitarr >> ((size_t)64 - num));
}
/*******************************************************************/
bitarr_t BitArrRotateRight(bitarr_t bitarr, size_t num)
{
	 return (bitarr >> num)|(bitarr << (64 - num));
}
/*******************************************************************/

char* BitArrToString(bitarr_t bitarr, char* str)
{
	int i;
	assert(str);
	for(i = 0; i < 64; i++)
	{
		str[i] =  BitArrGetBit(bitarr, 63) + '0';
		bitarr = bitarr << (size_t)1;
	}
	str[i] = '\0';
	return str;
}


/*******************************************************************/
bitarr_t BitArrMirror(bitarr_t bitarr)
{
   bitarr = ((bitarr & 0xFFFFFFFF00000000) >> 32) | ((bitarr & 0xFFFFFFFF ) << 32);
   bitarr = ((bitarr & 0xFFFF0000FFFF0000) >> 16) | ((bitarr & 0xFFFF0000FFFF) << 16);
   bitarr = ((bitarr & 0xFF00FF00) >> 8) | ((bitarr & 0xFF00FF00FF00FF) << 8);
   bitarr = ((bitarr & 0xF0F0F0F0F0F0F0F0) >> 4) | ((bitarr & 0xF0F0F0F0F0F0F0F) << 4);
   bitarr = ((bitarr &0xCCCCCCCCCCCCCCCC) >> 2) | ((bitarr & 0x3333333333333333) << 2);
   bitarr = ((bitarr & 0xAAAAAAAAAAAAAAAA) >> 1) | ((bitarr & 0x5555555555555555) << 1);

   return bitarr;
}










