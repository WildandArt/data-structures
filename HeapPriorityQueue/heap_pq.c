#include <stdlib.h> /*malloc , free*/

#include "heap.h"
#include "heap_pq.h"


struct heap_pq 
{
	heap_t *heap;
};

/*****************************************************************************/
heap_pq_t *HeapPQCreate(heap_pq_compare_func_t compare)
{
	heap_pq_t *heap_pq = (heap_pq_t*)malloc(sizeof(heap_pq_t));
	if(!heap_pq)
	{
		return NULL;
	}
	heap_pq->heap = HeapCreate((heap_compare_func_t)compare);
	if(!heap_pq->heap)
	{
		free(heap_pq);
		return NULL;
	}
	
	return heap_pq;
}
/*****************************************************************************/
void HeapPQDestroy(heap_pq_t *queue)
{
	HeapDestroy(queue->heap);
	free(queue);
}

/*****************************************************************************/
int HeapPQEnqueue(heap_pq_t *queue, void *data)
{
	return(HeapPush(queue->heap, data));
}

/*****************************************************************************/
void *HeapPQDequeue(heap_pq_t *queue)
{
	return(HeapPop(queue->heap));
}

/*****************************************************************************/
void *HeapPQPeek(const heap_pq_t *queue)
{
	return(HeapPeek(queue->heap));
}

/*****************************************************************************/
int HeapPQIsEmpty(const heap_pq_t *queue)
{
	return(HeapIsEmpty(queue->heap));
}

/*****************************************************************************/
size_t HeapPQSize(const heap_pq_t *queue)
{
	return(HeapSize(queue->heap)); 
}

/*****************************************************************************/
void *HeapPQErase(heap_pq_t *queue, heap_pq_ismatch_func_t ismatch, void *parameter)
{
	void *result = NULL;
	result = HeapRemove(queue->heap, parameter, (heap_ismatch_func_t)ismatch);
	if(!result)
	{
		return((void *)queue);
	}
	return(result);
}

/*****************************************************************************/
void HeapPQClear(heap_pq_t *queue)
{
	while(!HeapIsEmpty(queue->heap))
	{
		HeapPop(queue->heap);
	}
}

/*****************************************************************************/
