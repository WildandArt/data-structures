
/*
Author: Art
Reviewer: Nir
Date: 26 Apr Independence Day
*/

#include<stdlib.h>  /* malloc, free                                */
#include <stdio.h>  /* printf for utility functions(printing tree) */
#include<assert.h>  /* assert                                      */

#include "bst.h"    /* include bst                                 */
#include"queue.h"	/*include queue for Destroy function           */


typedef struct bst_node bst_node_t;
/*-----------My helper functions do not delete--------------------*/
bst_node_t *CreateNode(void *data);
bst_iter_t getRoot(bst_t *bst);
int isLeftChild(bst_iter_t iter);
int isRightChild(bst_iter_t iter);
int hasLeftChild(bst_iter_t iter);
int hasRightChild(bst_iter_t iter);
int hasOneChild(bst_iter_t iter);
int isLeaf(bst_iter_t iter);
/*----------------------------------------------------------------------------*/
struct bst_node
{
	void* data;
	struct bst_node* left;
	struct bst_node* right;
	struct bst_node* parent;
};
struct bst
{
	struct bst_node* end;
	bst_compare_func_t cmp;
	void *param;
};

/*----------------------------------------------------------------------------*/
void *BSTGetData(bst_iter_t iter)
{
	assert(iter);
	return iter->data;
}
/*----------------------------------------------------------------------------*/
bst_t *BSTCreate(bst_compare_func_t cmp, void * param)
{
	bst_node_t *dummy = NULL;
	bst_node_t *root = NULL;
	void *data = NULL;
	
	bst_t *bst = (bst_t *)malloc(sizeof(bst_t));
	if(NULL == bst)
	{
		return NULL;
	}
	bst->cmp = cmp;
	bst->param = param;
	dummy = CreateNode(data);
	
	if(NULL == dummy)
	{
		free(bst);
		return NULL;
	}
	bst->end = dummy;
	return bst;
}
/*----------------------------------------------------------------------------*/
void BSTDestroy(bst_t *bst)
{
	queue_t *q = NULL;
	bst_iter_t iter = NULL;
	bst_iter_t end = NULL;
	
	assert(bst);
	
	q = QueueCreate();
	
	iter = getRoot(bst);
	assert(iter);
	
	/* disconnect dummy from root*/
	end = BSTEnd(bst);
	end->left = NULL;
	
	QueueEnqueue(q, (void*)iter);
	
	while(!QueueIsEmpty(q))
	{
		iter = (bst_iter_t)QueuePeek(q);
		
		if(NULL != iter->right)
		{
			QueueEnqueue(q, (void*)iter->right);
		}
		if(NULL != iter->left)
		{
			QueueEnqueue(q, (void*)iter->left);
		}
		QueueDequeue(q);
		free(iter);
	}
	QueueDestroy(q);
	free(end);
	free(bst);
}
int BSTIsEmpty(const bst_t *bst)
{
	assert(bst);
	return (NULL == (bst->end)->left);
}

/*---------------------------------------------------------------------------*/
bst_iter_t BSTInsert(bst_t *bst, void *data)
{
	bst_iter_t new = NULL;
	bst_iter_t iterator = NULL;
	void *key = NULL;
	void *param = NULL;
	int result = 0;
	new = CreateNode(data);
	if(NULL == new)
	{
		return bst->end;
	}
	
	if(BSTIsEmpty(bst))
	{
		(bst->end)->left = new;
		/* root points to dummy*/
		new->parent = bst->end;
		return new;
	}
	/* point to root*/
	iterator = (bst->end)->left;
	
	key = data;
	
	while(iterator != NULL)
	{
		result = bst->cmp(key, iterator->data, param);
		
		if(result > 0)
		{
			if(NULL == iterator->right)
			{
				iterator->right = new;
				new->parent = iterator;
				return new;
			}
			iterator = iterator->right;
		}
		else
		{
			if(NULL == iterator->left)
			{
				iterator->left = new;
				new->parent = iterator;
				return new;
			}
			iterator = iterator->left;
		}
	}
}
/*---------------------------------------------------------------------------*/

