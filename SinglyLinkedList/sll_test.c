#include "sll.h"
#include <stdio.h>

void testAppend2FullLists();
void testEmptyAndFullList();
void testRemove();



int main()
{

	/*testRemove();*/
	testEmptyAndFullList();
	/*testAppend2FullLists();*/
	
	
return 0;
}
void testRemove()
{

	int b = 7;
	sll_iter_t iterator = NULL;
	sll_t *list1 = SLLCreate();
	
	sll_iter_t begin1 = SLLBegin(list1);
	
	iterator = SLLInsert(begin1, (void *)&b);

	printf("iterator %p \n, begin1 %p \n", (void*)iterator, (void*)begin1);
	printf("list1 size %lu \n", SLLCount(list1));
	printf("iterator : %d \n", *(int*)SLLGetData(iterator));
	SLLRemove(iterator);
	printf("list1 size %lu \n", SLLCount(list1));
	SLLDestroy(list1);

}
void testEmptyAndFullList()
{
	int a = 6;
	int b = 7;
	sll_iter_t iterator;
	sll_t *list1 = SLLCreate();
	sll_t *list2 = SLLCreate();

	sll_iter_t begin1 = SLLBegin(list1);
	sll_iter_t begin2 = SLLBegin(list2);
	/* insert  3 elements in list2*/
	
	SLLInsert(begin2, (void *)&b);
	SLLInsert(begin2, (void *)&b);
	SLLInsert(begin2, (void *)&a);
	/* size after insertion*/
	printf("list1 size %lu \n", SLLCount(list1));
	printf("list2 size %lu \n", SLLCount(list2));
	
	SLLAppend(list1, list2);
	/* insert after append */
	iterator = SLLInsert(begin1, (void *)&b);
	printf("list1 size %lu \n", SLLCount(list1));
	printf("list2 size %lu \n", SLLCount(list2));
	/* insert again after append */
	SLLInsert(iterator, (void *)&b);
	printf("list1 size %lu \n", SLLCount(list1));
	printf("list2 size %lu \n", SLLCount(list2));
	/* remove from list1 after append */
	SLLRemove(iterator);
	SLLRemove(iterator);
	printf("list1 size %lu \n", SLLCount(list1));
	printf("list2 size %lu \n", SLLCount(list2));
	/* insert into list 2 */
	SLLInsert(begin2, (void *)&b);

	printf("list1 size %lu \n", SLLCount(list1));
	printf("list2 size %lu \n", SLLCount(list2));
	/* remove from list2 */
	SLLRemove(begin2);
	printf("list1 size %lu \n", SLLCount(list1));
	printf("list2 size %lu \n", SLLCount(list2));	
	
	SLLDestroy(list1);
	SLLDestroy(list2);
}
void testAppend2FullLists()
{

	int a = 6;
	int b = 7;
	
	sll_t *list1 = SLLCreate();
	sll_t *list2 = SLLCreate();
	sll_iter_t begin1 = SLLBegin(list1);
	sll_iter_t begin2 = SLLBegin(list2);
	/* insert 2 in list1 and 3 elements in list2*/
	SLLInsert(begin1, (void *)&a);
	SLLInsert(begin1, (void *)&a);
	SLLInsert(begin2, (void *)&b);
	SLLInsert(begin2, (void *)&b);
	SLLInsert(begin2, (void *)&a);
	/* size after insertion*/
	printf("list1 size %lu \n", SLLCount(list1));
	printf("list2 size %lu \n", SLLCount(list2));
	
	SLLAppend(list1, list2);
	
	printf("list1 size %lu \n", SLLCount(list1));
	printf("list2 size %lu \n", SLLCount(list2));
	
	/*insert inside list1 and print the size*/
	SLLInsert(begin1, (void *)&a);
	printf("list1 size after inserting: %lu \n", SLLCount(list1));
	
	SLLInsert(begin2, (void *)&a);
	printf("list2 size after inserting: %lu \n", SLLCount(list2));
	printf(" begin2 : %d ", *(int*)SLLGetData(begin2));
	SLLInsert(begin2, (void *)&a);
	SLLRemove(begin2);
	printf("list2 size after removing: %lu \n", SLLCount(list2));
	/*
	output: list1 size 2 
		list2 size 3 
		list1 size 5 
		list2 size 0 
		list1 size after inserting: 6
		list2 size after inserting: 1 
	*/
	/*destroy both */
	SLLDestroy(list1);
	SLLDestroy(list2);
}
/* for testing */


/*  for testing
int SLLCompareInt(void* data, void* param)
{
	return !(*(int*)data == *(int*)param);
	
}

int Action( void *a, void *b)
{
	return *(int *)a += *(int*)&b;
}
*/














