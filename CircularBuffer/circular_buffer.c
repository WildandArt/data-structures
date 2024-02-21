
#include <stdlib.h> 	/* malloc, free     */  
#include <unistd.h> 	/* ssize_t ,size_t  */  
#include <assert.h> 	/* assert      	    */
#include "circular_buffer.h"	/* personal use     */


struct cbuff
{
	size_t read;
	size_t size;
	size_t buffer_capacity;
	char buffer[1]; 
	/*sem1, sem2, mutex1 mutex2 */
	/* tail =0 */
};

cbuff_t *CircularBufferCreate(size_t capacity)
{
	cbuff_t *cbuffer = NULL;
	/* alignment due to struct padding: padding is 7 */
	size_t buff_size = capacity < 8 ? 0 : capacity - 8;
	cbuffer = (cbuff_t*)malloc(sizeof(cbuff_t) + (buff_size));
	if(!cbuffer)
	{
		return NULL;
	}

	cbuffer->read = 0;
	cbuffer->size = 0;
	cbuffer->buffer_capacity = capacity;
	return cbuffer;
}
void CircularBufferDestroy(cbuff_t *buffer)
{
	assert(buffer);
	free(buffer);
	buffer = NULL;
}
size_t CircularBufferBufsiz(const cbuff_t *buffer)
{
	assert(buffer);
	return buffer->buffer_capacity;
}
int CircularBufferIsEmpty(const cbuff_t *buffer)
{
	assert(buffer);
	return buffer->size == 0;
}
size_t CircularBufferFreeSpace(const cbuff_t *buffer)
{
	assert(buffer);
	return buffer->buffer_capacity - buffer->size ;
}

ssize_t CircularBufferWrite(cbuff_t *buffer, const void *source, size_t amount)
{
	size_t free_space = CircularBufferFreeSpace(buffer);
	size_t counter = 0;									 
	assert(buffer);
	assert(source);
		
	if(amount > free_space)
	{
		amount = free_space;
	}
	
	while(amount && (buffer->size < buffer->buffer_capacity))
	{
		buffer->buffer[(buffer->read + buffer->size)\
		 % buffer->buffer_capacity] = *(char*)(source); 

		(*(char**)&source)++;									
		buffer->size++;
		counter++;
		amount--;
	}

	return counter;

}

ssize_t CircularBufferRead(cbuff_t *buffer, void *dest, size_t amount)
{	
	size_t counter = 0;										
	assert(buffer);
	assert(dest);
	
	if(amount > buffer->size)
		 amount = buffer->size;

	while(amount)						
	{
		*(char*)dest = buffer->buffer[buffer->read];
		buffer->read = (buffer->read + 1) % buffer->buffer_capacity;
		(*(char**)&dest)++;								
		amount--;
		(buffer->size)--;
		counter++;
	}
	return counter;
}





