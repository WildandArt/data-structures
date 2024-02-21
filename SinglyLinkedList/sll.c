#include "sll.h"

/*

Reviewer: Maya
Author:	Art
date: 8 march
*/

#include <stdlib.h>	/*malloc*/
#include <stdio.h>  	/* printf */
#include <assert.h> 	/* assert */

int SLLActEmpty(void* data, void* param);
/*
typedef struct sll_node *sll_iter_t;
typedef struct list sll_t;
*/
struct sll_node
{
	void* data;
	struct sll_node* next;
};

typedef struct sll_node node_t;

struct list
{
	node_t *head;
	node_t *tail;
};

/**********************************************************/

sll_t *SLLCreate(void)
{
    sll_t *sll = (sll_t*)malloc(sizeof(sll_t));
    if(NULL == sll)
    {
        printf("SLLCreate failed.\n");
        return NULL;
    }
    sll->head = (node_t*)malloc(sizeof(node_t));
    if(NULL == sll->head )
    {
        free(sll);
        printf("SLLCreate failed.\n");
        return NULL;

    }

    sll->tail = sll->head;
    (sll->tail)->next = NULL;
    (sll->tail)->data = sll;

    return sll;

}
/**********************************************************/
void SLLDestroy(sll_t *list)
{
	
	sll_iter_t tmp;
	sll_iter_t begin = list->head;
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
sll_iter_t SLLEnd(const sll_t *sll)
{
	assert(sll);
	return sll->tail; 
}
/**********************************************************/
sll_iter_t SLLBegin(const sll_t *sll)
{
	assert(sll);
	return sll->head; 
}

/**********************************************************/
sll_iter_t SLLNext(sll_iter_t iterator)
{
	assert(iterator);
	return iterator->next;/* may be casting to iter*/
}

/**********************************************************/
size_t SLLCount(const sll_t *sll)
{
	int count_var = 0;
	
	sll_iter_t from = sll->head;
	sll_iter_t to = sll->tail;
	
	sll_action_func_t counter = SLLActEmpty;
	
	assert(sll);
	
	SLLForEach(from, to, counter, &count_var);
		
	return count_var;
}

/**********************************************************/
int SLLIsEmpty(const sll_t *sll)
{
	assert(sll);
	return (sll->head) == (sll->tail);

}
/**********************************************************/
int SLLIterIsEqual(sll_iter_t iter1, sll_iter_t iter2)
{
	assert(iter1 && iter2);
	return iter1 == iter2;
}
/**********************************************************/
void* SLLGetData(sll_iter_t position)
{
	assert(position);
	return position->data;
}
/**********************************************************/
void SLLSetData(sll_iter_t iterator, void *data)
{
	assert(iterator);
	iterator->data = data;
}
/**********************************************************/
sll_iter_t SLLInsert(sll_iter_t iterator, void *data)
{
	node_t *node = (node_t*)malloc(sizeof(node_t));
	void* tmp;
	if(NULL == node)
	{
		printf("failed.\n");
		return NULL;
	}
	tmp = iterator->data;
	iterator->data = data;
	node->data = tmp;
	/*end of swap*/
	node->next = iterator->next;
	iterator->next = node;
	if(NULL == node->next)/* if iterator is Dummy*/
	{
		((sll_t *)(node->data))->tail = node;/* node is now dummy-tail of this list*/
	}
    	return iterator;
 }
 /**********************************************************/
 void SLLRemove(sll_iter_t iterator)
 {
 	sll_iter_t tmp;

 	iterator->data = (iterator->next)->data;
 	tmp = iterator->next; /*next element will be freed later */
 	/*point to the next after next element*/
 	iterator->next = (iterator->next)->next;
 	
 	free(tmp);
 	tmp = NULL;
 	
 	if((iterator->next) == NULL)/*if this is dummy*/
 	{
 		((sll_t *)(iterator->data))->tail = iterator;
 	}
 }


/**********************************************************/
int SLLForEach(sll_iter_t from, sll_iter_t to, \
sll_action_func_t action, void *param)
{
	size_t status = 0;
	
	while(from != to)
	{
		status = action(from->data, param);
		if(status)
		{
			return 1;
		}
		
		from = from->next;
	}
	return 0;
}
/**********************************************************/
void SLLAppend(sll_t *dest, sll_t *source)
{

	/* copy data from  head of source to tail of dest*/
	(dest->tail)->data = (source->head)->data;
	/* dest tail now points to source->head->next*/
	(dest->tail)->next = (source->head)->next;
	/* dest tail now points to source tail*/
	(dest->tail) = source->tail;
	dest->tail->data = dest;
	/* connecting the dummy to source*/
	source->tail = source->head;
	source->tail->data = source;
	source->tail->next = NULL;
}
/**********************************************************/

sll_iter_t SLLFind(sll_iter_t from, sll_iter_t to, \
sll_compare_func_t cmp,
 void *parameter)
 {
 	size_t result = 0;
 	
	 while(from != to)
	 {
	 	result = cmp(from->data, parameter);
	 	if(0 == result)
	 	{
	 		return from;
	 	}
	 	from = from->next;
	 }
	
	return to;
 }

/**********************************************************/


int SLLActEmpty(void* data, void* param)
{
	data = (void*)(data);
	(*(int *)param) += 1;
	return 0;
}














