#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define MAX_STR_LEN 64

typedef struct NODE {
	char szData[MAX_STR_LEN];

	struct NODE* next;
} NODE;

NODE* g_pHead = NULL;
NODE* g_pTail = NULL;

int IsListEmpty()
{
	if (g_pHead == NULL)
		return 1;

	return 0;
}

void PrintList(void)
{
	NODE* pTmp = g_pHead;
	while (pTmp != NULL)
	{
		printf("[%p] %s, next[%p]\n",
				pTmp, pTmp->szData, pTmp->next);
		pTmp = pTmp->next;
	}
	printf("head[%p] , tail[%p]\n",
				g_pHead, g_pTail);
	if(IsListEmpty()) puts("List is empty");
	putchar('\n');
}

void PrintListRecursion(NODE* pTmp)
{
	if (pTmp == NULL)
	{
		printf("head[%p] , tail[%p]\n",
				g_pHead, g_pTail);
		return;
	}
	printf("[%p] %s, next[%p]\n",
			pTmp, pTmp->szData, pTmp->next);
	PrintListRecursion(pTmp->next);
}

NODE* GenerateNewNode(const char* pszData)
{
	NODE* pNode = (NODE*)malloc(sizeof(NODE));
	memset(pNode, 0, sizeof(NODE));
	strcpy(pNode->szData, pszData);

	return pNode;
}

void InsertNodeAtHead(const char* pszData)
{
	NODE* pNode = GenerateNewNode(pszData);

	if(IsListEmpty()) g_pTail = pNode;
	pNode->next = g_pHead;
	g_pHead = pNode;
}

void AppendNodeAtTail(const char* pszData)
{
	NODE* pNode = GenerateNewNode(pszData);

#if 1 //when using g_pTail

	if(IsListEmpty()) g_pHead = pNode;
	else		  g_pTail->next = pNode;
	g_pTail = pNode;

#else 0 //when not using g_pTail
	if(IsListEmpty())
	{
		g_pHead = pNode;
		return;
	}

	NODE* pTmp = g_pHead;
	while (pTmp->next != NULL)
		pTmp = pTmp->next;

    pTmp->next = pNode;
#endif	
}

void ReleaseList(void)
{
	printf("\nReleaseList()\n");
	NODE* pTmp = g_pHead;
	while (pTmp != NULL) {
		NODE* pDelete = pTmp;
		pTmp = pTmp->next;

		printf("Delete: [%p] %s\n", pDelete, pDelete->szData);
		free(pDelete);
	}
    g_pHead = NULL;
	g_pTail = NULL;
}

int DeleteData(char* pszData)
{
	NODE* pCur = g_pHead;
	NODE* pPrev;
	while (pCur != NULL)
	{
		if (strcmp(pCur->szData, pszData) == 0)
		{
			printf("DeleteData():[%p] %s next[%p]\n", 
					pCur, pCur->szData, pCur->next);
			if (pCur == g_pHead) g_pHead = pCur->next;
			else                 pPrev->next = pCur->next;
			
			if (pCur == g_pTail){
				if (g_pTail == g_pHead) // If the only one element is being deleted...
					g_pTail = NULL;
				else
					g_pTail = pPrev;	
			} 

			free(pCur);
			return 1;
		}
		pPrev = pCur;
		pCur = pCur->next;
	}

	return 0;
}

void ReverseList(){
	g_pTail = g_pHead;

    NODE * pCur, * pPrev, * pNext;
    pCur = g_pHead;
    pPrev = NULL;
    while(pCur != NULL)
    {
        pNext = pCur->next;
        pCur->next = pPrev;
        pPrev = pCur;
        pCur = pNext;
    }
    g_pHead = pPrev;
}

void ReverseListRecursion(NODE * pTmp){
    if(pTmp->next == NULL)
    {
		g_pTail = g_pHead;
        g_pHead = pTmp;
        return;
    }
    ReverseListRecursion(pTmp->next);
    pTmp->next->next = pTmp;
    pTmp->next = NULL;
}

int main()
{
	puts("*** InsertNodeAtHead() ***");
	InsertNodeAtHead("TEST01");
	InsertNodeAtHead("TEST02");
	InsertNodeAtHead("TEST03");
	PrintList();

	DeleteData("TEST01");
	PrintList();
	DeleteData("TEST02");
	PrintList();
	DeleteData("TEST03");
	PrintList();

	puts("*** AppendNodeAtTail() ***");
	AppendNodeAtTail("TEST01");
	AppendNodeAtTail("TEST02");
	AppendNodeAtTail("TEST03");
	PrintList();

	DeleteData("TEST01");
	PrintList();
	DeleteData("TEST02");
	PrintList();
	DeleteData("TEST03");
	PrintList();

	puts("*** InsertNodeAtHead() ***");
	InsertNodeAtHead("TEST01");
	InsertNodeAtHead("TEST02");
	InsertNodeAtHead("TEST03");
	PrintList();
	puts("*** ReverseList() ***");
	ReverseList();
	PrintListRecursion(g_pHead);

	puts("*** ReverseListRecursion() ***");
	ReverseListRecursion(g_pHead);
	PrintListRecursion(g_pHead);

	ReleaseList();
	return 0;
}