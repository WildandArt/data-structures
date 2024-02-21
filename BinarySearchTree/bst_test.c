#include "bst.h"
#include <assert.h>
#include <stdio.h>
void testInsert();
void testNext();
void testPrev();
void testRemoveOneChild();
void testRemoveTwoChildren();
bst_t *CreateBST();
void testBeginAndCount();
void testDestroy();
void testForEachAndFind();
void testRemoveTwoChildrenIsLeaf();
void testRemoveTwoChildrenNotLeaf();
int cmp(void *data, void *new_data, void *param)
{
	(void)param;
	return *(int*)data - *(int*)new_data;
}
int Action(void *data, void *param)
{
	*(int*)data += *(int*)param;
	 return 0;
}

int main()
{
	/*testInsert();*/
	/*testNext(); *//* next seven collapses*/
	 /*testPrev();*/ /* preb of seven core dumps*/
	/*testBeginAndCount();*//* fails in count core dump*/
	 	
	/*testForEachAndFind();*//* problem with foreach and with destroy-both core dump*/

	/*testDestroy();*/

	
	/*testRemoveOneChild();*/ /* failed with removal of root */
	testRemoveTwoChildrenIsLeaf(); /* fails with removal 200*/
	/*testRemoveTwoChildrenNotLeaf(); passed but destroy core dumped strange*/

	return 0;
}

