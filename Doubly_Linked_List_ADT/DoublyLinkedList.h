#pragma once

// Data Structure
typedef struct NODE {
    // Data
	void* pData;

    // Structure
    struct NODE* prev;
	struct NODE* next;
} NODE;

typedef struct LIST_INFO {
    NODE* pHead;
    NODE* pTail;
    int nSize;
} LIST_INFO;

// Declaration
int AppendNode(LIST_INFO* pListData, NODE* pDstNode, void* pParam);
int AppendNodeAt(LIST_INFO* pListData, int idx, void* pParam);
void AppendNodeAtTail(LIST_INFO* pListData, void* pParam);

int DeleteNode(LIST_INFO* pListData, NODE* pDelete);
int DeleteNodeAt(LIST_INFO* pListData, int idx);

void FreeNode(NODE* pNode);
NODE* GenerateNewNode(void* pParam);

int GetListLength(LIST_INFO* pListData);
int GetListSize(LIST_INFO* pListData);
NODE* GetNodeAt(LIST_INFO* pListData, int idx);

void InitList(LIST_INFO* pListData);

void InsertNode(LIST_INFO* pListData, NODE* pDstNode, void* pParam);
int InsertNodeAt(LIST_INFO* pListData, int idx, void* pParam);
void InsertNodeAtHead(LIST_INFO* pListData, void* pParam);

int IsListEmpty();

void ReleaseList(LIST_INFO* pListData);
void ReverseList(LIST_INFO* pListData);