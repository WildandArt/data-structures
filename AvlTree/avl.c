
#include <stdlib.h> /*malloc,free*/
#include "avl.h" /*API*/

void printTree(avl_node_t *root, int space);
avl_node_t *GetRoot(avl_t *avl);




struct avl
{
	void *param;
	avl_compare_func_t cmp;
	avl_node_t *root;
	size_t height;
};
struct avl_node
{
	void *data;
	struct avl_node *left;
	struct avl_node *right;
	size_t height;
	
};

typedef int(*traversal_funcs)(avl_node_t *, avl_action_func_t, void *);


static avl_node_t *RecFuncInsert(avl_node_t *iter, void *data, avl_t *avl ,avl_node_t *new_node);
static size_t RecFuncCount(avl_node_t *node);
static void PostOrderRemoval(avl_node_t *node);
static void *RecFuncAVLFind(avl_node_t *node, void *data, avl_t *avl);
static int PreOrder(avl_node_t *root, avl_action_func_t act, void *arg);
static int InOrder(avl_node_t *root, avl_action_func_t act, void *arg);
static int PostOrder(avl_node_t *root, avl_action_func_t act, void *arg);
static int CalcBalanceFactor(avl_node_t *node);

static avl_node_t *RecFuncFreeMin(avl_node_t *root);
static avl_node_t *RecFuncFindMin(avl_node_t *root);
static avl_node_t *RecFuncAVLRemove(avl_node_t *root, void *data, avl_t *avl);

static avl_node_t *LeftRotate(avl_node_t *z);
static avl_node_t *RightRotate(avl_node_t *y);
static size_t Height(avl_node_t *node);
static avl_node_t *CreateNode(void *data);
static size_t Max(size_t height1, size_t height2);
 
static traversal_funcs array_func[3] = {PreOrder, InOrder ,PostOrder};


/*------------------------------------------------------------------*/
avl_t *AVLCreate(avl_compare_func_t cmp, void *param)
{
	avl_t *avl = (avl_t *)malloc(sizeof(avl_t));
	if(!avl)
	{
		return NULL;
	}
	
	avl->param = param;
	avl->cmp = cmp;
	avl->root = NULL;
	avl->height = 0;
	
	return (avl);
}
/*------------------------------------------------------------------*/
void AVLDestroy(avl_t *avl)
{
	PostOrderRemoval(avl->root);
	free(avl);
}
static void PostOrderRemoval(avl_node_t *node)
{
	if(!node)
	{
		return;
	}

	PostOrderRemoval(node->left);
	PostOrderRemoval(node->right);
	free(node);
}
/*------------------------------------------------------------------*/
void *AVLRemove(avl_t *avl, const void *data)
{
	avl_node_t *result = RecFuncAVLRemove(avl->root, (void *)data, avl);
	avl->root = result;
	avl->height = Height(avl->root);
	if(result)
	{
		return((void*)data);
	}
	return NULL;
}

/*--------------------------------------------------------------------------------*/
static avl_node_t *RecFuncAVLRemove(avl_node_t *root, void *data, avl_t *avl)
{
	int balance = 0;
	avl_node_t *temp = NULL;
	if(!root)
	{
		return NULL;
	}
	
	if((avl->cmp(root->data, data, avl->param) > 0))
	{
		root->left = RecFuncAVLRemove(root->left, data, avl);
	}
	else if((avl->cmp(root->data, data, avl->param) < 0))
	{
		root->right = RecFuncAVLRemove(root->right, data, avl);
	}
	else
	{
		if((!root->left) && (!root->right))
		{
			free(root);
			return NULL;
		}
		else if((!root->left))
		{
			temp = root->right;
			free(root);
			return temp;
		}
		else if((!root->right))
		{
			temp = root->left;
			free(root);
			return temp;
		}
		/*add here else*/
		temp = RecFuncFindMin(root->right);
		root->data = temp->data;
		root->right = RecFuncFreeMin(root->right);
	}
	
	if (!root)
	{
		return root;
	}
	
	root->height = 1 + Max(Height(root->left), Height(root->right));
	
	balance = CalcBalanceFactor(root);
	
	if(balance > 1 && avl->cmp(root->left->data, data, avl->param) > 0)
	{
		return (RightRotate(root));
	}
	if(balance > 1 && avl->cmp(root->left->data, data, avl->param) < 0) 
	{
		root->left = LeftRotate(root->left);
		return(RightRotate(root));
	}
	if(balance < -1 && avl->cmp(root->right->data, data, avl->param) < 0) 
	{
		return (LeftRotate(root));
	}
	if(balance < -1 && avl->cmp(root->right->data, data, avl->param) > 0) 
	{
		root->right = RightRotate(root->right);
		return(LeftRotate(root));
	}
	
	return root;
}

