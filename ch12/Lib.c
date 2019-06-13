#include "Lib.h"

char SPLITER[] = " \t\n\r~!@#$%^&*()_+{}:\"<>?-=[]|\\;',./";//特殊字元 
char SPACE[] = " \t\n\r";//空白 
char ALPHA[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";//英文字母 
char DIGIT[] = "0123456789";//數字 
char NAME_CHAR[] = "_0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";//字元 

// 記憶體配置函數 
int newMemoryCount = 0;
void* newMemory(int size) {
  void *ptr=malloc(size);//動態配置記憶體空間 
  assert(ptr != NULL);//size不可為0，故ptr不可為空 
  memset(ptr, 0, size);//將size大小的ptr字串覆蓋為0 
//  printf("memGet:%p\n", ptr);
  newMemoryCount++;
  return ptr;
}

int freeMemoryCount=0;
void freeMemory(void *ptr) {//記憶體清空 
//  printf("memFree:%p\n", ptr);
  free(ptr);
  freeMemoryCount++;
}

void checkMemory() {
  printf("newMemoryCount=%d freeMemoryCount=%d\n", newMemoryCount, freeMemoryCount);
}

// 檔案輸出入 
BYTE* newFileBytes(char *fileName, int *sizePtr) {
  FILE *file = fopen(fileName, "rb");
  fseek(file, 0 , SEEK_END);//檔案開頭 
  long size = ftell(file);//len of file 
  rewind(file);//指向文件開頭 
  BYTE *buffer = (char*) newMemory(size+1);//指向新記憶體配置空間 
  fread (buffer,size,1,file);// 讀到file 
  fclose(file);
  *sizePtr = size;
  return buffer;//回傳指標 
}

char* newFileStr(char *fileName) {
  int size;
  BYTE *buffer = newFileBytes(fileName, &size);//吃進buffer的字串 
  buffer[size] = '\0';//最末設為斷點 
  return (char*) buffer;
}

char *newStr(char *str) {
  char *rzStr = newMemory(strlen(str)+1);//分配str+1長度的新記憶區段 
  strcpy(rzStr, str);//將str內容複製到rzstr 
  return rzStr;
}

char *newSubstr(char *str, int i, int len) {
  char *rzStr = newMemory(len+1);//分配len+1度的新記憶區段 
  strSubstr(rzStr, str, i, len);//將rzstr變成str[i]開始len長度的字串 
  return rzStr;
}

// 字串函數 
void strPrint(void *data) {
  printf("%s ", data);//輸出自串 
}

void strPrintln(void *data) {
  printf("%s\n", data);//上面+換行 
}

BOOL strHead(char *str, char *head) { 
  return (strncmp(str, head, strlen(head))==0);// 比較str前是否為head字串 
}

BOOL strTail(char *str, char *tail) {
  int strLen = strlen(str), tailLen = strlen(tail);
  if (strLen < tailLen) return FALSE;
  return (strcmp(str+strLen-tailLen, tail)==0);//比尾 
}

int strCountChar(char *str, char *charSet) {//算字串字元數 
  int i, count=0;
  for (i=0; i<strlen(str); i++)
    if (strMember(str[i], charSet))
      count++;
  return count;
}

void strSubstr(char *substr, char *str, int i, int len) {
  strncpy(substr, &str[i], len);//自 str[i]複製len長度的字串到substr
  substr[len]='\0';//並在len長的substr設斷點 
}
 
BOOL strPartOf(char *token, char *set) {
  ASSERT(token != NULL && set != NULL);//兩指標位置不可為空 
  ASSERT(strlen(token) < 100);//token不可大於等於100 
  char ttoken[100];
  sprintf(ttoken, "|%s|", token);//ttoken為token開始之字串 
  return (strstr(set, ttoken)!=NULL);//set內是否有 ttoken
}

void strTrim(char *trimStr, char *str, char *set) {
  char *start, *stop;
  for (start = str; strMember(*start, set); start++);
  for (stop = str+strlen(str)-1; stop > str && strMember(*stop, set); stop--);
  if (start <= stop) {
    strncpy(trimStr, start, stop-start+1);
    trimStr[stop-start+1]='\0';
  } else
    strcpy(trimStr, "");
}

void strReplace(char *str, char *from, char to) {//換位 
  int i;
  for (i=0; i<strlen(str); i++)
    if (strMember(str[i], from))
      str[i] = to;
}

char tspaces[MAX_LEN];
char* strSpaces(int level) {
  assert(level < MAX_LEN);
  memset(tspaces, ' ', MAX_LEN);
  tspaces[level] = '\0';
  return tspaces;
}

void strToUpper(char *str) {
  int i;
  for (i = 0; i<strlen(str); i++)
    str[i] = toupper(str[i]);
}
