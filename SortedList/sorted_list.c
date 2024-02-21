/*
reviewer : Ishai
author : Art
22 march
*/
/******************************************************************************/
#include <stdio.h>  /* puts */
#include <stdlib.h> /* malloc, free */
#include <stddef.h> /* size_t, ssize_t */
#include <assert.h> /* assert */

#include "../include/sorted_list.h"    /* Internal use */
#include "../include/dll.h"    /* Internal use */

/******************************************************************************/
struct sorted_list
{
	dll_t *list;
	sorted_list_compare_func_t cmp;
};
/******************************************************************************/


sorted_list_t *SortedListCreate(sorted_list_compare_func_t compare)
{
	sorted_list_t *sorted_list =  (sorted_list_t*)malloc(sizeof(sorted_list_t));
	
	if(NULL == sorted_list)
		return NULL;

	sorted_list->cmp = compare;
	sorted_list->list = DLLCreate();

	if(NULL == sorted_list->list)
		return NULL;
	
	return sorted_list;
}
/******************************************************************************/
void SortedListDestroy(sorted_list_t *sorted_list)
{
	assert(sorted_list);
	sorted_list->cmp = NULL;
	DLLDestroy(sorted_list->list);
	free(sorted_list);
}
/******************************************************************************/
size_t SortedListCount(const sorted_list_t *sorted_list)
{
	assert(sorted_list);
	return DLLCount(sorted_list->list);
}
/******************************************************************************/
sorted_list_iter_t SortedListBegin(const sorted_list_t *sorted_list)
{
	sorted_list_iter_t iterator;
	assert(sorted_list);
	iterator.iterator = DLLBegin(sorted_list->list);
	#ifndef NDEBUG
	 iterator.list = (sorted_list_t*)sorted_list;
	 #endif
	return iterator;
}
/******************************************************************************/

sorted_list_iter_t SortedListEnd(const sorted_list_t *sorted_list)
{
	sorted_list_iter_t iterator;
	assert(sorted_list);
	iterator.iterator = DLLEnd(sorted_list->list);
	#ifndef NDEBUG
	 iterator.list = (sorted_list_t*)sorted_list;
	 #endif
	return iterator;
}
/******************************************************************************/
sorted_list_iter_t SortedListNext(const sorted_list_iter_t iterator)
{
	 sorted_list_iter_t next;
	 next.iterator = DLLNext(iterator.iterator);
	 return next; 
}
/******************************************************************************/

sorted_list_iter_t SortedListPrev(const sorted_list_iter_t iterator)
{
	sorted_list_iter_t prev;
	prev.iterator = DLLPrev(iterator.iterator);
	return prev;
}
/******************************************************************************/

int SortedListIsEmpty(const sorted_list_t *sorted_list)
{
	return DLLIsEmpty(sorted_list->list);
}
/******************************************************************************/
int SortedListIsEqual(const sorted_list_iter_t iter1,\
 const sorted_list_iter_t iter2)
{
	return DLLIterIsEqual(iter1.iterator, iter2.iterator);
}
/******************************************************************************/
sorted_list_iter_t SortedListRemove(sorted_list_iter_t iterator)
{
	dll_iter_t removed = DLLRemove(iterator.iterator);
	iterator.iterator = removed;
	return iterator;
}
/******************************************************************************/

void *SortedListPopBack(sorted_list_t *list)
{
	assert(list);
	return DLLPopBack(list->list);
}
/******************************************************************************/

void *SortedListPopFront(sorted_list_t *list)
{
	assert(list);
	return DLLPopFront(list->list);
}
/******************************************************************************/
void *SortedListGetData(const sorted_list_iter_t iterator)
{
	return DLLGetData(iterator.iterator);
}
/******************************************************************************/
sorted_list_iter_t SortedListInsert(sorted_list_t *sorted_list, void *data)
{
	sorted_list_iter_t from = SortedListBegin(sorted_list);
	sorted_list_iter_t to = SortedListEnd(sorted_list);
	
	for(;!SortedListIsEqual(from,to); from = SortedListNext(from))
	{
		if((sorted_list->cmp(SortedListGetData(from), data)) >= 0)
		{
			from.iterator = DLLInsertBefore(from.iterator, data);
			return from;
		}
	}
	from.iterator = DLLInsertBefore(from.iterator, data);
	return from;

}
/******************************************************************************/
sorted_list_iter_t SortedListFind(const sorted_list_t *list,\
 const sorted_list_iter_t from, const sorted_list_iter_t to, void *parameter)
{
	sorted_list_iter_t find = {NULL};
	assert(list);
	find.iterator = DLLFind(\
	from.iterator, to.iterator,  list->cmp, parameter);
	#ifndef NDEBUG
	find.list = (sorted_list_t*)list;
	#endif
	return find;
	
}
/******************************************************************************/
sorted_list_iter_t SortedListFindIf(const sorted_list_iter_t from,\
 const sorted_list_iter_t to, sorted_list_ismatch_func_t match, void *parameter)
{
	sorted_list_iter_t from1 = from;
	sorted_list_iter_t to1 = to;
	
	for(;!SortedListIsEqual(from1,to1); from1 = SortedListNext(from1))
	{
		if(match(SortedListGetData(from1), parameter))
		{
			return from1;
		}
	}
	return to;
}
/******************************************************************************/
int SortedListForEach(sorted_list_iter_t from, const sorted_list_iter_t to,\
 sorted_list_action_func_t action, void *parameter)
{

	assert(from.list == to.list);
	
	return DLLForEach(from.iterator, to.iterator,\
 action, parameter);
	
}
/******************************************************************************/
void SortedListMerge(sorted_list_t *dest, sorted_list_t *source)
{

 
	sorted_list_iter_t begin_dest = SortedListBegin(dest);
	
	sorted_list_iter_t from_src = SortedListBegin(source);
	sorted_list_iter_t to = from_src;

	while(DLLBegin(source->list) != DLLEnd(source->list))
	{
		while(!SortedListIsEqual(begin_dest, SortedListEnd(dest)) && ((dest->cmp(SortedListGetData(begin_dest), \
			SortedListGetData(from_src))) < 0))
		{
				begin_dest = SortedListNext(begin_dest);
		}
			
		if(SortedListIsEqual(begin_dest, SortedListEnd(dest)))
		{
			to = SortedListEnd(source);
			DLLSplice(begin_dest.iterator,  from_src.iterator,\
					to.iterator);
		}
		else
		{
			to = from_src;
			while(!SortedListIsEqual(to, SortedListEnd(source)) && ((dest->cmp(SortedListGetData(begin_dest), \
				SortedListGetData(to))) >= 0))
			{
				to = SortedListNext(to);
			}
			
			DLLSplice(begin_dest.iterator,  from_src.iterator,\
						to.iterator);
			from_src = SortedListBegin(source);
			begin_dest = to;
			to = from_src;
		}
	}
}

	

/******************************************************************************/









