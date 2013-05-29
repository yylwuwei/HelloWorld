//
//题目：求字符串中最长回文字符串的长度
//

#include <stdio.h>

int GetMax(int n1, int n2)
{
	return n1 > n2 ? n1 : n2;
}

int GetMaxNumPalindrome(char* pStr)
{
	int retNum = 1;
	int tempNum = 1;
	int i = 0, j = 0;
	int lenStr = strlen(pStr);

	//检查空字符串
	if (lenStr < 1)
	{
		return -1;
	}

	//遍历需要处理的字符串
	for (i = 0; i < lenStr; i++)
	{
		//处理回文情况wxw
		tempNum = 1;
		for(j = 1; i-j >= 0 && i+j < lenStr; j++)
		{
				if (pStr[i+1] == pStr[i-1])
				{
					tempNum += 2;
				}
				else
				{
					break;
				}
		}
		retNum = GetMax(retNum, tempNum);

		//处理回文情况abba
		tempNum = 0;
		for (j = 0; i-j >= 0 && i+1+j < lenStr; j++)
		{
			if (pStr[i-j] == pStr[i+1+j])
			{
				tempNum += 2;
			}
			else
			{
				break;
			}
		}
		retNum = GetMax(retNum, tempNum);
	}
	return retNum;
}

int main()
{
	char* pStr = "ww";
	printf("max num: %d \n", GetMaxNumPalindrome(pStr));
	return 0;
}