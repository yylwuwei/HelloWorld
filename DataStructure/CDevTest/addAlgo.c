
//
//�ڴ�й¶(OK)���쳣����(OK)��C��C++������(OK)��ʹ�ð���������(OK)��
//������ĸ����(OK)�� Ӣ���ƴ������(OK)���ظ�����(OK)��ģ�黯(OK)��ȱ��ע��

#include "addAlgo.h"

int GetSum(char* pStrNum1, char* pStrNum2, char* pStrNumResult)
{
	int lenStrNum1 = strlen(pStrNum1);
	int lenStrNum2 = strlen(pStrNum2);
	int lenStrNumResult = lenStrNum1 >= lenStrNum2 ? (lenStrNum1+2) : (lenStrNum2+2) ;
	int i = 0;
	int carry = 0;
	char singleResult = '\0'; 

	//�����������Ƿ�Ϸ�������Ϊ�ա��ַ���Χ0~9
	if (!(CheckNumString(pStrNum1)==RET_OK && CheckNumString(pStrNum2)==RET_OK))
	{
		return RET_ERR;
	}

	//�ַ�������
	ReverseNumString(pStrNum1);
	ReverseNumString(pStrNum2);

	for (i = 0; i < lenStrNumResult; i++)
	{
		pStrNumResult[i] = '\0';
	}

	//ִ�е�ѭ������Ϊ�ϴ������ַ����ĳ���
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
				//��������λ�ˣ�Ҳ�������һ��ѭ������ֱ�Ӳ������λ��1
				pStrNumResult[i+1] = '1';
			}
			else
			{
				//�н�λ���Ҳ������һ��ѭ���������ý�λʹ��
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
	//��Ҫ�࿪��һ���ռ䣬���ڱ����ַ���������
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



