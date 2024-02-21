
#include <stdio.h> /*printf*/
#include <assert.h> /*assert*/

#include "heap_pq.h" /* header file with functions declarations */
//#include "sorted_list.h" /* header file with functions declarations */

void TestCreateAndDestroy(void);
void TestEnqueue(void);
void TestDequeue(void);
void TestPeek(void);
void TestIsEmpty(void);
void TestSize(void);
void TestErase(void);
void TestClear(void);

int HeapPQCompareFunc(void *data, void *new_data)
{
	return *(int*)new_data - *(int*)data;
}

int HeapPQIsMatchParameter(void *parameter, void *new_data)
{
	return *(int*)parameter == *(int*)new_data;
}

int main()
{
	TestCreateAndDestroy();
	/*TestEnqueue();*/
	/*TestDequeue();
	TestPeek();*/
	/*TestIsEmpty();
	TestSize();*/
	TestErase();
	/*TestClear();*/
	
	return 0;
}

void TestCreateAndDestroy(void)
{
	heap_pq_t *queue = HeapPQCreate(HeapPQCompareFunc);
	assert(queue);
	HeapPQDestroy(queue);
}

void TestEnqueue(void)
{
	heap_pq_t *queue = HeapPQCreate(HeapPQCompareFunc);
	
	int data = 6;
	int data2 = 8;
	int data3 = 4;
	int data4 = 7;
	int result = -1;
	
	result = HeapPQEnqueue(queue, &data);
	assert(!result);
	result = HeapPQEnqueue(queue, &data2);
	assert(!result);
	result = HeapPQEnqueue(queue, &data3);
	assert(!result);
	result = HeapPQEnqueue(queue, &data4);
	assert(!result);
	
	HeapPQDestroy(queue);
}

void TestDequeue(void)
{
	void *result_dequeue = NULL;
	heap_pq_t *queue = HeapPQCreate(HeapPQCompareFunc);
	
	int data = 6;
	int data2 = 8;
	int data3 = 0;
	int data4 = 7;
	size_t count = 0;
	
	HeapPQEnqueue(queue, &data);
	HeapPQEnqueue(queue, &data2);
	HeapPQEnqueue(queue, &data3);
	HeapPQEnqueue(queue, &data4);
	
	result_dequeue = HeapPQDequeue(queue);
	assert(result_dequeue);
	count = HeapPQSize(queue);
	assert(3 == count);
	
	HeapPQDestroy(queue);
}

void TestPeek(void)
{
	heap_pq_t *queue = HeapPQCreate(HeapPQCompareFunc);
	int data = 6;
	int data2 = -8;
	int data3 = 0;
	int data4 = 7;
	void *result_of_peek = NULL;
	
	HeapPQEnqueue(queue, &data);
	HeapPQEnqueue(queue, &data2);
	HeapPQEnqueue(queue, &data3);
	HeapPQEnqueue(queue, &data4);

	result_of_peek = HeapPQPeek(queue);
	assert(result_of_peek);
	/*printf("result_of_peek = %d", *(int*)result_of_peek);*/

	HeapPQDestroy(queue);
}

void TestIsEmpty(void)
{
	heap_pq_t *queue = HeapPQCreate(HeapPQCompareFunc);
	int data = 6;
	int data2 = -8;
	int data3 = 0;
	int data4 = 7;
	int is_empty = 0;
	
	HeapPQEnqueue(queue, &data);
	HeapPQEnqueue(queue, &data2);
	HeapPQEnqueue(queue, &data3);
	HeapPQEnqueue(queue, &data4);

	is_empty = HeapPQIsEmpty(queue);
	assert(!is_empty);
	
	HeapPQDequeue(queue);
	HeapPQDequeue(queue);
	HeapPQDequeue(queue);
	HeapPQDequeue(queue);

	is_empty = HeapPQIsEmpty(queue);
	assert(is_empty);

	HeapPQDestroy(queue);
}

void TestSize(void)
{
	heap_pq_t *queue = HeapPQCreate(HeapPQCompareFunc);
	int data = 6;
	int data2 = -8;
	int data3 = 0;
	int data4 = 7;
	size_t count;
	
	HeapPQEnqueue(queue, &data);
	HeapPQEnqueue(queue, &data2);
	HeapPQEnqueue(queue, &data3);
	HeapPQEnqueue(queue, &data4);

	count = HeapPQSize(queue);
	assert(4 == count);
	
	HeapPQDequeue(queue);
	HeapPQDequeue(queue);
	
	count = HeapPQSize(queue);
	assert(2 == count);
	
	HeapPQDequeue(queue);
	HeapPQDequeue(queue);

	count = HeapPQSize(queue);
	assert(0 == count);

	HeapPQDestroy(queue);
}

void TestErase(void)
{
	heap_pq_t *queue = HeapPQCreate(HeapPQCompareFunc);
	int data = 6;
	int data2 = -8;
	int data3 = 0;
	int data4 = 7;
	size_t count = 0;
	int parameter = -8; 
	void *result_of_erase = NULL;
	heap_pq_ismatch_func_t ismatch = HeapPQIsMatchParameter;
	
	HeapPQEnqueue(queue, &data);
	HeapPQEnqueue(queue, &data2);
	HeapPQEnqueue(queue, &data3);
	HeapPQEnqueue(queue, &data4);

	result_of_erase = HeapPQErase(queue, ismatch, &parameter);
	assert((void *)queue != result_of_erase);
	count = HeapPQSize(queue);
	assert(3 == count);
	
	parameter = 10;
	result_of_erase = HeapPQErase(queue, ismatch, &parameter);
	assert((void *)queue == result_of_erase);
	count = HeapPQSize(queue);
	assert(3 == count);

	HeapPQDestroy(queue);
}

void TestClear(void)
{
	heap_pq_t *queue = HeapPQCreate(HeapPQCompareFunc);
	int data = 6;
	int data2 = -8;
	int data3 = 0;
	int data4 = 7;
	size_t count = 0; 
	int is_empty = 0;
	
	HeapPQEnqueue(queue, &data);
	HeapPQEnqueue(queue, &data2);
	HeapPQEnqueue(queue, &data3);
	HeapPQEnqueue(queue, &data4);
	
	count = HeapPQSize(queue);
	assert(4 == count);
	
	HeapPQClear(queue);
	count = HeapPQSize(queue);
	assert(0 == count);
	
	is_empty = HeapPQIsEmpty(queue);
	assert(is_empty);

	HeapPQDestroy(queue);
}





