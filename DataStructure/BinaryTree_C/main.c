#include <stdio.h>

#define TRUE 1
#define FALSE -1

typedef int ElemType; 
typedef int BOOL;

typedef struct _BinaryTreeNode
{
	ElemType elem;
	struct _BinaryTreeNode* left;
	struct _BinaryTreeNode* right;
}BinareTreeNode;

void InitBinaryTree()
{
	
}

void ShowBinaryTree()
{

}

void InsertBinaryTreeNode()
{

}

BOOL SearchBinaryTreeNode()
{
	return FALSE;
}

void DeleteBinaryTreeNode()
{

}

void DestroyBinaryTree()
{

}

int main()
{
	BinareTreeNode* pHeadNode = malloc(sizeof(BinareTreeNode));
	InitBinaryTree();
	InsertBinaryTreeNode();
	SearchBinaryTreeNode();
	DeleteBinaryTreeNode();
	ShowBinaryTree();
	DestroyBinaryTree();
	printf("binary tree journey!\n");
	return 0;
}