#include <stdio.h>

#define TRUE 1
#define FALSE -1

typedef char ElemType; 
typedef int BOOL;

typedef struct _BinaryTreeNode
{
	ElemType elem;
	struct _BinaryTreeNode* left;
	struct _BinaryTreeNode* right;
}BinareTreeNode;

//First Order Visit
void InitBinaryTree(BinareTreeNode* pHeadNode)
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