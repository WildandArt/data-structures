#include <assert.h> /*assert*/
#include <stdio.h> /*printf, puts*/
#include "avl.h"

void TestAVLCreate();
void TestAVLInsert();
void TestAVLCount();
void TestAVLForEach();
void TestAVLRemove();
void TestAVLHeight();

int Compare(void *data, void *new_data , void *param)
{
	return ((size_t)data - (size_t)new_data);
}

int Action(void *data, void *arg)
{
	(void )arg;
	printf("%d ", *(int *)&data);
	return 0;
}

int FailedAction(void *data, void *arg)
{
	(void )arg;
	printf("%d ", *(int *)&data);
	return 1;
}

int main()
{
	/*TestAVLCreate();*/
	/*TestAVLInsert();*/
	/*TestAVLForEach();*/
	/*TestAVLRemove();*/ 
	/*TestAVLHeight();*/
	puts("Passed");
}

void TestAVLCreate()
{
	void *param;
	avl_t *avl = AVLCreate(Compare,param);
	assert(avl);
	
	assert(AVLIsEmpty(avl) == 1);
	AVLDestroy(avl);
}


void TestAVLInsert()
{
	int result = 0;
	void *param;
	avl_t *avl = AVLCreate(Compare,param);
	assert(avl);
	printf("-----------------------------Insert-----------------------------------");
	assert(AVLIsEmpty(avl) == 1);
	
	
	result = AVLInsert(avl, (void *)100);
	
	assert(AVLIsEmpty(avl) == 0);
	
	result = AVLInsert(avl, (void *)113);
	
	result = AVLInsert(avl, (void *)150);
	/*assert(result == 0);
	assert(AVLCount(avl) == 6); */

	printf("----------------------------------------------------------------");
	printTree(GetRoot(avl), 0);
	
	result = AVLInsert(avl, (void *)11);
	printf("----------------------------------------------------------------");
	printTree(GetRoot(avl), 0);
	result = AVLInsert(avl, (void *)10);
	printf("----------------------------------------------------------------");
	printTree(GetRoot(avl), 0);
	
	result = AVLInsert(avl, (void *)9);
	printf("----------------------------------------------------------------");
	printTree(GetRoot(avl), 0);
	
	result = AVLInsert(avl, (void *)8);
	
	printTree(GetRoot(avl), 0);
	printf("----------------------------------------------------------------");
	result = AVLInsert(avl, (void *)7);
	printf("----------------------------------------------------------------");
	printTree(GetRoot(avl), 0);
	
	
	
	
	result = AVLForEach(avl, Action, NULL, POST_ORDER);


	/*
	result = AVLInsert(avl, (void *)9);
	
	
	result = AVLInsert(avl, (void *)11);
	
	
	
	result = AVLInsert(avl, (void *)13);
	
	
	result = AVLInsert(avl, (void *)14);
	
	
	result = AVLInsert(avl, (void *)15);
	*/
	
	/*
	assert(AVLFind(avl, (void *)9) == (void *)9);
	
	assert(AVLFind(avl, (void *)16) == NULL);
	*/
	AVLDestroy(avl);
}

void TestAVLForEach()
{
	int result = 0;
	void *param;
	void *arg = NULL;
	avl_t *avl = AVLCreate(Compare,param);
	assert(avl);
	
	assert(AVLIsEmpty(avl) == 1);
	
	result = AVLInsert(avl, (void *)25);
	assert(result == 0);
	
	assert(AVLIsEmpty(avl) == 0);
	
	result = AVLInsert(avl, (void *)15);
	assert(result == 0);
	assert(AVLCount(avl) == 2); 
	
	result = AVLInsert(avl, (void *)10);
	assert(AVLCount(avl) == 3); 
	
	result = AVLInsert(avl, (void *)4);
	assert(AVLCount(avl) == 4); 
	
	result = AVLInsert(avl, (void *)12);
	assert(AVLCount(avl) == 5); 
	
	result = AVLInsert(avl, (void *)22);
	assert(AVLCount(avl) == 6); 
	
	result = AVLInsert(avl, (void *)18);
	assert(AVLCount(avl) == 7); 
	
	result = AVLInsert(avl, (void *)24);
	assert(AVLCount(avl) == 8); 
	
	result = AVLInsert(avl, (void *)50);
	assert(AVLCount(avl) == 9); 
	
	result = AVLInsert(avl, (void *)31);
	assert(AVLCount(avl) == 10); 
	
	result = AVLInsert(avl, (void *)35);
	assert(AVLCount(avl) == 11); 
	
	result = AVLInsert(avl, (void *)44);
	assert(AVLCount(avl) == 12); 
	
	result = AVLInsert(avl, (void *)70);
	assert(AVLCount(avl) == 13); 
	
	result = AVLInsert(avl, (void *)66);
	assert(AVLCount(avl) == 14); 
	
	result = AVLInsert(avl, (void *)90);
	assert(AVLCount(avl) == 15); 
	
	printf("\n ----------------------- Action -----------------------\n");
	printf("\n PRE_ORDER : \n");
	result = AVLForEach(avl, Action, arg, PRE_ORDER);
	assert(result == 0);
	
	printf("\n IN_ORDER : \n");
	result = AVLForEach(avl, Action, arg, IN_ORDER);
	assert(result == 0);
	
	printf("\n POST_ORDER : \n");
	result = AVLForEach(avl, Action, arg, POST_ORDER);
	assert(result == 0);
	
	printf("\n ---------------------- FailedAction -----------------------\n");
	
	printf("\n PRE_ORDER : ");
	result = AVLForEach(avl, FailedAction, arg, PRE_ORDER);
	assert(result == 1);
	
	printf("\n IN_ORDER : ");
	result = AVLForEach(avl, FailedAction, arg, IN_ORDER);
	assert(result == 1);
	
	printf("\n POST_ORDER : ");
	result = AVLForEach(avl, FailedAction, arg, POST_ORDER);
	assert(result == 1);
	printf("\n");
		AVLDestroy(avl);
}

