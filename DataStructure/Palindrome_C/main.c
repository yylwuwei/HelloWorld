//
//��Ŀ�����ַ�����������ַ����ĳ���
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

	//�����ַ���
	if (lenStr < 1)
	{
		return -1;
	}

	//������Ҫ������ַ���
	for (i = 0; i < lenStr; i++)
	{
		//����������wxw
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

		//����������abba
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