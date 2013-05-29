#include "addAlgo.h"

int main()
{
	char strNum1[] = "12332";
	char strNum2[] = "996";

	int lenStrNum1 = strlen(strNum1);
	int lenStrNum2 = strlen(strNum2);
	int lenStrNumResult = lenStrNum1 >= lenStrNum2 ? (lenStrNum1+2) : (lenStrNum2+2) ;
	char* pStrNumResult = (char *)malloc(lenStrNumResult * sizeof(char));
	int ret = GetSum(strNum1, strNum2, pStrNumResult);
	if (ret != RET_ERR)
	{
		printf("%s\n", pStrNumResult);
	}
	else
	{
		printf("error number! \n");
	}
	free(pStrNumResult);

	return 0;
}