void *BSTRemove(bst_iter_t iter)
{
	void *data = NULL;
	void *iter_data = NULL;
	bst_iter_t to_be_removed;
	bst_iter_t min_node = NULL;
	assert(iter);
	
	iter_data = iter->data;
	
	/*lonely node*/
	if(NULL == iter->parent->parent && (!hasLeftChild(iter)) && (!hasRightChild(iter)))
	{
		iter->parent->left = NULL;
		free(iter);
		return iter_data;
	}
	
	if(isLeaf(iter))
	{
		/*copy data to parent, free the child */
		data = iter->data;
		if(isLeftChild(iter))
		{
			iter->parent->left = NULL;
		}
		else
		{
			iter->parent->right = NULL;
		}
		free(iter);
		return iter_data;
	}
	/*case has one child*/
	if(hasOneChild(iter))
	{
		to_be_removed = iter;
		if(hasLeftChild(iter))
		{
			iter->parent->left = iter->left;
			iter->left->parent = iter->parent;
			return iter_data;
		}
		if(hasRightChild(iter))
		{
			iter->parent->left = iter->right;
			iter->right->parent = iter->parent;
			return iter_data;
		}

		free(to_be_removed);
	}
	if(hasLeftChild(iter) && hasRightChild(iter))
	{
		min_node = BSTNext(iter);
		if(isLeaf(min_node))
		{
			data = min_node->data;

			if(isLeftChild(min_node))
			{
				/* free itself,parent->left = NULL*/
				iter->data = data;
				/*min_node->parent->data = data;*/
				min_node->parent->left = NULL;
				free(min_node);
				return iter_data;

			}
			if(isRightChild(min_node))
			{
				iter->data = data;
				min_node->parent->right = NULL;
				free(min_node);
				return iter_data;
			}
		}
		if(isLeftChild(min_node))
		{
			data = min_node->data;
			iter->data = data;
			min_node->parent->left = min_node->right;
			min_node->right->parent = min_node->parent;
			free(min_node);
			return iter_data;
		}
		if(isRightChild(min_node))
		{
			data = min_node->data;
			iter->data = data;
			min_node->right->parent = iter;
			iter->right = min_node->right;
			free(min_node);
			return iter_data;
		}
	}
	
}
/*---------------------------------------------------------------------------*/
int BSTForEach(bst_t *bst, bst_action_func_t act, void *param)
{
	bst_iter_t iterator = NULL;
	bst_iter_t end = NULL;
	int status = 0;
	
	assert(bst);
	
	if(NULL == getRoot((bst_t*)bst))
	{
		return 1;
	}
	end = BSTEnd(bst);
	iterator = BSTBegin(bst);
	
	while(!BSTIsIterEqual(iterator, end))
	{
		status = act(iterator->data, param);
		if(status)
		{
			return status;
		}
		
		iterator = BSTNext(iterator);
	}
	return 0;
}
/*---------------------------------------------------------------------------*/
bst_iter_t BSTFind(const bst_t *bst, void *data)
{
	bst_iter_t iterator = NULL;
	bst_iter_t end = NULL;
	void *param = NULL;
	int result = 0;
	assert(bst);
	
	end = BSTEnd(bst);
	
	if(BSTIsEmpty(bst))
	{
		return end;
	}
	
	iterator = getRoot((bst_t*)bst);
	
	while(iterator != NULL)
	{
		result = bst->cmp(data, iterator->data, param);
		
		if(result == 0)
		{
			return iterator;
		}
		if(result > 0)
		{
			iterator = iterator->right;
		}
		else
		{
			iterator = iterator->left;
		}
	}
	return end;
}
/*---------------------------------------------------------------------------*/
size_t BSTCount(const bst_t *bst)
{
	size_t counter = 0;
	bst_iter_t iterator = NULL;
	bst_iter_t end = NULL;
	
	assert(bst);
	
	if(NULL == getRoot((bst_t*)bst))
	{
		return 0;
	}
	end = BSTEnd(bst);
	iterator = BSTBegin(bst);
	++counter;
	
	while(!BSTIsIterEqual(BSTNext(iterator), end))
	{
		iterator = BSTNext(iterator);
		++counter;
	}
	return counter;
}
/*----------------------------------------------------------------------------*/
bst_iter_t BSTBegin(const bst_t *bst)
{
	bst_iter_t iterator = NULL;
	bst_iter_t end = NULL;
	bst_t *tree = NULL;
	tree = (bst_t*)bst;
	assert(bst);
	end = BSTEnd(tree);
	iterator = getRoot(tree);
	
	while(!BSTIsIterEqual(BSTPrev(iterator), end))
	{
		iterator = BSTPrev(iterator);
	}
	return iterator;
}

