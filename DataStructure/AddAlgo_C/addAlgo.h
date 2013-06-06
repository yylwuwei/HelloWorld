#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define RET_OK 1
#define RET_ERR -1

int GetSum(char* pStrNum1, char* pStrNum2, char* pStrNumResult);
int CheckNumString(char* pStrNum);
void ReverseNumString(char* pStrNum);