#include "stack.h"
#include <stdio.h>
void testStackIsEmpty();
void testStackCapacity();
void testPeek();

int main()

{
testPeek();
	return 0;
}

void DestroyTest()
{
	size_t capacity = 8;
	stack_t *s = StackCreate(capacity);
	StackDestroy(s);
}

void testPop()
{
	size_t capacity = 8;
	stack_t *s = StackCreate(capacity);
	StackPop(s);
	StackDestroy(s);
}

void testPush()
{
	size_t capacity = 8;
	stack_t *s;
	int x = 8;
	s = StackCreate(capacity);
		
	StackPush(s, &x);

	StackDestroy(s);
}

void testPeek()
{
	stack_t *s;
	size_t capacity = 8;
	int x = 3;
	s = StackCreate(capacity);
	StackPush(s, &x);
	printf(" Stack Peek \n");
	printf(" Stack Peek %d ", *(int*)StackPeek(s));
	StackDestroy(s);
}
void testStackIsEmpty()
{

	int x = 8;
	size_t capacity = 8;
	stack_t *s;
	int result;
	
	s = StackCreate(capacity);
	StackPush(s, &x);
	result = StackIsEmpty(s);
	printf(" 1 yes, 0 no: %d ", result);
}


void testStackCapacity()
{
	int x = 8;
	size_t capacity = 7;
	stack_t *s;
	size_t result;
	s = StackCreate(capacity);
	result = StackCapacity(s);
	printf("%lu", result);

}






