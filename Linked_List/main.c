#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define MAX_STR_LEN 64

typedef struct NODE {
	char szData[MAX_STR_LEN];
	struct NODE* next;
} NODE;

NODE* g_pHead = NULL;

void PrintList(void)
{
	NODE* pTmp = g_pHead;
	while (pTmp != NULL)
	{
		printf("[%p] %s, next[%p]\n",
			pTmp, pTmp->szData, pTmp->next);
		pTmp = pTmp->next;
	}

	putchar('\n');
}

int IsEmpty()
{
	if (g_pHead == NULL)
		return 1;

	return 0;
}

void InsertAtHead(char* pszData)
{
	NODE* pTmp = (NODE*)malloc(sizeof(NODE));
	memset(pTmp, 0, sizeof(NODE));
	strcpy(pTmp->szData, pszData);

	pTmp->next = g_pHead;
	g_pHead = pTmp;
}

int InsertAtTail(char* pszData)
{
	NODE* pTmp = g_pHead;
	while (pTmp->next != NULL)
		pTmp = pTmp->next;

	NODE* pNode = (NODE*)malloc(sizeof(NODE));
	memset(pNode, 0, sizeof(NODE));
	strcpy(pNode->szData, pszData);

	pTmp->next = pNode;
    pNode->next = NULL; //implied in memset
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
}

int FindData(char* pszData)
{
	NODE* pTmp = g_pHead;
	while (pTmp != NULL)
	{
		if (strcmp(pTmp->szData, pszData) == 0)
			return 1;
		pTmp = pTmp->next;
	}

	return 0;
}


int DeleteData(char* pszData)
{
	NODE* pCur = g_pHead->next;
	NODE* pPrev = g_pHead;
	while (pCur != NULL)
	{
		if (strcmp(pCur->szData, pszData) == 0)
		{
			printf("DeleteData(): %s\n", pCur->szData);
			pPrev->next = pCur->next;
			free(pCur);
			return 1;
		}

		pCur = pCur->next;
		pPrev = pPrev->next;
	}

	return 0;
}


int main()
{
	puts("*** InsertAtHead() ***");
	InsertAtHead("TEST01");
	InsertAtHead("TEST02");
	InsertAtHead("TEST03");
	PrintList();

	if (FindData("TEST01") == 1)
		printf("FindData(): TEST01 found\n");
	if (FindData("TEST02") == 1)
		printf("FindData(): TEST02 found\n");
	if (FindData("TEST03") == 1)
		printf("FindData(): TEST03 found\n");
	putchar('\n');

	DeleteData("TEST01");
	PrintList();
	DeleteData("TEST02");
	PrintList();
	DeleteData("TEST03");
	PrintList();

	puts("*** InsertAtTail() ***");
	InsertAtTail("TEST01");
	InsertAtTail("TEST02");
	InsertAtTail("TEST03");
	PrintList();


	if (FindData("TEST01") == 1)
		printf("FindData(): TEST01 found\n");
	if (FindData("TEST02") == 1)
		printf("FindData(): TEST02 found\n");
	if (FindData("TEST03") == 1)
		printf("FindData(): TEST03 found\n");
	putchar('\n');

	DeleteData("TEST01");
	PrintList();
	DeleteData("TEST02");
	PrintList();
	DeleteData("TEST03");
	PrintList();

	ReleaseList();
	return 0;
}