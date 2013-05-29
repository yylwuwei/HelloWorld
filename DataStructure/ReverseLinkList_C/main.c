//
//reverse list
//
//Q1: printf character, change line ?
//

#include <stdio.h>

typedef struct _Node
{
	char element;
	struct _Node* pNext;
}Node;

void PrintLinkList(Node* pHead)
{
	Node* pNode = pHead->pNext;
	printf("\nlink list: \n");
	while(pNode != NULL)
	{
		printf("%c", pNode->element);
		pNode = pNode->pNext;
	}
	printf("\n");
}

void CreateLinkList(Node* pHead)
{
	char tempElem = ' ';
	Node* pTempNode = NULL;
	Node* pEnd = NULL;
	while (scanf("%c", &tempElem))
	{
		fflush(stdin);
		if (tempElem != '#')
		{
			pTempNode = (Node *)malloc(sizeof(Node));
			pTempNode->element = tempElem;
			pTempNode->pNext = NULL;
			if (pHead->pNext == NULL)
			{
				pHead->pNext = pTempNode;
			}
			else
			{
				pEnd->pNext = pTempNode;
			}
			pEnd = pTempNode;			
		}
		else
		{
			return;
		}
	}
}

void ReverseLinkList(Node *pHead)
{
	Node *p1, *p2, *p3;
	int i = 0;
	if (NULL == pHead || NULL == pHead->pNext)
	{
		return;
	}
	p1 = pHead;
	p2 = p1->pNext;
	p3 = p2->pNext;
	while(p3 != NULL)
	{
		p2->pNext = p1;
		if (0 == i)
		{
			p2->pNext = NULL;
			++i;
		}
		p1 = p2;
		p2 = p3;
		p3 = p3->pNext;
	}
	p2->pNext = p1;
	pHead->pNext = p2;
}

Node * ReverseLinkList2(Node *pHead)
{
	Node *pTempHead = pHead;
	printf("%x\n", &(pHead->element));
	if (NULL == pHead || NULL == pHead->pNext)
	{
		return pHead;
	}
	pTempHead = ReverseLinkList2(pHead->pNext);
	pHead->pNext->pNext = pHead;
	pHead->pNext = NULL;
	return pTempHead;
}

void FreeLinkList(Node *pHead)
{
	Node *pTempHead = pHead->pNext;
	Node *p1 = NULL;
	while(NULL != pTempHead)
	{
		p1 = pTempHead;
		pTempHead = pTempHead->pNext;
		free(p1);
	}
	pHead->pNext = NULL;
	printf("\nFree link list is ok.\n\n");
}

int main()
{
	Node* pHead = (Node *)malloc(sizeof(Node));
	pHead->element = ' ';
	pHead->pNext = NULL;

	//create a link list
	CreateLinkList(pHead);

	//print a link list
	PrintLinkList(pHead);
	
	//reverse link list
	ReverseLinkList(pHead);
	//ReverseLinkList2(pHead);

	//print a link list
	PrintLinkList(pHead);

	//free memory all
	FreeLinkList(pHead);	

	return 0;
}