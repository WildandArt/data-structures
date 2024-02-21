
#include <stdio.h>     /*malloc free */
#include "heap.h"

int ComperInt(const void *x, const void *y)
{
	return -(*(int *)&x - *(int *)&y);
}

int Match(const void *x, const void *y)
{
	return !(*(int *)&x - *(int *)&y);
}

void PrintHeap2(heap_t *heap)
{
	void *vp;
	while(!HeapIsEmpty(heap))
	{
		vp = HeapPeek(heap);
		printf("%d\n", *(int *)&vp);
		HeapPop(heap);
	}
	printf("\ndfdfdcv\n");
}
int main()
{
	heap_t *heap = HeapCreate(ComperInt);
	void *vp;
	int i = 0;
	HeapPush(heap, (void *)100);
	HeapPush(heap, (void *)5);
	HeapPush(heap, (void *)90);
	HeapPush(heap, (void *)1);
	HeapPush(heap, (void *)2);
	HeapPush(heap, (void *)70);
	HeapPush(heap, (void *)80);
	/*HeapPush(heap, (void *)80);*/
	HeapRemove(heap, (void *)1, Match);
	
	PrintHeap2(heap);
	HeapDestroy(heap);
	
	return 0;
}

