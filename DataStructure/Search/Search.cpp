// Search.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int binary_search(int array[],int n,int value)
{
	if (n <= 0)
	{
		return -1;
	}

	//sort(array, array+n-1);

	int minA = 0;
	int maxA = n-1;
	int mid = 0;
	while (minA <= maxA) 
	{
		mid = (minA+maxA)/2;
		if (value < array[mid])
		{
			maxA = mid-1;
		}
		else if (value > array[mid])
		{
			minA = mid+1;
		}
		else
		{
			return mid;
		}
	}
	return -1;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int array[] = {5,6,88,9,10,11,12,13,19,19,26};
	int ret = -2;
	ret = binary_search(array, sizeof(array)/sizeof(int), 19);
	cout << ret << endl;	

	return 0;
}