bst_iter_t BSTEnd(const bst_t *bst)
{
	assert(bst);
	return bst->end;
}
/*----------------------------------------------------------------------------*/
bst_iter_t BSTPrev(bst_iter_t iter)
{
	bst_iter_t iterator;
	assert(iter);
	iterator = iter;
	
	if(hasLeftChild(iterator))
	{
		iterator = iterator->left;
		while(NULL != iterator->right)
		{
			iterator = iterator->right;
		}
		return iterator;
	}
	else
	{
		while((NULL != (iterator->parent)->parent) && (!isRightChild(iterator)))
		{
			iterator = iterator->parent;
		}
		return iterator->parent;
	}
}
/*----------------------------------------------------------------------------*/
bst_iter_t BSTNext(bst_iter_t iter)
{

	bst_iter_t iterator;
	assert(iter);
	iterator = iter;
	
	if(hasRightChild(iterator))
	{
		iterator = iterator->right;
		while(NULL != iterator->left)
		{
			iterator = iterator->left;
		}
		return iterator;
	}
	else
	{
		while((NULL != iterator->parent) && (!isLeftChild(iterator)))
		{
			iterator = iterator->parent;
		}
		return iterator->parent;
	}
}
/*----------------------------------------------------------------------------*/
int BSTIsIterEqual(bst_iter_t iter1, bst_iter_t iter2)
{
	return iter1 == iter2;
}

/*----------------Utilities---------------------------------------------------*/
bst_node_t *CreateNode(void *data)
{
	bst_node_t* node = (bst_node_t*)malloc(sizeof(bst_node_t));
	if(NULL == node)
	{
		return NULL;
	}
	node->data = data;
	node->parent = NULL;
	node->left = NULL;
	node->right = NULL;
	return node;
}
int isLeftChild(bst_iter_t iter)
{
	assert(iter);
	return BSTIsIterEqual((iter->parent)->left, iter);
}
int isRightChild(bst_iter_t iter)
{
	assert(iter);
	return BSTIsIterEqual((iter->parent)->right, iter);
}
int hasRightChild(bst_iter_t iter)
{
	assert(iter);
	return (NULL != (iter->right));
}
int hasLeftChild(bst_iter_t iter)
{
	assert(iter);
	return (NULL != (iter->left));
}
int isLeaf(bst_iter_t iter)
{
	assert(iter);
	return ((!hasRightChild(iter)) && (!hasLeftChild(iter)));
	
}
int hasOneChild(bst_iter_t iter)
{
	assert(iter);
	return ((!hasLeftChild(iter)) != (!hasRightChild(iter)));
}
void Inorder(bst_iter_t root)
{
	if(NULL == root)
	{
		return;
	}
	else
	{
		Inorder(root->left);
		printf("\n -%d- \n", *(int*)root->data);
		Inorder(root->right);
	}
}
void Preorder(bst_iter_t root)
{
	if(NULL == root)
	{
		return;
	}
	else
	{
		printf("\n -%d- \n", *(int*)root->data);
		Preorder(root->left);
		Preorder(root->right);
	}
}
bst_iter_t getRoot(bst_t *bst)
{
	bst_iter_t root = NULL;
	assert(bst);
	if(BSTIsEmpty(bst))
	{
		return NULL;
	}
	root = (bst->end)->left;
	return root;
}

void printTreeUtil(bst_iter_t root, int space)
{
	size_t i = 0;
	if(NULL == root)
	{
		return;
	}
	
	space += 10;
	
	printTreeUtil(root->right, space);
	printf("\n");
	for(i = 10; i < space; i++)
	{
		printf(" ");
	}
	printf("%d\n", *(int*)root->data);
	printTreeUtil(root->left, space);
}
void print2D(bst_iter_t root)
{
	printTreeUtil(root, 0);
}
/*----------------End of Utilities----------------------------------------*/







