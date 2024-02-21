#include <stdlib.h> /*malloc , free*/

#include <stdio.h> /*printf*/

#include "heap.h"


#define CAPACITY 10

static void HeapifyDown(heap_t *heap, size_t index);
static void HeapifyUp(heap_t *heap, size_t index);
static void Swap(heap_t *heap, size_t index1, size_t index2);
void Print(heap_t *heap);

struct heap
{
	heap_compare_func_t cmp;
	vector_t *array;
};

/* Time Complexity: O(1)*/
heap_t *HeapCreate(heap_compare_func_t cmp)
{
	heap_t *heap = (heap_t*)malloc(sizeof(heap_t));
	if(!heap)
	{
		return NULL;
	}
	heap->array = DVectorCreate(CAPACITY);
	if(!heap->array)
	{
		free(heap);
		return NULL;
	}
	heap->cmp = cmp;
	
	return heap;
}
/*****************************************************************************/
/* Time Complexity: O(1)*/
void HeapDestroy(heap_t *heap)
{
	DVectorDestroy(heap->array);
	free(heap);
}
/*****************************************************************************/
/* Time Complexity: O(log n)*/
int HeapPush(heap_t *heap, void *data)
{
	int status = 0;
	if(HeapIsEmpty(heap))
	{
		status = DVectorPushBack(heap->array, data);
		return status;
	}
	
	status = DVectorPushBack(heap->array, data);
	if(status)
	{
		return status;
	}
	HeapifyUp(heap, HeapSize(heap)-1);
	return status;
}
/*****************************************************************************/
/* Time Complexity: O(log n)*/
void *HeapPop(heap_t *heap)
{
	size_t index = 0;
	void *last_element = NULL;
	void *root = NULL;
	if(HeapIsEmpty(heap))
	{
		return NULL;
	}
	root = DVectorGetElement(heap->array, 0);
	index = HeapSize(heap) - 1;
	last_element = DVectorGetElement(heap->array, index);
	DVectorSetElement(heap->array, 0, last_element);
	DVectorSafePop(heap->array);//pop last elem in vector
	
	HeapifyDown(heap, 0);
	return (root);
}
/*****************************************************************************/
/* Time Complexity: O(1)*/
void *HeapPeek(const heap_t *heap)
{
	return(DVectorGetElement(heap->array, 0));
}
/*****************************************************************************/
/* Time Complexity: O(1)*/
size_t HeapSize(const heap_t *heap)
{
	return (DVectorSize(heap->array));
}
/*****************************************************************************/
/* Time Complexity: O(1)*/
int HeapIsEmpty(const heap_t *heap)
{
	return(DVectorIsEmpty(heap->array));
}

/*****************************************************************************/
/* Time Complexity: O(n)*/
void *HeapRemove(heap_t *heap, const void *data, heap_ismatch_func_t ismatch)
{
	size_t i = 0;
	void *result = NULL;
	void *current = NULL;
	void *parent = NULL;
	void *left_child = NULL;
	void *right_child = NULL;
	while(i < HeapSize(heap) && !ismatch(data, DVectorGetElement(heap->array, i)))
	{
		i++;
	}
	
	if(i < HeapSize(heap))
	{
		Swap(heap, i, HeapSize(heap) - 1);
		result = DVectorGetElement(heap->array, HeapSize(heap) - 1);
		DVectorSafePop(heap->array);
		
		
		if(i == HeapSize(heap))
		{
			return result;
		}
		
		if(((i * 2) + 1) >= HeapSize(heap))            /*leaf*/
		{
			HeapifyUp(heap, i);
			return (result);
		}
		
		if(i == 0)                                    /*root*/
		{
			HeapifyDown(heap, i);
			return (result);
		}
		current = DVectorGetElement(heap->array, i);
		parent = DVectorGetElement(heap->array, (i - 1)/2);
		left_child = DVectorGetElement(heap->array, (i*2) + 1);
		right_child = DVectorGetElement(heap->array, (i*2) + 2);
		
		if((heap->cmp(current, parent) <= 0))
		{
			HeapifyUp(heap, i);
			return (result);
		}
		
		if((heap->cmp(current, left_child) >= 0) || (heap->cmp(current, right_child) >= 0))
		{
			HeapifyDown(heap, i);
			return (result);
		}
	}
	return result;
}

/*****************************************************************************/
static void HeapifyDown(heap_t *heap, size_t index)
{
	void *root = NULL;
	void *left_child = NULL;
	void *right_child = NULL;
	
	if(((index * 2) + 1) >= HeapSize(heap))/*left child*/
	{
		return;
	}
	root = DVectorGetElement(heap->array, index);
	left_child = DVectorGetElement(heap->array, (2 * index) + 1);
	
	if((((index * 2) + 1) < HeapSize(heap)) && (((index * 2) + 2) < HeapSize(heap))) 
	{
		right_child = DVectorGetElement(heap->array, (2 * index) + 2);
		if((heap->cmp(root, left_child) >= 0) || (heap->cmp(root, right_child) >= 0))
		{
			if(heap->cmp(left_child, right_child) <= 0)
			{
				Swap(heap, index, (2 * index) + 1);
				HeapifyDown(heap, (2 * index) + 1);
			}
			else
			{
				Swap(heap, index, (2 * index) + 2);
				HeapifyDown(heap, (2 * index) + 2);
			}
		}
	}
	else if(((index * 2) + 1) < HeapSize(heap))
	{
		if((heap->cmp(root, left_child) >= 0))
		{
			Swap(heap, index, (2 * index) + 1);
			HeapifyDown(heap, (2 * index) + 1);
		}
	}
	
}
/*****************************************************************************/

static void HeapifyUp(heap_t *heap, size_t index)
{
	void *root = DVectorGetElement(heap->array, ((index - 1) / 2));
	void *child = DVectorGetElement(heap->array, index);
	if((index == 0) || ((heap->cmp(root, child) <= 0)))
	{
		return;
	}
	
	Swap(heap,((index - 1) / 2), index);
	HeapifyUp(heap, (index - 1) / 2);
}
/*****************************************************************************/
static void Swap(heap_t *heap, size_t index1, size_t index2)
{
	void *temp1 = DVectorGetElement(heap->array, index1);
	void *temp2 = DVectorGetElement(heap->array, index2);
	DVectorSetElement(heap->array, index1, temp2);
	DVectorSetElement(heap->array, index2, temp1);
	
}
/*****************************************************************************/

void Print(heap_t *heap)
{
	size_t i = 0;
	while(i < HeapSize(heap))
	{
		printf("%ld\n", (long int)DVectorGetElement(heap->array, i));
		i++;
	}
	printf("\n------------------------\n");
}
/* add ismatch*/





































