#pragma once

// Data Structure
typedef struct NODE {
    // Data
	void* pData;

    // Structure
	struct NODE* next;
} NODE;

void* DeleteNodeAtHead();
void FreeNode(NODE* pDelete);
NODE* GenerateNewNode(void* pParam);
void InsertNodeAtHead();
int IsEmpty();
void Push(void* pParam);
void* Pop();
void* Top();
int IsEmpty();
void PrintStack(void (*pfPrint)(void*));
void ReversePrintStack(NODE* pTemp, void (*pfPrint)(void*));
unsigned int StackSize();