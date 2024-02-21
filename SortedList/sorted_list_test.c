#include <stdio.h>
#include "sorted_list.h"
int CompareInts(void *data, void *new_data)
{
	return *(int*)data - *(int*)new_data;
}
int IsMatchInt(void *data, void *new_data)
{
	return *(int*)data == *(int*)new_data;
}
int ActionPrint(void *data, void *new_data)
{
	printf("element: %d ", *(int*)data);
	return 0;
}
int ActionFunction(void *data, void *new_data)
{
	 *(int*)data += *(int*)new_data;
	 return 0;
}
void testForEach();

int main()
{
	testForEach();
	/*sorted_list_compare_func_t compare = CompareInts;
	sorted_list_t *list;
	int a = 5;
	int b = 1;
	int c = 6;
	int d = 4;
	sorted_list_iter_t begin;
	sorted_list_iter_t end;
	sorted_list_iter_t from;
	sorted_list_iter_t to;
	sorted_list_iter_t find;
	list = SortedListCreate(compare);
	begin = SortedListBegin(list);
	
	begin = SortedListInsert(list, &a);
	begin = SortedListInsert(list, &b);
	begin = SortedListInsert(list, &c);
	begin = SortedListInsert(list, &d);
	
	from = SortedListBegin(list);
	to = SortedListEnd(list);
	find = SortedListFind(list, from, to, &c);
	
	printf(" -><><> found element :%d -><><>\n",*(int*)SortedListGetData(find));
	from = SortedListBegin(list);
	to = SortedListEnd(list);
	find = SortedListFindIf(from, to, IsMatchInt, &d);
	printf(" -><><> found match :%d -><><>\n",*(int*)SortedListGetData(find));
	
	from = SortedListBegin(list);
	to = SortedListEnd(list);
	
	SortedListForEach( from, to, ActionFunction, &d);
	
	from = SortedListBegin(list);
	to = SortedListEnd(list);
	
	for(;!SortedListIsEqual(from,to); from = SortedListNext(from))
	{
		printf(" \nafter foreach element :%d ",*(int*)SortedListGetData(from));
	}
	printf("\n");
	to = SortedListBegin(list);
	from = SortedListPrev(SortedListEnd(list));
	for(;!SortedListIsEqual(from,to); from = SortedListPrev(from))
	{
		printf(" element :%d ",*(int*)SortedListGetData(from));
	}
	printf(" element :%d ",*(int*)SortedListGetData(from));
	SortedListDestroy(list);*/
	


return 0;
}

void testForEach()
{
	sorted_list_t *list1;
	sorted_list_t *list2;
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	int e = 5;
	int f = 6;
	int g = 7;
	int h = 8;
	int z = 100;
	sorted_list_compare_func_t compare = CompareInts;
	sorted_list_iter_t begin;
	sorted_list_iter_t from;
	sorted_list_iter_t to = {NULL};
	
	list1 = SortedListCreate(compare);
	list2 = SortedListCreate(compare);
	
	begin = SortedListBegin(list1);
	
	
	SortedListInsert(list1, &a);
	SortedListInsert(list1, &f);
	SortedListInsert(list1, &g);
	SortedListInsert(list1, &h);
	
	SortedListInsert(list2, &b);
	SortedListInsert(list2, &c);
	SortedListInsert(list2, &d);
	SortedListInsert(list2, &z);


	
	from = SortedListBegin(list1);
	to = SortedListEnd(list1);
	
	for(;!SortedListIsEqual(from,to); from = SortedListNext(from))
	{
		printf(" \nbefore foreach element :%d ",*(int*)SortedListGetData(from));
	}
	printf("jhjhjh\n");
	
	from = SortedListBegin(list1);
	to = SortedListEnd(list1);
	
	SortedListForEach( from, to, ActionFunction, (void*)&d);
	/*SortedListMerge(list1, list2);*/
	
	
	from = SortedListBegin(list1);
	to = SortedListEnd(list1);
	
	for(;!SortedListIsEqual(from,to); from = SortedListNext(from))
	{
		printf(" \nafter foreach element :%d ",*(int*)SortedListGetData(from));
	}
	printf("\n");
	
	to = SortedListBegin(list1);
	from = SortedListPrev(SortedListEnd(list1));
	
	for(;!SortedListIsEqual(from,to); from = SortedListPrev(from))
	{
		printf(" element :%d ",*(int*)SortedListGetData(from));
	}
	printf(" element :%d ",*(int*)SortedListGetData(from));
	
	
	SortedListDestroy(list1);
	SortedListDestroy(list2);		
}