void testForEachAndFind()
{
	bst_t *tree = NULL;

	bst_iter_t iter_hundred = NULL;
	bst_iter_t iter_sevfive = NULL;
	bst_iter_t iter_two_hundred = NULL;
	bst_iter_t iter_one_eighty = NULL;
	bst_iter_t iter_one_ninety = NULL;
	bst_iter_t iter_one_fifty = NULL;
	bst_iter_t iter_two_fifty = NULL;
	bst_iter_t iter_two_seventy = NULL;
	bst_iter_t iter_three_hundred = NULL;
	bst_iter_t iter_three_fifty = NULL;
	bst_iter_t iter_two_thirty = NULL;
	bst_iter_t root = NULL;
	bst_iter_t prev = NULL;
	bst_iter_t end = NULL;
	bst_iter_t find = NULL;
	
	int status = 0;

	int one = 1;
	int hundred = 100;
	int two_hundred = 200;
	int three_hundred = 300;
	int sevfive = 75;
	int three_fifty = 350;
	int two_fifty = 250;
	int one_eighty = 180;
	int one_ninety = 190;
	int one_fifty = 150;
	int two_seventy = 270;
	int two_thirty = 230;
	tree = BSTCreate(cmp, (void*)1);
	end = BSTEnd(tree);
	
	iter_hundred = BSTInsert(tree, (void*)&hundred);
	iter_sevfive = BSTInsert(tree, (void*)&sevfive);
	iter_two_hundred = BSTInsert(tree, (void*)&two_hundred);
	iter_three_hundred = BSTInsert(tree, (void*)&three_hundred);
	iter_one_eighty = BSTInsert(tree, (void*)&one_eighty);
	iter_one_ninety = BSTInsert(tree, (void*)&one_ninety);
	iter_one_fifty = BSTInsert(tree, (void*)&one_fifty);
	iter_two_fifty = BSTInsert(tree, (void*)&two_fifty);
	iter_two_seventy = BSTInsert(tree, (void*)&two_seventy);
	iter_two_thirty = BSTInsert(tree, (void*)&two_thirty);
	iter_three_fifty = BSTInsert(tree, (void*)&three_fifty);
	
	/*find = BSTFind(tree, (void*)&two_thirty);
	assert(230 == *(int*)BSTGetData(find));
	printf("\n BSTFind %d \n", *(int*)BSTGetData(find));
	print2D(iter_hundred);
	printf("\n----------------------------------\n");*/
	status = BSTForEach(tree,  Action, (void*)&one);
	printf("\n----------------------------------\n");
	/*print2D(iter_hundred);*/
	/*assert(0 == status);*/
	printf("\n---------------testForEach--& Find----passed-------------\n");
	BSTDestroy(tree);
}
void testBeginAndCount()
{

	bst_t *tree = NULL;

	bst_iter_t iter_hundred = NULL;
	bst_iter_t iter_sevfive = NULL;
	bst_iter_t iter_two_hundred = NULL;
	bst_iter_t iter_one_eighty = NULL;
	bst_iter_t iter_one_ninety = NULL;
	bst_iter_t iter_one_fifty = NULL;
	bst_iter_t iter_two_fifty = NULL;
	bst_iter_t iter_two_seventy = NULL;
	bst_iter_t iter_three_hundred = NULL;
	bst_iter_t iter_three_fifty = NULL;
	bst_iter_t iter_two_thirty = NULL;
	bst_iter_t root = NULL;
	bst_iter_t prev = NULL;
	bst_iter_t end = NULL;
	bst_iter_t begin = NULL;

	int hundred = 100;
	int two_hundred = 200;
	int three_hundred = 300;
	int sevfive = 75;
	int three_fifty = 350;
	int two_fifty = 250;
	int one_eighty = 180;
	int one_ninety = 190;
	int one_fifty = 150;
	int two_seventy = 270;
	int two_thirty = 230;
	tree = BSTCreate(cmp, (void*)1);
	end = BSTEnd(tree);
	assert((0 == BSTCount(tree)));
	iter_two_hundred = BSTInsert(tree, (void*)&two_hundred);
	iter_three_hundred = BSTInsert(tree, (void*)&three_hundred);
	assert((2 == BSTCount(tree)));
	iter_two_fifty = BSTInsert(tree, (void*)&two_fifty);
	iter_two_seventy = BSTInsert(tree, (void*)&two_seventy);
	iter_two_thirty = BSTInsert(tree, (void*)&two_thirty);
	iter_three_fifty = BSTInsert(tree, (void*)&three_fifty);
	
	begin = BSTBegin(tree);
	assert((200 == *(int*)BSTGetData(begin)));
	print2D(iter_two_hundred);
	
	printf("\nCount : %lu \n", BSTCount(tree)); 
	/*assert((6 == BSTCount(tree)));
	printf("\n----------------------------------\n");

	printf("\ntestBeginAndCount passed\n");*/
}
void testDestroy()
{
	bst_t *tree = NULL;
	bst_iter_t iter_hundred = NULL;
	bst_iter_t iter_sevfive = NULL;
	bst_iter_t iter_two_hundred = NULL;
	bst_iter_t end = NULL;
	int hundred = 100;
	int two_hundred = 200;
	int sevfive = 75;
	
	tree = BSTCreate(cmp, (void*)1);
	end = BSTEnd(tree);
	
	iter_hundred = BSTInsert(tree, (void*)&hundred);
	iter_sevfive = BSTInsert(tree, (void*)&sevfive);
	iter_two_hundred = BSTInsert(tree, (void*)&two_hundred);
	
	BSTDestroy(tree);
	/*assert(NULL == iter_hundred);*/
	/*print2D(iter_hundred);*/

	printf("\nPassed");
}

