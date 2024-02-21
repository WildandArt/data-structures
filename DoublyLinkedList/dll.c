#include "../include/dll.h"

/*

Reviewer: Yotam
Author:	Art
date: 17 march
*/

#include <stdlib.h>	/*malloc*/
#include <stdio.h>  	/* printf */
#include <assert.h> 	/* assert */

struct dll_node
{
	void* data;
	struct dll_node* next;
	struct dll_node* prev;
};

typedef struct dll_node node_t;
/**********************************************************/
int DLLActCount(void* data, void* param);

struct dll
{
	node_t *head;
	node_t *tail;
};

/**********************************************************/

dll_t *DLLCreate(void)
{
    dll_t *dll = (dll_t*)malloc(sizeof(dll_t));
    if(NULL == dll)
        return NULL;
    
    dll->head = (node_t*)malloc(sizeof(node_t));
    if(NULL == dll->head )
    {
        free(dll);
        return NULL;
    }

    dll->tail = dll->head;
    (dll->tail)->next = NULL;
    (dll->tail)->prev = NULL;
    (dll->tail)->data = dll;

    return dll;
}
/**********************************************************/
void DLLDestroy(dll_t *list)
{
	dll_iter_t tmp;
	dll_iter_t begin = list->head;
	while(begin)
	{
		tmp = begin->next;
		free(begin);
		begin = tmp;
	}
	free(list);
	list = NULL;
}
/**********************************************************/
void DLLSplice(dll_iter_t dest, dll_iter_t source_from, dll_iter_t source_to)
{
	dll_iter_t tmp_next = source_to -> next;

	/* data */
	void *temp = NULL;

	temp = source_from->data;
	source_from->data = source_to->data;
	source_to->data = dest->data;
	dest->data = temp;
	/*connections */
	source_from -> next -> prev = dest;
	source_to -> next = dest -> next; /*could be NULL*/
	
	if(dest -> next)/* if next not null, if dest not dummy*/
	{
		dest -> next -> prev = source_to;
	}
	else/*if dest is dummy*/
	{
		((dll_t *)source_to -> data) ->tail = source_to;
	}
	
	dest -> next = source_from -> next;
	source_from -> next = tmp_next; /* tmp = to-> next ;could be NULL*/   
	
	if(!source_from -> next)/* if null, if from is dummy*/
	{
		((dll_t *)source_from -> data) ->tail = source_from;
	}
	
	else/* if from is not dummy*/
	{
		source_from -> next -> prev = source_from;
	}
}

