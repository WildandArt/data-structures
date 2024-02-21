#include <assert.h>
#include <stdlib.h>
#include "dll.h"
#include "hash_table.h"


struct hash_table
{
	hash_func_t hash_func;
	dll_t **elements;
	size_t size;
	hash_cmp_func_t cmp;
};

static dll_iter_t FindIterator(const hash_table_t *table, const void *data);

hash_table_t *HashTableCreate(size_t size, hash_func_t hash, hash_cmp_func_t cmp)
{
	size_t i = 0;
	size_t j = 0;
	hash_table_t *hash_table = (hash_table_t*)malloc(sizeof(hash_table_t));
	if( NULL == hash_table)
	{
		return NULL;
	}
	
	hash_table->elements = (dll_t **) malloc( sizeof(dll_t*) * size);
	
	if( NULL == hash_table->elements)
	{	
		free(hash_table);
		return NULL;
	}
	for(i = 0; i < size; ++i)
	{
		hash_table->elements[i] = DLLCreate();
		/*dangerous bug */
		if(NULL == hash_table->elements[i])
		{
			
			for(j = 0; j < i - 1; ++j)
			{
				DLLDestroy(hash_table->elements[i]);
			}

			free(hash_table->elements);
			free(hash_table);
			return NULL;
		}
	}
	hash_table->hash_func = hash;
	hash_table->cmp = cmp;
	hash_table->size = size;
	
	return hash_table;
}
void HashTableDestroy(hash_table_t *hash_table)
{
	size_t i = 0;
	if(NULL == hash_table)
	{
		return;
	}
	for(i = 0; i < hash_table->size; ++i)
	{
		DLLDestroy(hash_table->elements[i]);
	}
	free(hash_table->elements);
	free(hash_table);
}

int HashTableInsert(hash_table_t *table, void *data)
{
	dll_iter_t result = NULL;
	
	size_t index = table->hash_func(data) % table->size;
	
	dll_t *doubly_list = table->elements[index];
	
	result = DLLPushFront(doubly_list, data);
	
	if(DLLIterIsEqual(DLLEnd(doubly_list), result))
	{
		return 1;
	}
	return 0;
}
void HashTableRemove(hash_table_t *table, const void *data)
{
	dll_iter_t found = FindIterator(table, data);
	
	if(!DLLIterIsEqual(found, NULL)) 
	{
		DLLRemove(found);
	}
	return;
}

static dll_iter_t FindIterator(const hash_table_t *table, const void *data)
{
	dll_iter_t found = NULL;
	
	size_t index = (table->hash_func(data)) % table->size;
	dll_t *doubly_list = table->elements[index];
	
	found = DLLFind(DLLBegin(doubly_list), DLLEnd(doubly_list), table->cmp, (void*)data);
	
	if(DLLIterIsEqual(DLLEnd(doubly_list),found))
	{
		return NULL;
	}
	return found;
}
void *HashTableFind(const hash_table_t *table, const void *data)
{
	dll_iter_t found = FindIterator(table, data);
	if(!DLLIterIsEqual(found, NULL)) 
	{
		return DLLGetData(found);
	}
	return NULL;
}

size_t HashTableSize(const hash_table_t *table)
{

	size_t i = 0;
	size_t counter = 0;
	assert(table);
	for(i = 0; i < table->size; ++i)
	{
		counter += DLLCount(table->elements[i]);
	}
	return counter;
}

int HashTableIsEmpty(const hash_table_t *table)
{
	size_t i = 0;
	int status = 0;
	assert(table);
	for(i = 0; i < (table->size) && (status == 1); ++i)
	{
		status = DLLIsEmpty(table->elements[i]);
	}
	return (status == 1);
}


int HashForEach(hash_table_t *table, hash_action_func_t act, void *param)
{
	size_t i = 0;
	int status = 0;
	
	for(i = 0; i < (table->size) && status == 0; ++i)
	{
		status = DLLForEach(DLLBegin(table->elements[i]), DLLEnd(table->elements[i]), act, param);
	}
	return (status);
}