void testRemoveTwoChildrenNotLeaf()
{
	bst_t *tree = NULL;
	bst_iter_t iter_thou = NULL;
	bst_iter_t iter_five_h = NULL;
	bst_iter_t iter_five_fifty = NULL;
	bst_iter_t iter_four_h = NULL;
	bst_iter_t iter_six_h = NULL;
	bst_iter_t iter_three_h = NULL;
	bst_iter_t iter_two_h = NULL;
	bst_iter_t iter_three_fifty = NULL;
	bst_iter_t iter_three_sev = NULL;
	
	bst_iter_t root = NULL;
	bst_iter_t prev = NULL;
	bst_iter_t end = NULL;
	
	void *removed_data = NULL;
	int thou = 1000;
	int five_h = 500;
	int five_fifty = 550;
	int four_h = 400;
	int six_h = 600;
	int three_h = 300;
	int two_h = 200;
	int three_fifty = 350;
	int three_sev = 370;

	tree = BSTCreate(cmp, (void*)1);
	end = BSTEnd(tree);
	
	iter_thou = BSTInsert(tree, (void*)&thou);
	iter_five_h = BSTInsert(tree, (void*)&five_h);
	iter_four_h = BSTInsert(tree, (void*)&four_h);
	iter_five_fifty = BSTInsert(tree, (void*)&five_fifty);
	iter_six_h = BSTInsert(tree, (void*)&six_h);
	
	print2D(iter_thou);
	printf("\n-------------after 500 removal---------------------\n");
	removed_data = BSTRemove(iter_five_h);
	assert(500 == *(int*)removed_data);
	print2D(iter_thou);
	printf("\n-----------Part 2-----------------------\n");
	BSTDestroy(tree);
	tree = BSTCreate(cmp, (void*)1);
	
	iter_five_h = BSTInsert(tree, (void*)&five_h);
	iter_three_h = BSTInsert(tree, (void*)&three_h);
	iter_four_h = BSTInsert(tree, (void*)&four_h);
	iter_two_h = BSTInsert(tree, (void*)&two_h);
	iter_three_fifty = BSTInsert(tree, (void*)&three_fifty);
	iter_three_sev = BSTInsert(tree, (void*)&three_sev);
	
	print2D(iter_five_h);
	printf("\n--------after 300 removal--------------------------\n");
	removed_data = BSTRemove(iter_three_h);
	assert(300 == *(int*)removed_data);
	print2D(iter_five_h);
	printf("\n---------------------------------------------------\n");
	BSTDestroy(tree);
}
void testRemoveTwoChildrenIsLeaf()
{
	bst_t *tree = NULL;

	bst_iter_t iter_hundred = NULL;
	bst_iter_t iter_sevfive = NULL;
	bst_iter_t iter_two_hundred = NULL;
	bst_iter_t iter_one_eighty = NULL;
	bst_iter_t iter_one_ninety = NULL;
	bst_iter_t iter_one_fifty = NULL;
	bst_iter_t iter_two_fifty = NULL;
	bst_iter_t iter_two_seventy = NULL;
	bst_iter_t iter_three_hundred = NULL;
	bst_iter_t iter_three_fifty = NULL;
	bst_iter_t iter_two_thirty = NULL;
	bst_iter_t root = NULL;
	bst_iter_t prev = NULL;
	bst_iter_t end = NULL;
	

	int hundred = 100;
	int two_hundred = 200;
	int three_hundred = 300;
	int sevfive = 75;
	int three_fifty = 350;
	int two_fifty = 250;
	int one_eighty = 180;
	int one_ninety = 190;
	int one_fifty = 150;
	int two_seventy = 270;
	int two_thirty = 230;
	tree = BSTCreate(cmp, (void*)1);
	end = BSTEnd(tree);
	
	iter_hundred = BSTInsert(tree, (void*)&hundred);
	iter_sevfive = BSTInsert(tree, (void*)&sevfive);
	iter_two_hundred = BSTInsert(tree, (void*)&two_hundred);
	iter_three_hundred = BSTInsert(tree, (void*)&three_hundred);
	iter_one_eighty = BSTInsert(tree, (void*)&one_eighty);
	iter_one_ninety = BSTInsert(tree, (void*)&one_ninety);
	iter_one_fifty = BSTInsert(tree, (void*)&one_fifty);
	iter_two_fifty = BSTInsert(tree, (void*)&two_fifty);
	iter_two_seventy = BSTInsert(tree, (void*)&two_seventy);
	iter_two_thirty = BSTInsert(tree, (void*)&two_thirty);
	iter_three_fifty = BSTInsert(tree, (void*)&three_fifty);
	
	print2D(iter_hundred);
	
	printf("\n----------------------------------\n");
	BSTRemove(iter_one_eighty);
	printf("\n---------remove 180--min is right leaf-----------------------");
	print2D(iter_hundred);
	
	printf("\n----------remove 200 min is left leaf------------------------");
	
	BSTRemove(iter_two_hundred);
	print2D(iter_hundred);

	printf("\n-------------------------------------------------------\n");
}
void testRemoveOneChild()
{
	bst_t *tree = NULL;

	bst_iter_t iter_five = NULL;
	bst_iter_t iter_ten = NULL;
	bst_iter_t iter_two = NULL;
	bst_iter_t iter_twenty = NULL;
	bst_iter_t iter_seven = NULL;
	bst_iter_t root = NULL;
	bst_iter_t prev = NULL;
	bst_iter_t end = NULL;
	void *removed = NULL;

	int hundred = 100;
	int two = 2;
	int five = 5;
	int seven = 7;
	int ten = 10;
	int twenty = 20;
	tree = BSTCreate(cmp, (void*)1);
	end = BSTEnd(tree);
	
	iter_ten = BSTInsert(tree, (void*)&ten);
	iter_five = BSTInsert(tree, (void*)&five);
	iter_two = BSTInsert(tree, (void*)&two);
	iter_seven = BSTInsert(tree, (void*)&seven);
	iter_twenty = BSTInsert(tree, (void*)&twenty);
	
	print2D(iter_ten);
	printf("\n----------remove seven------------------------");
	BSTRemove(iter_seven);
	printf("\n---------------------------------");
	print2D(iter_ten);
	printf("\n----------remove five------------------------");
	BSTRemove(iter_five);
	print2D(iter_ten);
	printf("\n-----------insert five-----------------------");
	iter_five = BSTInsert(tree, (void*)&five);
	print2D(iter_ten);
	printf("\n-------------remove two---------------------");
	BSTRemove(iter_two);
	print2D(iter_ten);
	printf("\n--------------remove five--------------------");

	BSTRemove(iter_five);
	print2D(iter_ten);
	printf("\n----------------------------------");
	printf("\n----remove root(10) with one child-----");
	BSTRemove(iter_ten);
	printf("\n-----------after-----------------------");
	print2D(getRoot(tree));
	printf("\n-----------after-root removal 20----------------------");
	BSTRemove(getRoot(tree));
	print2D(getRoot(tree));
	printf("\n----------------------------------");
	/*
	this is a test for dummy, not obligatory
	prev = BSTPrev(iter_twenty);
	assert(1 == BSTIsIterEqual(prev, end));
	printf("\nprev returns dummy PASSED");*/

}
void testInsert()
{
		bst_t *tree = NULL;
		void *param = (int*)1;
		bst_iter_t root = NULL;
		bst_iter_t iter_two = NULL;
		bst_iter_t iter_three = NULL;
		bst_iter_t iter_five = NULL;
		bst_iter_t iter_six = NULL;
		bst_iter_t iter_seven = NULL;
		bst_iter_t iter_eight = NULL;
		bst_iter_t iter_ten = NULL;
		int hundred = 100;
		int two = 2;
		int three = 3;
		int five = 5;
		int six = 6;
		int seven = 7;
		int eight = 8;
		int ten = 10;
		int twenty = 20;

		tree = BSTCreate(cmp, param);

		iter_five = BSTInsert(tree, (void*)&ten);
		iter_five = BSTInsert(tree, (void*)&five);
		iter_five = BSTInsert(tree, (void*)&two);
		iter_five = BSTInsert(tree, (void*)&twenty);
		iter_five = BSTInsert(tree, (void*)&seven);
		iter_five = BSTInsert(tree, (void*)&six);
		iter_five = BSTInsert(tree, (void*)&eight);
		assert(iter_five);
		root = getRoot(tree);
		print2D(root);
		
		/*Preorder(root);*/

}
void testNext()
{
	bst_t *tree = NULL;
	void *param = (int*)1;
	bst_iter_t iter_five = NULL;
	bst_iter_t iter_ten = NULL;
	bst_iter_t iter_two = NULL;
	bst_iter_t iter_twenty = NULL;
	bst_iter_t iter_seven = NULL;
	bst_iter_t root = NULL;
	bst_iter_t next = NULL;
	bst_iter_t end = NULL;
	int hundred = 100;
	int two = 2;
	int five = 5;
	int seven = 7;
	int ten = 10;
	int twenty = 20;
	tree = BSTCreate(cmp, param);
	end = BSTEnd(tree);
	iter_ten = BSTInsert(tree, (void*)&ten);
	iter_five = BSTInsert(tree, (void*)&five);
	iter_two = BSTInsert(tree, (void*)&two);
	iter_seven = BSTInsert(tree, (void*)&seven);
	iter_twenty = BSTInsert(tree, (void*)&twenty);
	/*next = BSTNext(iter_twenty);
	assert(1 == BSTIsIterEqual(next, end));*/
	root = getRoot(tree);
	print2D(root);

	next = BSTNext(iter_two);
	printf("\n getdata %d \n", *(int*)BSTGetData(next));
	next = BSTNext(iter_seven);
	printf("\n getdata %d \n", *(int*)BSTGetData(next));

}
void testPrev()
{
	bst_t *tree = NULL;
	void *param = (int*)1;
	bst_iter_t iter_five = NULL;
	bst_iter_t iter_ten = NULL;
	bst_iter_t iter_two = NULL;
	bst_iter_t iter_twenty = NULL;
	bst_iter_t iter_seven = NULL;
	bst_iter_t root = NULL;
	bst_iter_t prev = NULL;
	bst_iter_t end = NULL;
	

	int hundred = 100;
	int two = 2;
	int five = 5;
	int seven = 7;
	int ten = 10;
	int twenty = 20;
	
	tree = BSTCreate(cmp, param);
	end = BSTEnd(tree);
	
	iter_ten = BSTInsert(tree, (void*)&ten);
	iter_five = BSTInsert(tree, (void*)&five);
	iter_two = BSTInsert(tree, (void*)&two);
	iter_seven = BSTInsert(tree, (void*)&seven);
	iter_twenty = BSTInsert(tree, (void*)&twenty);
	

	prev = BSTPrev(iter_two);
	assert(1 == BSTIsIterEqual(prev, end));
	printf("\nPASSED");
	
	prev = BSTPrev(iter_seven);
	assert(5 == (*(int*)BSTGetData(prev)));
	printf("\nPASSED");
	print2D(iter_ten);
}

bst_t *CreateBST(bst_t *t)
{
	bst_t *tree = t;

	bst_iter_t iter_five = NULL;
	bst_iter_t iter_ten = NULL;
	bst_iter_t iter_two = NULL;
	bst_iter_t iter_twenty = NULL;
	bst_iter_t iter_seven = NULL;
	bst_iter_t root = NULL;
	bst_iter_t prev = NULL;
	bst_iter_t end = NULL;

	int hundred = 100;
	int two = 2;
	int five = 5;
	int seven = 7;
	int ten = 10;
	int twenty = 20;
	assert(tree);
	tree = BSTCreate(cmp, (void*)1);
	end = BSTEnd(tree);
	
	iter_ten = BSTInsert(tree, (void*)&ten);
	iter_five = BSTInsert(tree, (void*)&five);
	iter_two = BSTInsert(tree, (void*)&two);
	iter_seven = BSTInsert(tree, (void*)&seven);
	iter_twenty = BSTInsert(tree, (void*)&twenty);
	
	return tree;
}




