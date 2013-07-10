// GraphOption.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <list>
#include <queue>
#include <stack>

using namespace std;

const int VEX_NUM = 4;
bool visited[VEX_NUM];

typedef struct _MatrixGraph 
{
	int arcNum;
	char vex[VEX_NUM];
	int arc[VEX_NUM][VEX_NUM];
}MatrixGraph;

void CreateMatrixGraph(MatrixGraph& matrixGraphObj)
{
	int i,j;

	for (i = 0; i < VEX_NUM; i++)
		for (j = 0; j < VEX_NUM; j++)
			matrixGraphObj.arc[i][j] = 0;
	
	cout << "please input vexnode info: " << endl;
	for (i = 0; i < VEX_NUM; i++)
	{
		cin >> matrixGraphObj.vex[i];
	}

	cout << "please input arcNum: " << endl;
	cin >> matrixGraphObj.arcNum;

	cout << "please input arc begin and end info: " << endl;
	for (i = 0; i < matrixGraphObj.arcNum; i++)
	{
		int bV,eV;
		cin >> bV >> eV;
		matrixGraphObj.arc[bV-1][eV-1] = 1;
	}
}

void PrintMatrixGraph(MatrixGraph& matrixGraphObj)
{
	int i,j;
	cout << "print matrix graph: " << endl;
	for (i = 0; i < VEX_NUM; i++)
	{
		for (j = 0; j < VEX_NUM; j++)
			cout << matrixGraphObj.arc[i][j] << " ";
		cout << endl;
	}
}

void VisitVexNode(char vNode)
{
	cout << vNode << endl;
}

int FindFirstVexNode(MatrixGraph& matrixGraphObj, int vOrder)
{
	for(int i = 0; i < VEX_NUM; i++)
	{
		if (matrixGraphObj.arc[vOrder][i] != 0)
		{
			return i;
		}
	}
	return -1;
}

int FindNextVexNode(MatrixGraph& matrixGraphObj, int vOrder, int w)
{
	for (int i = w+1; i < VEX_NUM; i++)
	{
		if (matrixGraphObj.arc[vOrder][i] != 0)
		{
			return i;
		}
	}
	return -1;
}

void ImplDFSMatrixGraph(MatrixGraph& matrixGraphObj, int vOrder)
{
	VisitVexNode(matrixGraphObj.vex[vOrder]);
	visited[vOrder] = true;
	//search all next vex node and select a node to traverse which is not visited
	int w = -1;
	for (w = FindFirstVexNode(matrixGraphObj, vOrder); w >= 0; w=FindNextVexNode(matrixGraphObj, vOrder, w))
	{
		if (!visited[w])
		{
			ImplDFSMatrixGraph(matrixGraphObj, w);
		}
	}
}

void DFSMatrixGraph(MatrixGraph& matrixGraphObj)
{
	int i;
	for (i = 0; i < VEX_NUM; i++)
	{
		visited[i] = false;
	}
	for (i = 0; i < VEX_NUM; i++)
	{
		if (!visited[i])
		{
			ImplDFSMatrixGraph(matrixGraphObj, i);
		}
	}
}

void BFSMatrixGraph(MatrixGraph& matrixGraphObj)
{
	int i;
	for (i = 0; i < VEX_NUM; i++)
	{
		visited[i] = false;
	}
	queue<char> vexQueue;
	for (i = 0; i < VEX_NUM; i++)
	{
		if (!visited[i])
		{
			VisitVexNode(matrixGraphObj.vex[i]);
			visited[i] = true;
			vexQueue.push(matrixGraphObj.vex[i]);
			int w = -1;
			while(!vexQueue.empty())
			{
				vexQueue.pop();
				for (w = FindFirstVexNode(matrixGraphObj, i); w >= 0; w = FindNextVexNode(matrixGraphObj, i , w))
				{
					if (!visited[w])
					{
						visited[w] = true;
						VisitVexNode(matrixGraphObj.vex[w]);
						vexQueue.push(matrixGraphObj.vex[w]);
					}
				}			
			}
		}
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	MatrixGraph matrixGraphObj;
	CreateMatrixGraph(matrixGraphObj);
	PrintMatrixGraph(matrixGraphObj);
	//DFSMatrixGraph(matrixGraphObj);
	BFSMatrixGraph(matrixGraphObj);
	return 0;
}