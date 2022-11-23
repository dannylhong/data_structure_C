#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define MAX_STR_LEN 64

typedef struct NODE {
	char szData[MAX_STR_LEN];

    struct NODE* prev;
	struct NODE* next;
} NODE;

NODE* g_pHead = NULL;
NODE* g_pTail = NULL;
int g_nSize = 0;

void PrintList(void)
{
	printf("PrintList():\n  g_nSize: %d\n  g_pHead[%p]\n", g_nSize, g_pHead);
	NODE* pTmp = g_pHead;
	while (pTmp != NULL)
	{
		printf("         [%14p] prev[%14p], %s, next[%14p]\n",
				pTmp, pTmp->prev, pTmp->szData, pTmp->next);
		pTmp = pTmp->next;
	}
    printf("  g_pTail[%p]\n\n", g_pTail);
}

void PrintListRecursion(NODE* pTmp)
{
	if (pTmp == NULL)
	{
		printf("g_nSize: %d, g_pHead[%p] , g_pTail[%p]\n\n",
				g_nSize, g_pHead, g_pTail);
		return;
	}
	printf("[%14p] prev[%14p], %s, next[%14p]\n",
				pTmp, pTmp->prev, pTmp->szData, pTmp->next);
	PrintListRecursion(pTmp->next);
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
    g_nSize = 0;
}

void ReleaseListRecursion(NODE* pTmp)
{
    if (pTmp == NULL)
    {
        g_pHead = NULL;
        g_pTail = NULL;
        g_nSize = 0;
    	printf("\nReleaseListRecursion()\n");
        return;
    }
    ReleaseListRecursion(pTmp->next);
    printf("Delete: [%p] %s\n", pTmp, pTmp->szData);
    free(pTmp);
}

NODE* FindNodeWithKey(const char* pszData)
{
	NODE* pTmp = g_pHead;
	while (pTmp != NULL)
    {
        if (strcmp(pTmp->szData, pszData) == 0)
		{
            return pTmp;
        }
		pTmp = pTmp->next;
    }
    return NULL;
}

int DeleteNode(NODE* pNode)
{
    if(pNode == NULL) return -1;

    // Link information of the node ahead
    if(pNode == g_pHead) g_pHead = pNode->next;
    else                 pNode->prev->next = pNode->next;

    // Link information of the node after
    if(pNode == g_pTail) g_pTail = pNode->prev;
    else                 pNode->next->prev = pNode->prev;

    printf("DeleteNode():\n         [%14p] prev[%14p], %s, next[%14p]\n\n",
				            pNode, pNode->prev, pNode->szData, pNode->next);

    free(pNode);
    g_nSize--;
    
	return 0;
}

int DeleteNodeWithName(const char* pszData)
{
	NODE* pNode = FindNodeWithKey(pszData);

    return DeleteNode(pNode);
}

int GetListSize()
{
    return g_nSize;
}

int GetListLength()
{
    return GetListSize();
}

int IsListEmpty()
{
    return GetListSize();
}

NODE* GetNodeAt(int idx)
{
    if(idx >= GetListSize()) return NULL;

    NODE* pTmp = g_pHead;
	while (idx-- > 0)
	{
        pTmp = pTmp->next;
    }
    return pTmp;
}

NODE* GenerateNewNode(const char* pszData)
{
    NODE* pNode = (NODE*)malloc(sizeof(NODE));
	memset(pNode, 0, sizeof(NODE));
	strcpy(pNode->szData, pszData);
    
    return pNode;
}

void InsertNode(NODE* pTmp, const char* pszData)
{
    NODE* pNode = GenerateNewNode(pszData);

    // Link information of the new node
    if(pTmp == NULL) pNode->prev = NULL;
    else             pNode->prev = pTmp->prev;
    pNode->next = pTmp;

    // Link information of the node ahead
    if(pTmp == g_pHead) g_pHead = pNode;
    else                pNode->prev->next = pNode;
    
    // Link information of the node after
    if(g_pTail == NULL) g_pTail = pNode;
    else                pNode->next->prev = pNode;
    
    g_nSize++;
}

int InsertNodeAt(int idx, const char* pszData)
{
    NODE* pTmp = GetNodeAt(idx);

    if(pTmp == NULL) return -1;
    
    InsertNode(pTmp, pszData);
    
    return 0;
}

