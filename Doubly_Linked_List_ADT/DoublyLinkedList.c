#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "DoublyLinkedList.h"

int AppendNode(LIST_INFO* pListData, NODE* pDstNode, void* pParam)
{
    NODE* pNode = GenerateNewNode(pParam);

    // Link information of the new node
    if(pDstNode == NULL) pNode->next = NULL;
    else                 pNode->next = pDstNode->next;
    pNode->prev = pDstNode;

    // Link information of the node after
    if(pDstNode == pListData->pTail) pListData->pTail = pNode;
    else                             pNode->next->prev = pNode;
    
    // Link information of the node ahead
    if(pListData->pHead == NULL) pListData->pHead = pNode;
    else                         pNode->prev->next = pNode;
    
    pListData->nSize++;
}

int AppendNodeAt(LIST_INFO* pListData, int idx, void* pParam)
{
    NODE* pTmp = GetNodeAt(pListData, idx);

    if(pTmp == NULL) return -1;

    AppendNode(pListData, pTmp, pParam);

    return 0;
}

void AppendNodeAtTail(LIST_INFO* pListData, void* pParam)
{
    AppendNode(pListData, pListData->pTail, pParam);

    return;
}

int DeleteNode(LIST_INFO* pListData, NODE* pDelete)
{
    if(pDelete == NULL) return -1;

    // Link information of the node ahead
    if(pDelete == pListData->pHead) pListData->pHead = pDelete->next;
    else                            pDelete->prev->next = pDelete->next;

    // Link information of the node after
    if(pDelete == pListData->pTail) pListData->pTail = pDelete->prev;
    else                            pDelete->next->prev = pDelete->prev;

    printf("DeleteNode():\n         [%14p] prev[%14p], next[%14p]\n",
				        pDelete, pDelete->prev, pDelete->next);
    FreeNode(pDelete);
    pListData->nSize--;
    
	return 0;
}

int DeleteNodeAt(LIST_INFO* pListData, int idx)
{
    NODE* pNode = GetNodeAt(pListData, idx);

    return DeleteNode(pListData, pNode);
}

int DeleteNodeWithKey(LIST_INFO* pListData, void* pszKey, int (*pfCmpare)(void* , void*))
{
	NODE* pNode = FindNodeWithKey(pListData, pszKey, pfCmpare);

    return DeleteNode(pListData, pNode);
}

NODE* FindNodeWithKey(LIST_INFO* pListData, void* pszKey, int (*pfCmpare)(void* , void*))
{
	NODE* pTmp = pListData->pHead;
	while (pTmp != NULL)
    {
        if (pfCmpare(pTmp->pData, pszKey) == 0)
		{
            return pTmp;
        }
		pTmp = pTmp->next;
    }
    return NULL;
}

void FreeNode(NODE* pNode)
{
    free(pNode->pData);
    free(pNode);
}

//////////////////////////////////////////////////////////////////////////////////
// pParam: the caller is responsible for the memory allocation and initialization.
NODE* GenerateNewNode(void* pParam)
{
    NODE* pNode = (NODE*)malloc(sizeof(NODE));
	memset(pNode, 0, sizeof(NODE));
    pNode->pData = pParam;

    return pNode;
}

int GetListLength(LIST_INFO* pListData)
{
    return GetListSize(pListData);
}

int GetListSize(LIST_INFO* pListData)
{
    return pListData->nSize;
}


NODE* GetNodeAt(LIST_INFO* pListData, int idx)
{
    if(idx >= GetListSize(pListData)) return NULL;

    NODE* pTmp = pListData->pHead;
	while (idx-- > 0)
	{
        pTmp = pTmp->next;
    }
    return pTmp;
}

void InitList(LIST_INFO* pListData)
{
    pListData->pHead = NULL;
    pListData->pTail = NULL;
    pListData->nSize = 0;
}

void InsertNode(LIST_INFO* pListData, NODE* pDstNode, void* pParam)
{
    NODE* pNode = GenerateNewNode(pParam);

    // Link information of the new node
    if(pDstNode == NULL) pNode->prev = NULL;
    else                 pNode->prev = pDstNode->prev;
    pNode->next = pDstNode;

    // Link information of the node ahead
    if(pDstNode == pListData->pHead) pListData->pHead = pNode;
    else                             pNode->prev->next = pNode;
    
    // Link information of the node after
    if(pListData->pTail == NULL) pListData->pTail = pNode;
    else                         pNode->next->prev = pNode;
    
    pListData->nSize++;
}

int InsertNodeAt(LIST_INFO* pListData, int idx, void* pParam)
{
    NODE* pTmp = GetNodeAt(pListData, idx);

    if(pTmp == NULL) return -1;
    
    InsertNode(pListData, pTmp, pParam);
    
    return 0;
}

void InsertNodeAtHead(LIST_INFO* pListData, void* pParam)
{
    InsertNode(pListData, pListData->pHead, pParam);

    return;
}

int IsListEmpty(LIST_INFO* pListData)
{
    return GetListSize(pListData);
}

void PrintList(LIST_INFO* pListData, void (*pfPrint)(void*))
{
	printf("\nPrintList():\n  g_nSize: %d\n  g_pHead[%p]\n", pListData->nSize, pListData->pHead);
	NODE* pTmp = pListData->pHead;

	while (pTmp != NULL)
	{
        printf("         [%14p], prev[%14p], next[%14p]   ",
				        pTmp, pTmp->prev, pTmp->next);
        pfPrint(pTmp->pData);
		pTmp = pTmp->next;
	}
    printf("  g_pTail[%p]\n\n", pListData->pTail);
}

void ReleaseList(LIST_INFO* pListData)
{
	printf("\nReleaseList()\n");
	NODE* pTmp = pListData->pHead;
	while (pTmp != NULL) {
		NODE* pDelete = pTmp;
		pTmp = pTmp->next;

		printf("Delete: [%p]\n", pDelete);
		FreeNode(pDelete);
	}
    pListData->pHead = NULL;
	pListData->pTail = NULL;
    pListData->nSize = 0;
}

void ReverseList(LIST_INFO* pListData)
{
    pListData->pTail = pListData->pHead;

    NODE * pCur, * pPrev, * pNext;
    pCur = pListData->pHead;
    pPrev = NULL;
    while(pCur != NULL)
    {
        pNext = pCur->next;
        pCur->next = pPrev;
        pCur->prev = pNext;
        pPrev = pCur;
        pCur = pNext;
    }
    pListData->pHead = pPrev;
}