/*------------------------------------------------------------------*/
int AVLInsert(avl_t *avl, const void *data)
{
	avl_node_t *new_node = CreateNode((void*)data); 
	
	if(AVLIsEmpty(avl))
	{
		avl->root = new_node;
		return 0;
	}
	avl->root = RecFuncInsert((avl->root), (void *)data, avl, new_node);
	avl->height = Height(avl->root);
	
	return (0);
}
avl_node_t *CreateNode(void *data)
{
	avl_node_t *new_node = (avl_node_t*)malloc(sizeof(avl_node_t)); 
	if(NULL == new_node)
	{
		return NULL;
	}
	new_node->data = (void*)data;
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->height = 1;
	
	return new_node;
}
/*------------------------------------------------------------------*/
static avl_node_t *RecFuncInsert(avl_node_t *iter, void *data, \
 avl_t *avl, avl_node_t *new_node)
{

	int balance = 0;
	
	if(!iter)
	{
		return (new_node);
	}
	
	if(avl->cmp(iter->data, data, avl->param) > 0)
	{
		iter->left = RecFuncInsert(iter->left, data, avl, new_node);
	}
	else
	{
		iter->right = RecFuncInsert(iter->right, data, avl, new_node);
	}
	
	iter->height = 1 + Max(Height(iter->left), Height(iter->right));
	
	balance = CalcBalanceFactor(iter);
	
	if(balance > 1 && avl->cmp(iter->left->data, data, avl->param) > 0)
	{
		return (RightRotate(iter));
	}
	if(balance > 1 && avl->cmp(iter->left->data, data, avl->param) < 0)
	{
		iter->left = LeftRotate(iter->left);
		return(RightRotate(iter));
	}
	if(balance < -1 && avl->cmp(iter->right->data, data, avl->param) < 0)
	{
		return (LeftRotate(iter));
	}
	if(balance < -1 && avl->cmp(iter->right->data, data, avl->param) > 0)
	{
		iter->right = RightRotate(iter->right);
		return(LeftRotate(iter));
	}
	
	return iter;
}
/*------------------------------------------------------------------*/
static avl_node_t *RightRotate(avl_node_t *y)
{
	avl_node_t *x = y->left;
	avl_node_t *T3 = x->right;
	
	x->right = y;
	y->left = T3;
	
	y->height = Max(Height(y->left),Height(y->right)) + 1;
	x->height = Max(Height(x->left),Height(x->right)) + 1;
	return x;
}
/*------------------------------------------------------------------*/
static avl_node_t *LeftRotate(avl_node_t *z)
{
	avl_node_t *y = z->right;
	avl_node_t *T2 = y->left;
	
	y->left = z;
	z->right = T2;
	
	z->height = Max(Height(z->left),Height(z->right)) + 1;
	
	y->height = Max(Height(y->left),Height(y->right)) + 1;
	
	return y;
}
/*------------------------------------------------------------------*/
static size_t Height(avl_node_t *node)
{
	if(!node)
	{
		return 0;
	}
	return node->height;
}
/*------------------------------------------------------------------*/
static int CalcBalanceFactor(avl_node_t *node)
{
	if(NULL == node)
	{
		return 0;
	}
	return Height(node->left) - Height(node->right);
}
/*------------------------------------------------------------------*/
static size_t Max(size_t height1, size_t height2)
{
	return height1 > height2 ? height1 : height2;
}
/*------------------------------------------------------------------*/

