#include "Stack.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

NODE* GenerateNewNode(void* pParam)
{
    NODE* pNode = (NODE*)malloc(sizeof(NODE));
	memset(pNode, 0, sizeof(NODE));
    pNode->pData = pParam;

    return pNode;
}

void* DeleteNodeAtHead(STACK_INFO* pStack)
{
    if(pStack->pHead == NULL) return NULL;

    NODE* pDelete = pStack->pHead;
    void* pData = pDelete->pData;
    pStack->pHead = pStack->pHead->next;
    pStack->nSize--;

    free(pDelete);

    return pData;
}

void InitStack(STACK_INFO* pStack)
{
    pStack->pHead = NULL;
    pStack->nSize = 0;
}

void InsertNodeAtHead(STACK_INFO* pStack, void* pParam)
{
    NODE* pNode = GenerateNewNode(pParam);
	pNode->next = pStack->pHead;
	pStack->pHead = pNode;
    pStack->nSize++;
}


void Push(STACK_INFO* pStack, void* pParam)
{
    InsertNodeAtHead(pStack, pParam);
}    

void* Pop(STACK_INFO* pStack)
{
    return DeleteNodeAtHead(pStack);
}

void* Top(STACK_INFO* pStack)
{
    return pStack->pHead->pData;
}

int IsEmpty(STACK_INFO* pStack)
{
    return pStack->pHead == NULL;
}

void PrintStack(STACK_INFO* pStack, void (*pfPrint)(void*))
{
    printf("\nPrintStack Start\n");
    NODE* pTemp = pStack->pHead;
    while(pTemp != NULL)
    {
        pfPrint(pTemp->pData);
        pTemp = pTemp->next;
    }
    printf("\nPrintStack End\n\n");
}

void ReversePrintStack(STACK_INFO* pStack, NODE* pTemp, void (*pfPrint)(void*))
{
    if(pTemp == NULL) return;
    ReversePrintStack(pStack, pTemp->next, pfPrint);
    pfPrint(pTemp->pData);
}

unsigned int StackSize(STACK_INFO* pStack)
{
    return pStack->nSize;
}