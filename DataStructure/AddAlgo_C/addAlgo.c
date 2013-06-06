
//
//内存泄露(OK)、异常机制(OK)、C与C++风格混淆(OK)、使用阿拉伯数字(OK)、
//单个字母命名(OK)、 英语和拼音混淆(OK)、重复代码(OK)、模块化(OK)、缺少注释

#include "addAlgo.h"

int GetSum(char* pStrNum1, char* pStrNum2, char* pStrNumResult)
{
	int lenStrNum1 = strlen(pStrNum1);
	int lenStrNum2 = strlen(pStrNum2);
	int lenStrNumResult = lenStrNum1 >= lenStrNum2 ? (lenStrNum1+2) : (lenStrNum2+2) ;
	int i = 0;
	int carry = 0;
	char singleResult = '\0'; 

	//检查输入参数是否合法：不能为空、字符范围0~9
	if (!(CheckNumString(pStrNum1)==RET_OK && CheckNumString(pStrNum2)==RET_OK))
	{
		return RET_ERR;
	}

	//字符串逆序
	ReverseNumString(pStrNum1);
	ReverseNumString(pStrNum2);

	for (i = 0; i < lenStrNumResult; i++)
	{
		pStrNumResult[i] = '\0';
	}

	//执行的循环次数为较大数字字符串的长度
	for (i = 0; i < lenStrNumResult-2; i++)
	{
		singleResult = '\0'; 
		if (i < lenStrNum1 && i < lenStrNum2)
		{
			singleResult = pStrNum1[i]+(pStrNum2[i]-'0')+carry;
		}
		else if(i >= lenStrNum1 && i < lenStrNum2)
		{
			singleResult = pStrNum2[i]+carry;
		}
		else if (i < lenStrNum1 && i >= lenStrNum2)
		{
			singleResult = pStrNum1[i]+carry;
		}

		if (singleResult > '9')
		{
			pStrNumResult[i] = singleResult-10;
			if (i == lenStrNumResult-3)
			{
				//如果是最高位了，也就是最后一次循环，则直接补在最高位补1
				pStrNumResult[i+1] = '1';
			}
			else
			{
				//有进位，且不是最后一次循环，则设置进位使用
				carry = 1;
			}	
		}
		else
		{
			pStrNumResult[i] = singleResult;
			carry = 0;
		}
	}
	ReverseNumString(pStrNumResult);
	return RET_OK;
}

int CheckNumString(char* pStrNum)
{
	int i = 0;

	if (pStrNum == NULL)
	{
		return RET_ERR;
	}

	for (i = 0; i < strlen(pStrNum); i++)
	{
		if (!(pStrNum[i] >= '0' && pStrNum[i] <= '9'))
		{
			return RET_ERR;
		}
	}

	return RET_OK;
}

void ReverseNumString(char* pStrNum)
{
	//需要多开辟一个空间，用于保存字符串结束符
	int len = strlen(pStrNum)+1;
	char* tempStr = (char *)malloc(len * sizeof(char));
	int i = 0;
	int j = 0;

	for (i = 0; i < len; i++)
	{
		tempStr[i] = '\0';
	}

	for (i = 0; i < len; i++)
	{
		tempStr[i] = pStrNum[i];
	}
	for (i = len-2; i >= 0; i--)
	{
		pStrNum[j++] = tempStr[i];
	}

	free(tempStr);
}