size_t AVLHeight(const avl_t *avl)
{
	return (avl->height);
}

/*------------------------------------------------------------------*/

size_t AVLCount(const avl_t *avl)
{
	return(RecFuncCount(avl->root));
}

/*------------------------------------------------------------------*/

int AVLIsEmpty(const avl_t *avl)
{
	return(NULL == avl->root);
}
/*------------------------------------------------------------------*/

void *AVLFind(const avl_t *avl, const void *data)
{
	return (RecFuncAVLFind(avl->root,(void *)data, (void*)avl));
}

static void *RecFuncAVLFind(avl_node_t *node, void *data, avl_t *avl)
{
	void *find_data = NULL;
	if(!node)
	{
		return NULL;
	}
	if((avl->cmp(node->data, data, avl->param) == 0))
	{
		return(node->data);
	}
	else if((avl->cmp(node->data, data, avl->param) > 0))
	{
		find_data = RecFuncAVLFind(node->left, data, avl);
	}
	else if((avl->cmp(node->data, data, avl->param) < 0))
	{
		find_data = RecFuncAVLFind(node->right, data, avl);
	}
	return find_data;
}
/*------------------------------------------------------------------*/

int AVLForEach(avl_t *avl, avl_action_func_t act, void *arg, order_t order)
{
	return (array_func[order](avl->root, act, arg));
}


/*------------------------------------------------------------------*/
static size_t RecFuncCount(avl_node_t *node)
{
	size_t count = 0;
	if(!node)
	{
		return 0;
	}
	count += RecFuncCount(node->left);
	count += RecFuncCount(node->right);
	count++;
	return count;
}

/*------------------------------------------------------------------*/
static int PreOrder(avl_node_t *root, avl_action_func_t act, void *arg)
{
	int result = 0;
	if(!root)
	{
		return result;
	}
	if(act(root->data,arg))
	{
		return 1;
	}
	result = PreOrder(root->left, act, arg);
	if(result != 0)
	{
		return result;
	}
	result = PreOrder(root->right, act, arg);
	return result;
}

/*------------------------------------------------------------------*/
static int InOrder(avl_node_t *root, avl_action_func_t act, void *arg)
{
	int result = 0;
	if(!root)
	{
		return result;
	}
	result = InOrder(root->left, act, arg);
	
	if(result != 0)
	{
		return result;
	}
	if(act(root->data, arg))
	{
		return 1;
	}
	result = InOrder(root->right, act, arg);
	return result;
}

/*------------------------------------------------------------------*/
static int PostOrder(avl_node_t *root, avl_action_func_t act, void *arg)
{
	int result = 0;
	if(!root)
	{
		return result;
	}
	result = PostOrder(root->left, act, arg);
	
	if(result != 0)
	{
		return result;
	}	
	result = PostOrder(root->right, act, arg);
	if(result != 0)
	{
		return result;
	}
	if(act(root->data, arg))
	{
		result = 1;
		return result;
	}
	return result;
} 

/*------------------------------------------------------------------*/
static avl_node_t *RecFuncFindMin(avl_node_t *root)
{
	if(!root->left)
	{
		return root;
	}
	RecFuncFindMin(root->left);
	return root;
}

/*------------------------------------------------------------------*/
static avl_node_t *RecFuncFreeMin(avl_node_t *root)
{
	avl_node_t *temp = NULL;
	if(!root)
	{
		return NULL;
	}
	if(!root->left)
	{
		temp = root->right;
		free(root);
		return temp;
	}
	root->left = RecFuncFreeMin(root->left);
	return (root);
}


/*------------------------------------------------------------------*/
/*testing functions*/
/*void printTree(avl_node_t *root, int space)
{
	size_t i = 0;
	if(NULL == root)
	{
		return;
	}

	space += 10;

	printTree(root->right, space);
	printf("\n");
	for(i = 10; i < space; i++)
	{
		printf(" ");
	}
	printf("%d\n",(int*)root->data);
	printTree(root->left, space);
}

avl_node_t *GetRoot(avl_t *avl)
{
	return(avl->root);
}*/
/*------------------------------------------------------------------*/


















