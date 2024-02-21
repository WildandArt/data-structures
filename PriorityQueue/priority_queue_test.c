#include<stdio.h>
#include"priority_queue.h"
#include<assert.h>

int IsMatchInt(void *data, void *new_data)
{
	return *(int*)data == *(int*)new_data;
}

int CompareInts(void *data, void *new_data)
{
	return *(int*)data - *(int*)new_data;
}
void testCreateDestroy();
void testEnqueue();
void testDequeue();
void testPeek();
void testErase();
void testClear();
void testSize();

int main()
{
printf("\nTests: testCreateDestroy, testEnqueue,testPeek,\n testErase, testClear, testSize\n");
	testCreateDestroy();
	testEnqueue();
	testDequeue();
	testPeek();
	testErase();
	testClear();
	testSize();
	return 0;
}

void testCreateDestroy()
{
	int (*cmp)(void* data, void *new_data) = CompareInts;
	priority_queue_t *q = PriorityQueueCreate(cmp);
	printf("\nTEST CreateDestroy SUCCESS");
	PriorityQueueDestroy(q);

}

void testEnqueue()
{
	int num1 = 1;
	int num10 = 10;
	int num20 = 20;
	int num30 = 30;
	int result = 0;
	int (*cmp)(void* data, void *new_data) = CompareInts;
	priority_queue_t *q = PriorityQueueCreate(cmp);
	assert(0 == PriorityQueueSize(q));
	result = PriorityQueueEnqueue(q, (void*)&num30);
	assert(0 == result);
	assert(1 == PriorityQueueSize(q));
	result = PriorityQueueEnqueue(q, (void*)&num10);
	assert(0 == result);
	assert(30 == *(int*)PriorityQueuePeek(q));
	result = PriorityQueueEnqueue(q, (void*)&num20);
	assert(0 == result);
	result = PriorityQueueEnqueue(q, (void*)&num1);
	
	assert(30 == *(int*)PriorityQueuePeek(q));
	assert(4 == PriorityQueueSize(q));
	PriorityQueueDequeue(q);
	PriorityQueueDequeue(q);
	assert(2 == PriorityQueueSize(q));
	printf("\nTEST Enqueue SUCCESS");
	PriorityQueueDestroy(q);
}
void testDequeue()
{
	priority_queue_t *q = PriorityQueueCreate(CompareInts);
	int num1 = 1;
	int num10 = 10;
	int num20 = 20;
	int num30 = 30;
	int result = 0;
	assert(PriorityQueueIsEmpty(q));
	result = PriorityQueueEnqueue(q, (void*)&num10);
	assert(!PriorityQueueIsEmpty(q));
	PriorityQueueDequeue(q);
	assert(PriorityQueueIsEmpty(q));
	printf("\nTEST Dequeue SUCCESS");
	
	PriorityQueueDestroy(q);
}

void testPeek()
{
	void *result;
	int num10 = 10;
	int (*cmp)(void* data, void *new_data) = CompareInts;
	priority_queue_t *q = PriorityQueueCreate(cmp);
	PriorityQueueEnqueue(q, (void*)&num10);
	result = PriorityQueuePeek(q);
	printf("\nPeek result %d", *(int*)result);
	printf("\nTEST PEEK SUCCESS");
	PriorityQueueDestroy(q);
}
void testSize()
{
	size_t size;
	int num10 = 10;
	priority_queue_t *q = PriorityQueueCreate(CompareInts);
	assert(0 == PriorityQueueSize(q));
	PriorityQueueEnqueue(q, (void*)&num10);
	assert(1 == PriorityQueueSize(q));
	PriorityQueueDequeue(q);
	assert(0 == PriorityQueueSize(q));
	printf("\nTEST Size SUCCESS");

}
void testErase()
{
/*1. check fail condition
2. check success, erase something that is there
 */
	void *result;
	int num1 = 1;
	int num10 = 10;
	int num20 = 20;
	priority_queue_t *q = PriorityQueueCreate(CompareInts);
	
	assert(1 == PriorityQueueIsEmpty(q));
	PriorityQueueEnqueue(q, (void*)&num10);
	PriorityQueueEnqueue(q, (void*)&num10);
	result = PriorityQueueErase(q, IsMatchInt, (void*)&num1);
	assert(q == result);
	/*assert((size_t)1 == PriorityQueueSize(q));*/
	printf("\nTEST Erase SUCCESS\n");
	PriorityQueueDestroy(q);
}
void testClear()
{
	int num1 = 1;
	int num10 = 10;
	int num20 = 20;
	
	priority_queue_t *q = PriorityQueueCreate(CompareInts);
	PriorityQueueEnqueue(q, (void*)&num10);
	assert(0 == PriorityQueueIsEmpty(q));
	
	PriorityQueueClear(q);
	
	assert(1 == PriorityQueueIsEmpty(q));
	
	printf("\nTEST Clear SUCCESS\n");
	PriorityQueueDestroy(q);
}
 














