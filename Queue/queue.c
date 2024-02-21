
#include <stdlib.h> /*malloc*/
#include <assert.h> /*assert*/
#include "queue.h"   /*Personal Use*/
#include "sll.h"   /*Personal Use*/

struct queue
{
	sll_t *sll;
};

queue_t *QueueCreate()
{
	queue_t *q = (queue_t*)malloc(sizeof(queue_t));
	
	if (NULL == q)
	{
		return NULL;
	}
	q->sll =  SLLCreate();
	
	if(NULL == q->sll)
	{
		free(q);
		return NULL;
	}
	
	return q;
}
void QueueDestroy(queue_t *queue)
{	
	SLLDestroy(queue->sll);
	free(queue);
}

int QueueEnqueue(queue_t *queue, void *data)
{
	return !SLLInsert(SLLEnd(queue->sll), data); 
}

void QueueDequeue(queue_t *queue)
{
	SLLRemove(SLLBegin(queue->sll));
}

void *QueuePeek(const queue_t *queue)
{
	return SLLGetData(SLLBegin(queue->sll));
}

int QueueIsEmpty(const queue_t *queue)
{
	return SLLIsEmpty(queue->sll);
}

size_t QueueSize(const queue_t *queue)
{
	return SLLCount(queue->sll);
}

void QueueAppend(queue_t *dest, queue_t *source)
{
	SLLAppend(dest->sll, source->sll);
}







