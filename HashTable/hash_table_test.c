#include "hash_table.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LINE_LEN 50
void TestCreate();
void TestInsert();
void TestDictionary();

int CompareInt(void *data, void *new_data)
{
	return *(int*)data == *(int*)new_data;
}
int CompareStr(void *data, void *new_data)
{
	return strcmp((char*)data, (char*)new_data);
}
size_t BasicHash(const void *key)
{
	return (size_t)key % 10;
}
size_t StringHash(const void *key)
{
	size_t value = 0;
	size_t power_coeff = 1;
	while(*(char*)key)
	{
		value += (*(char*)key)*power_coeff;
		power_coeff *= 5;
		++(*(char **)&key);
	}
	return value % MAX_LINE_LEN;
}

int main()
{
	
 	/*TestCreate();
	TestInsert();*/
	/*TestDictionary();*/
	
	

	return (0);
}
void TestDictionary()
{
	FILE *fp = NULL;
	char line[MAX_LINE_LEN];
	char *new_line = NULL;
	void *result = NULL;
	hash_table_t *table = HashTableCreate(50 , StringHash, CompareStr);
	
	fp = fopen("/usr/share/dict/words", "r");
	if(NULL == fp)
	{
		printf("error");
	}
	while(fgets(line, MAX_LINE_LEN, fp)!= NULL)
	{
		new_line = (char*)malloc(51);
		if(NULL == new_line)
		{
			printf("malloc");
		}
		strcpy(new_line, line);
		assert(0 == HashTableInsert(table, (void*)new_line));
		puts(new_line);
	}
	
	printf("\n table size : %lu \n", HashTableSize(table));
	
	printf("\nEnter word: \n");
   	scanf("%s", line);
   	printf("scanf line: %s", line);
   	result = HashTableFind(table, (void*)line);
   	if(NULL != result)
   	{
   		printf("\nfound \n");
   	}
	fclose(fp);
	
}


void TestCreate()
{
	size_t size = 15;
	hash_table_t *table = HashTableCreate(size , StringHash, CompareInt);
	HashTableDestroy(table);
}
void TestInsert()
{
	hash_table_t *table = NULL;
	size_t size = 10;
	table = HashTableCreate(size, StringHash, CompareInt);
	printf("\n status %d \n", HashTableInsert(table, (void*)9)); 
	
	HashTableDestroy(table);
}










