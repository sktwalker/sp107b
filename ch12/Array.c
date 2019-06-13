#include <stdlib.h>
#include <string.h>
#include "Array.h"
//free若不用會消耗記憶體資源 
void ArrayTest() {//測試資料 
  char *names[] = { "John", "Mary", "George", "Bob" };
  Array *array = ArrayNew(1);
  int i;
  for (i=0; i<4; i++)
    ArrayAdd(array, names[i]);//4位元 
  ArrayEach(array, strPrintln);
  printf("ArrayPop()=%s\n", ArrayPop(array));
  printf("ArrayLast()=%s\n", ArrayLast(array));
  for (i=0; i<4; i++) {
    int arrayIdx = ArrayFind(array, names[i], strcmp);
    printf("ArrayFind(%s)=%d\n", names[i], arrayIdx);
  }
  ArrayEach(array, strPrintln);
  ArrayFree(array, NULL);
}

Array* ArrayNew(int size) {// 
  Array *array = ObjNew(Array, 1);//動態陣列的資料結構 
  array->count = 0;
  array->size = size;
  array->item = ObjNew(void*, array->size);
  return array;
}

void ArrayFree(Array *array, FuncPtr1 freeFuncPtr) {
  if (array == NULL) return;
  if (freeFuncPtr != NULL)
    ArrayEach(array, freeFuncPtr);
  ObjFree(array->item);
  ObjFree(array);
}

void ArrayAdd(Array *array, void *item) {
  ASSERT(array->count <= array->size);//若個數大於大小則終止 
  if (array->count == array->size) {
    int newSize = array->size*2;//大小增為兩倍 
    void **newItems = ObjNew(void*, newSize);
    memcpy(newItems, array->item, array->size*sizeof(void*));//將舊item複製size個到newItems
//  printf("array grow from %d to %d\n", array->count, newSize);
    ObjFree(array->item);
    array->item = newItems;
    array->size = newSize;
  }
  array->item[array->count++] = item;
//printf("add item = %s\n", item);
}

void ArrayPush(Array *array, void *item) {
  ArrayAdd(array, item);
}

void* ArrayPop(Array *array) {
  ASSERT(array->count>0);
  return array->item[--(array->count)];
}

void* ArrayPeek(Array *array) {
  return ArrayLast(array);
}

void* ArrayLast(Array *array) {
  ASSERT(array->count > 0);
  return array->item[array->count-1];
}

Array* split(char *str, char *spliter, SplitMode mode) {//keep/remove 
  Array *tokens = ArrayNew(10);
  int si, tokenCount=0;
  int begin=0, ti = 0;
  for (si=0; si<=strlen(str); si++) {
      if (str[si]=='\0' || strMember(str[si], spliter)) {
        int len = si-begin;
        if (len > 0)
          ArrayAdd(tokens, newSubstr(str, begin, len));
        if (mode == KEEP_SPLITER)
          ArrayAdd(tokens, newSubstr(str, si, 1));
//      printf("token1=%s token2=%s\n", tokens->item[ti-2], tokens->item[ti-1]);
        begin = si+1;
      }
  }
  return tokens;
}

int ArrayFind(Array *array, void *data, FuncPtr2 fcmp) {
  int i;
  for (i=0; i<array->count; i++)
    if (fcmp(array->item[i], data)==0)
      return i;
  return -1;
}

void ArrayEach(Array *array, FuncPtr1 f) {//f為單一參數指標 
  int i;
  for (i=0; i<array->count; i++)
    f(array->item[i]);//array中每個item以f處理 
}