/**********************************************************/
int DLLMultiFind(const dll_iter_t from, const dll_iter_t to, \
dll_cmp_func_t cmp, void *param, dll_t *dest)
{
	int counter = 0;
	dll_iter_t tmp_from = from;
	dll_iter_t iter = NULL;
	
	while(tmp_from != to)
	{
		if(0 == cmp(tmp_from->data, param))
		{
			iter = DLLPushBack(dest, tmp_from);
			if(dest->tail == iter)
			{
				return -1;
			}
			counter++;
		}
		tmp_from = tmp_from->next;
	}
	return counter;
}
/**********************************************************/
dll_iter_t DLLInsertAfter(dll_iter_t iterator, void *data)
{
	
	  node_t *node = (node_t*)malloc(sizeof(node_t));

	  if(NULL == node)
	  {
		while(NULL != iterator->next)
			iterator = iterator->next;
		return iterator;
	  }
	  node->data = data;
	  node->next = iterator->next;
	  node->prev = iterator;
	  
	  iterator->next->prev = node;
	  iterator->next = node;
	  
	  return node;
}
/**********************************************************/
dll_iter_t DLLPushBack(dll_t *dll, void *data)
{
	dll_iter_t end;
	assert(dll);
	assert(data);
	end = DLLEnd(dll);
	
	return DLLInsertBefore(end, data);
}
/**********************************************************/
void *DLLPopBack(dll_t *dll)
{
	
	void *data = dll->tail->prev->data; 
	assert(dll);                                             
	DLLRemove(dll->tail->prev);
	
	
	return data;
}
/**********************************************************/
dll_iter_t DLLInsertBefore(dll_iter_t iterator, void *data)
{
	node_t *node = (node_t*)malloc(sizeof(node_t));
	void* tmp;
	if(NULL == node)
	{
		while(NULL != iterator->next)
			iterator = iterator->next;
		return iterator;
	}
	tmp = iterator->data;
	iterator->data = data;
	node->data = tmp;
	
	node->next = iterator->next;/*1*/
	
	iterator->next = node;/*2*/
	node->prev = iterator;/*4*/
	
	if(NULL == node->next)
	{
		((dll_t *)(node->data))->tail = node;
	}
	else
	{
		node->next->prev = node;
	}
    	return iterator;
}
/**********************************************************/
dll_iter_t DLLRemove(dll_iter_t iterator)
{
	node_t *node_to_free = iterator->next;
	iterator->data = iterator->next->data;

	if(NULL != iterator->next->next)
	{
		iterator->next->next->prev = iterator;
	}
	
	iterator->next = iterator->next->next;
	
	if(NULL == iterator->next)
	{
		((dll_t*)(iterator->data))->tail = iterator;
	}
	free(node_to_free);
	node_to_free = NULL;
	return iterator->next;
	
}
/**********************************************************/
void *DLLPopFront(dll_t *dll)
{
	/* pop front to empty list undefined*/
	void *data = dll->head->data;
	dll->head = dll->head->next;
	free(dll->head->prev);
	dll->head->prev = NULL;
	return data;
}
/**********************************************************/
dll_iter_t DLLPushFront(dll_t *dll, void *data)
{
	dll_iter_t end = DLLEnd(dll);
	node_t *node = (node_t*)malloc(sizeof(node_t));
	if(NULL == node)
	{
		return end;
	}
	
	node->data = data;
	node->prev = NULL;
	node->next = dll->head;
	
	dll->head->prev = node;
	dll->head = node;
	return dll->head;
}
/**********************************************************/
dll_iter_t DLLEnd(const dll_t *dll)
{
	return dll->tail; 
}
/**********************************************************/
dll_iter_t DLLBegin(const dll_t *dll)
{
	return dll->head; 
}

/**********************************************************/
dll_iter_t DLLNext(dll_iter_t iterator)
{
	assert(iterator);
	return iterator->next;
}
 
/**********************************************************/
dll_iter_t DLLPrev(const dll_iter_t iterator)
{
	assert(iterator);
	return iterator->prev;
}
/**********************************************************/
int DLLIsEmpty(const dll_t *dll)
{
	assert(dll);
	return (dll->head) == (dll->tail);

}
/**********************************************************/
int DLLIterIsEqual(const dll_iter_t iter1, const dll_iter_t iter2)
{
	return iter1 == iter2;
}
/**********************************************************/
void* DLLGetData(dll_iter_t position)
{
	return position->data;
}
/**********************************************************/
void DLLSetData(dll_iter_t iterator, void *data)
{
	iterator->data = data;
}
/**********************************************************/
int DLLForEach(dll_iter_t from, const dll_iter_t to,\
 dll_act_func_t act, void *param)
{
	int status = 0;
	
	while(from != to)
	{
		status = act(from->data, param);
		if(status)
		{
			return status;
		}
		
		from = from->next;
	}
	return 0;
}
/**********************************************************/
dll_iter_t DLLFind(dll_iter_t from, dll_iter_t to, \
dll_cmp_func_t cmp,
 void *param)
 {
 	size_t result = 0;
 	
	 while(from != to)
	 {
	 	result = cmp(from->data, param);
	 	if(0 == result)
	 	{
	 		return from;
	 	}
	 	from = from->next;
	 }
	
	return to;
 }
/**********************************************************/

size_t DLLCount(const dll_t *dll)
{
	size_t count_var = 0;
	
	dll_iter_t from = DLLBegin(dll);
	dll_iter_t to = DLLEnd(dll);
	dll_act_func_t counter = DLLActCount;
	DLLForEach(from, to, counter, &count_var);
	return count_var;
}


/**********************************************************/
int DLLActCount(void* data, void* param)
{
	data = (void*)(data);
	(*(int *)param) += 1;
	return 0;
}
/**********************************************************/





