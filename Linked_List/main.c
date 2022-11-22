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

int IsEmpty()
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
	if(IsEmpty()) printf("[%p] List is empty\n", g_pHead);
	putchar('\n');
}

void PrintListRec(NODE* pTmp)
{
	if (pTmp == NULL)
	{
		printf("head[%p] , tail[%p]\n",
				g_pHead, g_pTail);
		return;
	}
	printf("[%p] %s, next[%p]\n",
			pTmp, pTmp->szData, pTmp->next);
	PrintListRec(pTmp->next);
}

void InsertAtHead(char* pszData)
{
	NODE* pNode = (NODE*)malloc(sizeof(NODE));
	memset(pNode, 0, sizeof(NODE));
	strcpy(pNode->szData, pszData);

	if(IsEmpty()) g_pTail = pNode;
	pNode->next = g_pHead;
	g_pHead = pNode;
}

void AppendAtTail(char* pszData)
{
	NODE* pNode = (NODE*)malloc(sizeof(NODE));
	memset(pNode, 0, sizeof(NODE));
	strcpy(pNode->szData, pszData);

	if(IsEmpty()) g_pHead = pNode;
	else		  g_pTail->next = pNode;
	g_pTail = pNode;

#if 0 //when not using g_pTail
	if(IsEmpty())
	{
		g_pHead = pNode;
		// pNode->next = NULL; //implied in memset
		return;
	}

	NODE* pTmp = g_pHead;
	while (pTmp->next != NULL)
		pTmp = pTmp->next;

    pTmp->next = pNode;
    // pNode->next = NULL; //implied in memset
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
	NODE* pPre;
	while (pCur != NULL)
	{
		if (strcmp(pCur->szData, pszData) == 0)
		{
			printf("DeleteData():[%p] %s next[%p]\n", 
					pCur, pCur->szData, pCur->next);
			if (pCur == g_pHead) g_pHead = pCur->next;
			else                 pPre->next = pCur->next;
			
			if (pCur == g_pTail){
				if (g_pTail == g_pHead) // If the only one element is being deleted...
					g_pTail = NULL;
				else
					g_pTail = pPre;	
			} 

			free(pCur);
			return 1;
		}
		pPre = pCur;
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

void ReverseListRec(NODE * pTmp){
    if(pTmp->next == NULL)
    {
		g_pTail = g_pHead;
        g_pHead = pTmp;
        return;
    }
    ReverseListRec(pTmp->next);
    pTmp->next->next = pTmp;
    pTmp->next = NULL;
}

int main()
{
	puts("*** InsertAtHead() ***");
	InsertAtHead("TEST01");
	InsertAtHead("TEST02");
	InsertAtHead("TEST03");
	PrintList();

	DeleteData("TEST01");
	PrintList();
	DeleteData("TEST02");
	PrintList();
	DeleteData("TEST03");
	PrintList();

	puts("*** AppendAtTail() ***");
	AppendAtTail("TEST01");
	AppendAtTail("TEST02");
	AppendAtTail("TEST03");
	PrintList();

	DeleteData("TEST01");
	PrintList();
	DeleteData("TEST02");
	PrintList();
	DeleteData("TEST03");
	PrintList();

	puts("*** InsertAtHead() ***");
	InsertAtHead("TEST01");
	InsertAtHead("TEST02");
	InsertAtHead("TEST03");
	PrintList();
	puts("*** ReverseList() ***");
	ReverseList();
	PrintListRec(g_pHead);

	puts("*** ReverseListRec() ***");
	ReverseListRec(g_pHead);
	PrintListRec(g_pHead);

	ReleaseList();
	return 0;
}