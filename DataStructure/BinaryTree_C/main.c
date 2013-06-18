#include <stdio.h>
#include <malloc.h>

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

//First Order Visit to create
void CreateBinaryTree(BinareTreeNode* pNode)
{
	ElemType elem;
	scanf("%c", &elem);
	if ('#' == elem)
	{
		pNode = NULL;
	}
	else
	{
		pNode = (BinareTreeNode*)malloc(sizeof(BinareTreeNode));
		pNode->elem = elem;
		printf("%c\n",elem);
		CreateBinaryTree(pNode->left);
		CreateBinaryTree(pNode->right);
	}
}

void ShowBinaryTree()
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
	BinareTreeNode* pHeadNode = NULL;
	CreateBinaryTree(pHeadNode);
	SearchBinaryTreeNode();
	DeleteBinaryTreeNode();
	ShowBinaryTree();
	DestroyBinaryTree();
	printf("binary tree journey!\n");
	return 0;
}