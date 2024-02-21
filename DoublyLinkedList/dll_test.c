#include "dll.h"

#include <stdio.h>

void testInsertBefore();
void testPopPushBack();
void testInsertAfter();
void testDLLPushFront();
void testPopFront();
void removeTest();
void testSplice();
void testPop();

int main()
{
	/*testPopPushBack();
	testInsertAfter();
	testDLLPushFront();
	testPopFront();*/
	/*removeTest();*/
	testSplice();
	/*testPopPushBack();*/
	/*testPop();*/
	return 0;
}

void testInsertBefore()
{
	/* defined insert before dummy, 
	and before first element, and empty list*/
	int a = 7;
	int b = 9;
	dll_t *list = DLLCreate();
	dll_iter_t end = DLLEnd(list);
	dll_iter_t begin = DLLBegin(list);
	
	dll_iter_t inserted = DLLInsertBefore(begin, (void*)&a);
	
	printf("inserted : %d \n", *(int*)DLLGetData(inserted));
	printf("list1 size %lu \n", DLLCount(list));
	
	inserted = DLLInsertBefore(end, (void*)&b);
	printf("inserted : %d \n", *(int*)DLLGetData(inserted));
	printf("list1 size %lu \n", DLLCount(list));
	
	DLLDestroy(list);
}

void testPop()
{
	int a = 1;
	int b = 2;
	void *vp;
	dll_t *list = DLLCreate();
	dll_iter_t pushedBack;
	printf("list1 size %lu \n", DLLCount(list));
	DLLPushBack(list, (void*)&a);
	pushedBack = DLLPushBack(list, (void*)&b);
	printf("inserted data from back: %d \n", *(int*)DLLGetData(pushedBack));
	printf("list1 size %lu \n", DLLCount(list));
	vp = DLLPopBack(list);
	printf("\npopped from back : %d \n", *(int*)vp);
	printf("list1 size %lu \n", DLLCount(list));
	DLLDestroy(list);
}
void testPopPushBack()
{
/*1. */
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	void *vp;
	dll_t *list = DLLCreate();
	dll_iter_t end = DLLEnd(list);
	dll_iter_t begin = DLLBegin(list);
	dll_iter_t pushedBack = DLLPushBack(list, (void*)&a);
	printf("inserted data from back: %d \n", *(int*)DLLGetData(pushedBack));
	 pushedBack = DLLPushBack(list, (void*)&b);
	 printf("inserted data from back: %d \n", *(int*)DLLGetData(pushedBack));
	 pushedBack = DLLPushBack(list, (void*)&c);
	 printf("inserted data from back: %d \n", *(int*)DLLGetData(pushedBack));
	 pushedBack = DLLPushBack(list, (void*)&d);
	 printf("inserted data from back: %d \n", *(int*)DLLGetData(pushedBack));
	 /* 1234 */
	printf("list1 size %lu \n", DLLCount(list));
	
	vp = DLLPopBack(list);
	printf("\npopped from back : %d \n", *(int*)vp);
	vp = DLLPopBack(list);
	printf("\npopped from back : %d \n", *(int*)vp);
	vp = DLLPopBack(list);
	printf("\npopped from back : %d \n", *(int*)vp);
	printf("list1 size %lu \n", DLLCount(list));

	DLLDestroy(list);
}

void testInsertAfter()
{
	/* check insert after dummy-undef, 
	after empty list-undef, after head defined
	 and  in the middle defined */
	int a = 7;
	int b = 9;
	void *vp;
	dll_t *list = DLLCreate();
	dll_iter_t end = DLLEnd(list);/*fail */
	dll_iter_t begin = DLLBegin(list);/* fail*/
	dll_iter_t inserted = DLLInsertBefore(begin, (void*)&a);
	dll_iter_t after = DLLInsertAfter(inserted, (void *)&a);
	printf("list size after insertion %lu \n", DLLCount(list));
	printf("inserted data: %d \n", *(int*)DLLGetData(after));
	DLLDestroy(list);
}

