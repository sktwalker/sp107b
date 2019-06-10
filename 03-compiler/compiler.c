#include <assert.h>
#include "compiler.h"

int E();
void STMT();
void BLOCK();
void IF();

int tempIdx = 0, labelIdx = 0;

#define nextTemp() (tempIdx++)
#define nextLabel() (labelIdx++)
#define emit printf

int isNext(char *set) 
{
  char eset[SMAX], etoken[SMAX];
  sprintf(eset, " %s ", set);//將字串set轉為eset
  sprintf(etoken, " %s ", tokens[tokenIdx]);//將第tokenIdx個tokens放入etoken
  return (tokenIdx < tokenTop && strstr(eset, etoken) != NULL);//確定eset內含有etoken並且tokenIdx不為結束字元
}

int isEnd() 
{
  return tokenIdx >= tokenTop;//索引超出範圍
}

char *next() 
{
  // printf("token[%d]=%s\n", tokenIdx, tokens[tokenIdx]);
  return tokens[tokenIdx++];//跳到下一個token
}

char *skip(char *set) 
{
  if (isNext(set)) //若eset內含有etoken並且tokenIdx不為結束字元
  {
    return next();//回傳下個token的位置
  } 
  else
  {
    printf("skip(%s) got %s fail!\n", set, next());//否則錯誤
    assert(0);
  }
}

// F = (E) | Number | Id
int F() {
  int f;
  if (isNext("("))// '(' E ')'
  { 
    next(); // (
    f = E();
    next(); // )
  } 
  else { // Number | Id
    f = nextTemp();
    char *item = next();
    emit("t%d = %s\n", f, item);//t(nextTemp) = next()
  }
  return f;
}

// E = F (op E)*
int E() {
  int i1 = F();
  while (isNext("+ - * / & | ! < > =")) //確定有下列符號時
  {
    char *op = next();
    int i2 = E();
    int i = nextTemp();
    emit("t%d = t%d %s t%d\n", i, i1, op, i2);//t(nextTemp) = t(F()) "+ - * / & | ! < > =" t(E())
    i1 = i;
  }
  return i1;
}

// ASSIGN = id '=' E;
void ASSIGN() {
  char *id = next();
  skip("=");//若有=則token+1
  int e = E();
  skip(";");//若有;則token+1
  emit("%s = t%d\n", id, e);//id = t(E())
}

// while (E) STMT
void WHILE() {
  int whileBegin = nextLabel();
  int whileEnd = nextLabel();
  emit("(L%d)\n", whileBegin);
  skip("while");
  skip("(");//(
  int e = E();
  emit("if not T%d goto L%d\n", e, whileEnd);
  skip(")");//)
  STMT();
  emit("goto L%d\n", whileBegin);
  emit("(L%d)\n", whileEnd);
}

void IF() {
  int elseBegin = nextLabel();
  int ifEnd = nextLabel();
  skip("if");
  skip("(");//(
  int e = E();
  skip(")");//)
  emit("ifnot t%d goto L%d\n", e, elseBegin);
  STMT();
  emit("goto L%d\n", ifEnd);
  if(isNext("else")) {
    emit("(L%d)\n", elseBegin);
    skip("else");
    STMT();
  }
  emit("(L%d)\n", ifEnd);
}

void STMT() {
  if (isNext("while"))
    return WHILE();
  else if (isNext("if"))
    IF();
  else if (isNext("{"))
    BLOCK();
  else
    ASSIGN();
}

void STMTS() {
  while (!isEnd() && !isNext("}")) {
    STMT();
  }
}

// { STMT* }
void BLOCK() {
  skip("{");
  STMTS();
  skip("}");
}

void PROG() {
  STMTS();
}

void parse() {
  printf("============ parse =============\n");
  tokenIdx = 0;
  PROG();
}