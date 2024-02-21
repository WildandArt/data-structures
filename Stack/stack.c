/*
author: Art
reviewer: David
date : 2 March											
*/


#include<stdio.h>  /* printf, size_t, NULL */					
#include<stdlib.h> /* malloc               */					
#include<assert.h> /* assert               */
#include"stack.h"   /* Api                  */			

struct stack
{
	size_t capacity;
	size_t top;
	void **elements;
};


stack_t *StackCreate(size_t capacity)
{
	stack_t *stack = (stack_t*)malloc(sizeof(stack_t));			
	if( NULL == stack)
	{
		return NULL;
	}
	
	stack->elements = (void **) malloc( sizeof(void*) * capacity);
	
	if( NULL == stack->elements)
	{	
		free(stack);							
		return NULL;
	}
	
	stack->top = 0;
	
	stack->capacity = capacity;
	
	return stack;
		
}

void StackPop(stack_t *stack)
{
	assert(stack);
	if(0 == stack->top)
	{
		return;
	}
	
	stack->top -= 1;
}

void StackPush(stack_t *stack, void *element)
{
	assert(stack);
	
	if((stack->capacity) < (stack->top))
	{
		return;
	}
	
	stack->elements[stack->top] = element;
	
	stack->top += 1;
}
void StackDestroy(stack_t *stack)
{
	assert(stack);
	free(stack->elements);
	free(stack);

}

void *StackPeek(stack_t *stack)
{
	assert(stack);
	if(stack->top == 0)
	{
		return NULL;
	}

	return stack->elements[(stack->top) - 1];
}
size_t StackSize(stack_t *stack)
{
	assert(stack);
	return stack->top;

}
size_t StackCapacity(stack_t *stack)
{
	assert(stack);
	return stack->capacity;
}

int StackIsEmpty(stack_t *stack)
{
	assert(stack);
	return stack->top == 0;
}








