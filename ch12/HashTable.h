#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "Array.h"

typedef struct {// 一個配對紀錄 
  char *key;
  void *data;
} Entry;

Entry* EntryNew(char *key, void *data);//一個新紀錄 
int EntryCompare(Entry *e1, Entry *e2);//比較兩個紀錄 

int hash(char *key, int range);//雜湊值 

#define HashTable Array

HashTable* HashTableNew(int size);//建立雜湊表 
void HashTableFree(HashTable *table);//清除雜湊表 
void HashTablePut(HashTable *table, char *key, void *data);//放一個新雜湊 
void *HashTableGet(HashTable *table, char *key);//得到雜湊表 
void HashTableEach(HashTable *table, FuncPtr1 f);//每個都f 
Array* HashTableToArray(HashTable *table);//轉陣列(arr) 
void HashTableTest();

#endif