void testDLLPushFront()
{
	int a = 7;
	int b = 9;
	void *vp;
	dll_iter_t pushed_front;
	dll_t *list = DLLCreate();
	printf("list size before insertion %lu \n", DLLCount(list));
	pushed_front = DLLPushFront(list, (void*)&a);
	pushed_front = DLLPushFront(list, (void*)&b);
	printf("list size after insertion %lu \n", DLLCount(list));
	printf("inserted data from front: %d \n", *(int*)DLLGetData(pushed_front));
	DLLDestroy(list);
}
void testPopFront()
{

	int a = 7;
	int b = 9;
	void *vp;
	dll_iter_t popped_front;
	dll_t *list = DLLCreate();
	dll_iter_t pushed_front = DLLPushFront(list, (void*)&a);
	
	vp = DLLPopFront(list);
	printf("popped front %d", *(int*)vp);
	DLLDestroy(list);
}

void removeTest()
{
	int a = 7;
	int b = 8;
	dll_t *list = DLLCreate();
	dll_iter_t removed;
	dll_iter_t begin = DLLBegin(list);
	dll_iter_t end = DLLEnd(list);
	dll_iter_t inserted = DLLInsertBefore(begin, (void*)&a);
	inserted = DLLInsertBefore(begin, (void*)&a);
	/*inserted = DLLInsertBefore(begin, (void*)&a);*/
	printf("list size after insertion %lu \n", DLLCount(list));
	begin = DLLBegin(list);
	end = DLLEnd(list);
	removed = DLLRemove(begin);
	
	printf("list size after removal %lu \n", DLLCount(list));
	DLLDestroy(list);
}

void testSplice()
{
	/* add source to head of the dest */
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	int e = 5;
	int f = 6;
	int g = 7;
	int h = 8;
	/* list 1 = dest*/
	dll_t *list = DLLCreate();
	dll_t *list2 = DLLCreate();
	dll_iter_t begin = DLLBegin(list);
	dll_iter_t begin2 = DLLBegin(list2);
	dll_iter_t end = DLLEnd(list);
	dll_iter_t end2 = DLLEnd(list2);
	dll_iter_t inserted2;
	dll_iter_t from;
	dll_iter_t to;
	
	dll_iter_t inserted1 = DLLInsertBefore(begin, (void*)&d);
	inserted1 = DLLInsertBefore(begin, (void*)&c);
	inserted1 = DLLInsertBefore(begin, (void*)&b);
	inserted1 = DLLInsertBefore(begin, (void*)&a);
	printf("list1 size1 after insertion %lu \n", DLLCount(list));
	begin = DLLBegin(list);
	while(begin != DLLEnd(list))
	{
    		printf("list 1 element %d\n",*(int*)DLLGetData(begin));
		
		begin = DLLNext(begin);
	}
	/* list 2 = source*/
	 inserted2 = DLLInsertBefore(begin2, (void*)&h);
	 inserted2 = DLLInsertBefore(begin2, (void*)&g);
	 inserted2 = DLLInsertBefore(begin2, (void*)&f);
	 inserted2 = DLLInsertBefore(begin2, (void*)&e);
	printf("list2 size2 after insertion %lu \n", DLLCount(list2));
	begin = DLLBegin(list2);
	while(begin != DLLEnd(list2))
	{
    		printf("list 2 element %d\n",*(int*)DLLGetData(begin));
		
		begin = DLLNext(begin);
	}
	
	
	begin = DLLNext(DLLNext(DLLBegin(list)));
	from = DLLBegin(list2);
	to = DLLEnd(list2);
	/* dest head and source head to dummy */
	DLLSplice(begin, from, to);
	printf("dest element after splice %d\n",*(int*)DLLGetData(begin));
	printf("from element after splice %d\n",*(int*)DLLGetData(from));
	printf("to element after splice %d\n",*(int*)DLLGetData(to));
	
	begin = DLLBegin(list);
	begin2 = DLLBegin(list2);
	printf("list size1 after splice %lu \n", DLLCount(list));
	printf("list size2 after splice %lu \n", DLLCount(list2));
	printf("run on splice\n");
	begin = DLLBegin(list);
	while(begin != DLLEnd(list))
	{
    		printf("element %d\n",*(int*)DLLGetData(begin));
		
		begin = DLLNext(begin);
	}
	/*begin = DLLPrev(DLLEnd(list));
	while(begin != NULL)
	{
    		printf("element %d\n",*(int*)DLLGetData(begin));
		
		begin = DLLPrev(begin);
	}
	*/
	DLLDestroy(list);
	DLLDestroy(list2);
	}