int AppendNode(NODE* pTmp, const char* pszData)
{
    NODE* pNode = GenerateNewNode(pszData);

    // Link information of the new node
    if(pTmp == NULL) pNode->next = NULL;
    else             pNode->next = pTmp->next;
    pNode->prev = pTmp;

    // Link information of the node after
    if(pTmp == g_pTail) g_pTail = pNode;
    else                pNode->next->prev = pNode;
    
    // Link information of the node ahead
    if(g_pHead == NULL) g_pHead = pNode;
    else                pNode->prev->next = pNode;
    
    g_nSize++;
}

int AppendNodeAt(int idx, const char* pszData)
{
    NODE* pTmp = GetNodeAt(idx);

    if(pTmp == NULL) return -1;

    AppendNode(pTmp, pszData);

    return 0;
}

int DeleteNodeAt(int idx)
{
    NODE* pNode = GetNodeAt(idx);

    return DeleteNode(pNode);
}


void InsertNodeAtHead(const char* pszData)
{
    InsertNode(g_pHead, pszData);

    return;
}

void AppendNodeAtTail(const char* pszData)
{
    AppendNode(g_pTail, pszData);

    return;
}

void ReverseList()
{
    g_pTail = g_pHead;

    NODE * pCur, * pPrev, * pNext;
    pCur = g_pHead;
    pPrev = NULL;
    while(pCur != NULL)
    {
        pNext = pCur->next;
        pCur->next = pPrev;
        pCur->prev = pNext;
        pPrev = pCur;
        pCur = pNext;
    }
    g_pHead = pPrev;
}

void ReverseListRecursion(NODE * pTmp)
{
    if(pTmp->next == NULL)
    {
        pTmp->prev = NULL;
		g_pTail = g_pHead;
        g_pHead = pTmp;
        return;
    }
    ReverseListRecursion(pTmp->next);
    pTmp->next->next = pTmp;
    pTmp->prev = pTmp->next;
    pTmp->next = NULL;
}

int main()
{
    puts("*** InsertNodeAtHead() ***");
    InsertNodeAtHead("TEST01");
    InsertNodeAtHead("TEST02");
    InsertNodeAtHead("TEST03");
    PrintList();

    puts("*** AppendNodeAtTail() ***");
    AppendNodeAtTail("TEST04");
    AppendNodeAtTail("TEST05");
    AppendNodeAtTail("TEST06");
    PrintList();

    DeleteNodeWithName("TEST02");
    PrintList();
    DeleteNodeWithName("TEST04");
    PrintList();
    DeleteNodeWithName("TEST06");
    PrintList();
    DeleteNodeWithName("TEST01");
    PrintList();
    DeleteNodeWithName("TEST03");
    PrintList();
    DeleteNodeWithName("TEST05");
    PrintList();

    puts("*** AppendNodeAtTail() ***");
    AppendNodeAtTail("TEST04");
    AppendNodeAtTail("TEST05");
    AppendNodeAtTail("TEST06");
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

    puts("*** InsertNodeAt(3, \"TEST12\") ***");
    InsertNodeAt(3, "TEST12");
    PrintList();
    puts("*** InsertNodeAt(0, \"TEST10\") ***");
    InsertNodeAt(0, "TEST10");
    PrintList();
    puts("*** InsertNodeAt(6, \"TEST11\") ***");
    InsertNodeAt(6, "TEST11");
    PrintList();
    puts("*** AppendNodeAt(3, \"TEST13\") ***");
    AppendNodeAt(3, "TEST13");
    PrintList();
    puts("*** AppendNodeAt(0, \"TEST14\") ***");
    AppendNodeAt(0, "TEST14");
    PrintList();
    puts("*** AppendNodeAt(GetListLength()-1, \"TEST15\") ***");
    AppendNodeAt(GetListLength()-1, "TEST15");
    PrintList();

    puts("*** ReverseList() ***");
    ReverseList();
    PrintListRecursion(g_pHead);

    puts("*** ReverseListRecursion() ***");
    ReverseListRecursion(g_pHead);
    PrintListRecursion(g_pHead);

    DeleteNodeAt(3);
    PrintList();
    DeleteNodeAt(0);
    PrintList();
    DeleteNodeAt(GetListLength()-1);
    PrintList();

    ReleaseListRecursion(g_pHead);
    PrintList();

    return 0;
}