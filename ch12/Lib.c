#include "Lib.h"

char SPLITER[] = " \t\n\r~!@#$%^&*()_+{}:\"<>?-=[]|\\;',./";//�S��r�� 
char SPACE[] = " \t\n\r";//�ť� 
char ALPHA[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";//�^��r�� 
char DIGIT[] = "0123456789";//�Ʀr 
char NAME_CHAR[] = "_0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";//�r�� 

// �O����t�m��� 
int newMemoryCount = 0;
void* newMemory(int size) {
  void *ptr=malloc(size);//�ʺA�t�m�O����Ŷ� 
  assert(ptr != NULL);//size���i��0�A�Gptr���i���� 
  memset(ptr, 0, size);//�Nsize�j�p��ptr�r���л\��0 
//  printf("memGet:%p\n", ptr);
  newMemoryCount++;
  return ptr;
}

int freeMemoryCount=0;
void freeMemory(void *ptr) {//�O����M�� 
//  printf("memFree:%p\n", ptr);
  free(ptr);
  freeMemoryCount++;
}

void checkMemory() {
  printf("newMemoryCount=%d freeMemoryCount=%d\n", newMemoryCount, freeMemoryCount);
}

// �ɮ׿�X�J 
BYTE* newFileBytes(char *fileName, int *sizePtr) {
  FILE *file = fopen(fileName, "rb");
  fseek(file, 0 , SEEK_END);//�ɮ׶}�Y 
  long size = ftell(file);//len of file 
  rewind(file);//���V���}�Y 
  BYTE *buffer = (char*) newMemory(size+1);//���V�s�O����t�m�Ŷ� 
  fread (buffer,size,1,file);// Ū��file 
  fclose(file);
  *sizePtr = size;
  return buffer;//�^�ǫ��� 
}

char* newFileStr(char *fileName) {
  int size;
  BYTE *buffer = newFileBytes(fileName, &size);//�Y�ibuffer���r�� 
  buffer[size] = '\0';//�̥��]���_�I 
  return (char*) buffer;
}

char *newStr(char *str) {
  char *rzStr = newMemory(strlen(str)+1);//���tstr+1���ת��s�O�аϬq 
  strcpy(rzStr, str);//�Nstr���e�ƻs��rzstr 
  return rzStr;
}

char *newSubstr(char *str, int i, int len) {
  char *rzStr = newMemory(len+1);//���tlen+1�ת��s�O�аϬq 
  strSubstr(rzStr, str, i, len);//�Nrzstr�ܦ�str[i]�}�llen���ת��r�� 
  return rzStr;
}

// �r���� 
void strPrint(void *data) {
  printf("%s ", data);//��X�ۦ� 
}

void strPrintln(void *data) {
  printf("%s\n", data);//�W��+���� 
}

BOOL strHead(char *str, char *head) { 
  return (strncmp(str, head, strlen(head))==0);// ���str�e�O�_��head�r�� 
}

BOOL strTail(char *str, char *tail) {
  int strLen = strlen(str), tailLen = strlen(tail);
  if (strLen < tailLen) return FALSE;
  return (strcmp(str+strLen-tailLen, tail)==0);//��� 
}

int strCountChar(char *str, char *charSet) {//��r��r���� 
  int i, count=0;
  for (i=0; i<strlen(str); i++)
    if (strMember(str[i], charSet))
      count++;
  return count;
}

void strSubstr(char *substr, char *str, int i, int len) {
  strncpy(substr, &str[i], len);//�� str[i]�ƻslen���ת��r���substr
  substr[len]='\0';//�æblen����substr�]�_�I 
}
 
BOOL strPartOf(char *token, char *set) {
  ASSERT(token != NULL && set != NULL);//����Ц�m���i���� 
  ASSERT(strlen(token) < 100);//token���i�j�󵥩�100 
  char ttoken[100];
  sprintf(ttoken, "|%s|", token);//ttoken��token�}�l���r�� 
  return (strstr(set, ttoken)!=NULL);//set���O�_�� ttoken
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

void strReplace(char *str, char *from, char to) {//���� 
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
