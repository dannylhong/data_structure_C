#include "Stack.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

NODE* g_pHead = NULL;
unsigned int g_nSize = 0;

void* DeleteNodeAtHead()
{
    if(g_pHead == NULL) return NULL;

    NODE* pDelete = g_pHead;
    void* pData = pDelete->pData;
    g_pHead = g_pHead->next;
    g_nSize--;

    free(pDelete);

    return pData;
}

NODE* GenerateNewNode(void* pParam)
{
    NODE* pNode = (NODE*)malloc(sizeof(NODE));
	memset(pNode, 0, sizeof(NODE));
    pNode->pData = pParam;

    return pNode;
}

void InsertNodeAtHead(void* pParam)
{
    NODE* pNode = GenerateNewNode(pParam);
	pNode->next = g_pHead;
	g_pHead = pNode;
    g_nSize++;
}


void Push(void* pParam)
{
    InsertNodeAtHead(pParam);
}    

void* Pop()
{
    return DeleteNodeAtHead();
}

void* Top()
{
    return g_pHead->pData;
}

int IsEmpty()
{
    return g_pHead == NULL;
}

void PrintStack(void (*pfPrint)(void*))
{
    printf("\nPrintStack Start\n");
    NODE* pTemp = g_pHead;
    while(pTemp != NULL)
    {
        pfPrint(pTemp->pData);
        pTemp = pTemp->next;
    }
    printf("\nPrintStack End\n\n");
}

void ReversePrintStack(NODE* pTemp, void (*pfPrint)(void*))
{
    if(pTemp == NULL) return;
    ReversePrintStack(pTemp->next, pfPrint);
    pfPrint(pTemp->pData);
}

unsigned int StackSize()
{
    return g_nSize;
}