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
}BinareTreeNode, *BiTree;

void PrintNode(ElemType elem)
{
	printf("%c ", elem);
}

//First Order Visit to create
BinareTreeNode* PreOrderCreateBinaryTree(BinareTreeNode* pNode)
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
		//printf("%c\n",elem);
		pNode->left = PreOrderCreateBinaryTree(pNode->left);
		pNode->right = PreOrderCreateBinaryTree(pNode->right);
	}
	return pNode;
}

// void PreOrderCreateBiTree2(BiTree& T)
// {
// 	ElemType elem;
// 	scanf("%c", &elem);
// 	if ('#' == elem)
// 	{
// 		T = NULL;
// 	}
// 	else
// 	{
// 		T = (BinareTreeNode *)malloc(sizeof(BinareTreeNode));
// 		T->elem = elem;
// 		PreOrderCreateBiTree2(T->left);
// 		PreOrderCreateBiTree2(T->right);
// 	}
// }

void PreOrderTraverse(BinareTreeNode* pNode, void(* Visit)(ElemType elem))
{
	if (NULL != pNode)
	{
		Visit(pNode->elem);
		PreOrderTraverse(pNode->left, PrintNode);
		PreOrderTraverse(pNode->right, PrintNode);
	}
}

int main()
{
	BinareTreeNode* pHeadNode = NULL;
	//ABD##E##C##
	pHeadNode = PreOrderCreateBinaryTree(pHeadNode);
	PreOrderTraverse(pHeadNode, PrintNode);
	printf("\nbinary tree journey!\n");
	return 0;
}