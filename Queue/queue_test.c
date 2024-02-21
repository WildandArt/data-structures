
#include "queue.h"
#include <stdio.h>
int main()
{
	int a = 10;
	int b = 20;
	
	queue_t *queue = QueueCreate();
	queue_t *queue1 = QueueCreate();
	
	printf("is empty? %d\n", QueueIsEmpty(queue));
	
	/*two enqueues*/
	printf("-----------------Enqueue---------------------\n");
	QueueEnqueue(queue, (void *)&b);
	printf("QueuePeek = %d\n", *(int *)QueuePeek(queue));
	QueueEnqueue(queue, (void *)&a);
	printf("size queue: %lu\n", QueueSize(queue));
	printf("-----------------Dequeue---------------------\n");
	QueueDequeue(queue);
	printf("size queue: %lu\n", QueueSize(queue));
	printf("-----------------Append---------------------\n");
	QueueEnqueue(queue1, (void *)&b);
	QueueEnqueue(queue1, (void *)&a);
	printf("size queue  : %lu\n", QueueSize(queue));
	printf("size queue 1: %lu\n", QueueSize(queue1));
	QueueAppend(queue, queue1);
	printf("size queue after append : %lu\n", QueueSize(queue));
	printf("size queue 1 after append : %lu\n", QueueSize(queue1));
	printf("-----------------Destroy---------------------\n");
	QueueDestroy(queue);
	QueueDestroy(queue1);
	
	return 0;
}

