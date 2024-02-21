
#include <assert.h> /*assert*/
#include <stddef.h> /*size_t */
#include<stdlib.h>  /*malloc, free*/
#include"sorted_list.h"
#include"priority_queue.h"
/*****************************************************************************/



struct priority_queue{

	sorted_list_t *list;

};


/*****************************************************************************/

/* Complexity - time Complexity O(1), space complexity O(1).
   Creation of a Queue, if cfreation fails it will return NULL */

priority_queue_t *PriorityQueueCreate(priority_queue_compare_func_t compare)
{
	
	priority_queue_t *q = (priority_queue_t*) malloc(sizeof(priority_queue_t));
	if(NULL == q)
	{
		return NULL;
	}
	q->list = SortedListCreate(compare);
	if(NULL == q->list)
	{
		free(q->list);
		q->list = NULL;
		return NULL;
	}

	return q;
}

/*****************************************************************************/

/* Complexity - time Complexity O(n), space complexity O(1).
   Destroy of the Queue. */

void PriorityQueueDestroy(priority_queue_t *queue)
{	
	assert(queue);
	SortedListDestroy(queue->list);
	free(queue);
	queue = NULL;
}

/*****************************************************************************/

/* Complexity - time Complexity O(n), space complexity O(1).
   Adds element to the back of queue. return 0 on success. */

int PriorityQueueEnqueue(priority_queue_t *queue, void *data)
{
	sorted_list_iter_t result;
	assert(queue);
	result = SortedListInsert(queue->list, data);
		
	return SortedListIsEqual(SortedListEnd(queue->list), result);
}

/*****************************************************************************/

/* Complexity - time Complexity O(1), space complexity O(1).
   Removes element from head of queue */

void *PriorityQueueDequeue(priority_queue_t *queue)
{
	assert(queue);
	return SortedListPopBack(queue->list);
}

/*****************************************************************************/

/* Complexity - time Complexity O(1), space complexity O(1).
   Return the data from the head of queue */

void *PriorityQueuePeek(const priority_queue_t *queue)
{
	assert(queue);
	return SortedListGetData(SortedListPrev(SortedListEnd(queue->list)));
}

/*****************************************************************************/

/* Complexity - time Complexity O(1), space complexity O(1).
   Return 1 if empty and 0 if not */

int PriorityQueueIsEmpty(const priority_queue_t *queue)
{
	assert(queue);
	return SortedListIsEmpty(queue->list);

}

/*****************************************************************************/

/* Complexity - time Complexity O(n), space complexity O(1).
   Returns the size of queue */

size_t PriorityQueueSize(const priority_queue_t *queue)
{
	assert(queue);
	return SortedListCount(queue->list);
}

/*****************************************************************************/

/* Complexity - time Complexity O(n), space complexity O(1).
   Returns the data of removed element */
   
void *PriorityQueueErase(priority_queue_t *queue, \
priority_queue_ismatch_func_t ismatch, void *parameter)
{
	sorted_list_iter_t from; 
	sorted_list_iter_t to; 
	sorted_list_iter_t found;
	void *returned = NULL;
	
	assert(queue);
	
	from = SortedListBegin(queue->list);
	to = SortedListEnd(queue->list);
	
	found = SortedListFindIf(from, to, ismatch, parameter);
	
	if(SortedListIsEqual(SortedListEnd(queue->list), found))
	{
		return queue;
	}
	returned = SortedListGetData(found);
	SortedListRemove(found);
	
	return returned;
}

/*****************************************************************************/

/* Complexity - time Complexity O(n), space complexity O(1).
   Returns empty queue */
   
void PriorityQueueClear(priority_queue_t *queue)
{
	assert(queue);
	while(!SortedListIsEmpty(queue->list))
	{
		SortedListPopFront(queue->list);
	}
}

/*****************************************************************************/


