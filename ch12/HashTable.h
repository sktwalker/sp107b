#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "Array.h"

typedef struct {// �@�Ӱt����� 
  char *key;
  void *data;
} Entry;

Entry* EntryNew(char *key, void *data);//�@�ӷs���� 
int EntryCompare(Entry *e1, Entry *e2);//�����Ӭ��� 

int hash(char *key, int range);//����� 

#define HashTable Array

HashTable* HashTableNew(int size);//�إ������ 
void HashTableFree(HashTable *table);//�M������� 
void HashTablePut(HashTable *table, char *key, void *data);//��@�ӷs���� 
void *HashTableGet(HashTable *table, char *key);//�o������� 
void HashTableEach(HashTable *table, FuncPtr1 f);//�C�ӳ�f 
Array* HashTableToArray(HashTable *table);//��}�C(arr) 
void HashTableTest();

#endif
