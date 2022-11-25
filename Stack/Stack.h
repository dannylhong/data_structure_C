#pragma once

// Data Structure
typedef struct NODE {
    // Data
	void* pData;

    // Structure
	struct NODE* next;
} NODE;

NODE* GenerateNewNode(void* pParam);

typedef struct STACK_INFO {
    NODE* pHead;
    unsigned nSize;
} STACK_INFO;

void* DeleteNodeAtHead(STACK_INFO* pStack);
void FreeNode(STACK_INFO* pStack, NODE* pDelete);
void InitStack(STACK_INFO* pStack);
void InsertNodeAtHead(STACK_INFO* pStack, void* pParam);
int IsEmpty(STACK_INFO* pStack);
void Push(STACK_INFO* pStack, void* pParam);
void* Pop(STACK_INFO* pStack);
void* Top(STACK_INFO* pStack);
int IsEmpty(STACK_INFO* pStack);
void PrintStack(STACK_INFO* pStack, void (*pfPrint)(void*));
void ReversePrintStack(STACK_INFO* pStack, NODE* pTemp, void (*pfPrint)(void*));
unsigned StackSize(STACK_INFO* pStack);