void TestAVLRemove()
{
	int result = 0;
	void *res = NULL;
	avl_t *avl = AVLCreate(Compare,NULL);
	assert(avl);
	assert(AVLCount(avl) == 0); 
	
	assert(AVLIsEmpty(avl) == 1);
	
	result = AVLInsert(avl, (void *)25);
	assert(result == 0);
	assert(AVLCount(avl) == 1); 
	
	assert(AVLIsEmpty(avl) == 0);
	
	result = AVLInsert(avl, (void *)15);
	assert(result == 0);
	/*assert(AVLCount(avl) == 2); */
	

	result = AVLInsert(avl, (void *)10);
	/*assert(AVLCount(avl) == 3); */
	
	result = AVLInsert(avl, (void *)4);
	/*assert(AVLCount(avl) == 4); */
	
	result = AVLInsert(avl, (void *)12);
	
	result = AVLInsert(avl, (void *)11);
	
	
	result = AVLInsert(avl, (void *)22);
	
	
	result = AVLInsert(avl, (void *)18);
	
	
	result = AVLInsert(avl, (void *)24);
	
	
	result = AVLInsert(avl, (void *)50);
	
	
	result = AVLInsert(avl, (void *)31);
	
	
	result = AVLInsert(avl, (void *)35);
	
	
	result = AVLInsert(avl, (void *)44);
	
	
	result = AVLInsert(avl, (void *)70);
	
	
	result = AVLInsert(avl, (void *)66);
	
	
	result = AVLInsert(avl, (void *)90);


	printTree(GetRoot(avl), 0);
	printf("-----------------------before remove-----------------------------------------");

	res = AVLRemove(avl, (void *)44);/* core dumped*/
		printTree(GetRoot(avl), 0);
	printf("----------------------24------------------------------------------");
	res = AVLRemove(avl, (void *)24);
	printTree(GetRoot(avl), 0);

	printf("----------------------------35------------------------------------");
	res = AVLRemove(avl, (void *)35);
	printTree(GetRoot(avl), 0);
	printf("----------------------------------------------------------------");
	res = AVLRemove(avl, (void *)18);
	printTree(GetRoot(avl), 0);
	printf("----------------------------------------------------------------");

	res = AVLRemove(avl, (void *)11);
	printTree(GetRoot(avl), 0);
	printf("----------------------------------------------------------------");

	res = AVLRemove(avl, (void *)15);
		printTree(GetRoot(avl), 0);
	printf("----------------------------------------------------------------");

	res = AVLRemove(avl, (void *)4);
		printTree(GetRoot(avl), 0);
	printf("----------------------------------------------------------------");

	res = AVLRemove(avl, (void *)12);/* here is another problem */
		printTree(GetRoot(avl), 0);
	printf("----------------------------------------------------------------");
	printTree(GetRoot(avl), 0);
	
	printf("remove : %d\n",*(int *)&res);
		AVLDestroy(avl);
}

void TestAVLHeight()
{
	avl_t *avl = AVLCreate(Compare,NULL);
	assert(avl);
	printf("height : %zu\n",AVLHeight(avl));
	
	AVLInsert(avl, (void *)33);
	
	AVLInsert(avl, (void *)9);
	
	AVLInsert(avl, (void *)8);
	
	AVLInsert(avl, (void *)11);
	
	AVLInsert(avl, (void *)21);
	
	AVLInsert(avl, (void *)61);
	
	AVLInsert(avl, (void *)53);
	
	printf("height : %zu\n",AVLHeight(avl));
}


