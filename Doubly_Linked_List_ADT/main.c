#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "DoublyLinkedList.h"

// User Data
#define MAX_STR_LEN 64
typedef struct USER_DATA {
    //Member Variable
	char szName[MAX_STR_LEN];  // key
    char szPhone[MAX_STR_LEN]; // value
    
    //Member Function Pointer
    const char* (*GetKey)(struct USER_DATA*);
    const char* (*GetVal)(struct USER_DATA*);
} USER_DATA; // think of it as dictionary

int KeyCompare(void* pUserData, void* pszKey);

USER_DATA* GenerateNewData(const char* pszName, const char* pszPhone);
const char* GetKeyFromUserData(USER_DATA* pUser);
const char* GetValFromUserData(USER_DATA* pUser);

void PrintList(LIST_INFO* pListData);

int main()
{
    LIST_INFO userList01 = { 0 };
    InitList(&userList01);

    USER_DATA* pNewData = NULL;
    
    pNewData = GenerateNewData("Daniel Hong", "010-1234-1234");
    InsertNodeAtHead(&userList01, pNewData);
    PrintList(&userList01);
    
    pNewData = GenerateNewData("Samuel Hong", "010-4321-1234");
    InsertNodeAtHead(&userList01, pNewData);
    PrintList(&userList01);
    
    pNewData = GenerateNewData("Yoomin Hong", "010-4321-4321");
    AppendNodeAtTail(&userList01, pNewData);
    PrintList(&userList01);

    pNewData = GenerateNewData("Sarang Hong", "010-1234-5678");
    AppendNodeAt(&userList01, 0, pNewData);
    PrintList(&userList01);

    pNewData = GenerateNewData("Yeere Min", "010-4567-9876");
    InsertNodeAt(&userList01, 2, pNewData);
    PrintList(&userList01);

    ReverseList(&userList01);
    PrintList(&userList01);

    DeleteNodeWithKey(&userList01, "Samuel Hong", KeyCompare);
    PrintList(&userList01);
    DeleteNodeWithKey(&userList01, "Yoomin Hong", KeyCompare);
    PrintList(&userList01);
    DeleteNodeWithKey(&userList01, "Yeere Min", KeyCompare);
    PrintList(&userList01);

    ReverseList(&userList01);
    PrintList(&userList01);


    LIST_INFO userList02 = { 0 };
    InitList(&userList02);


    pNewData = GenerateNewData("Test01", "010-1234-1234");
    InsertNodeAtHead(&userList02, pNewData);
    pNewData = GenerateNewData("Test02", "010-4321-1234");
    InsertNodeAtHead(&userList02, pNewData);    
    pNewData = GenerateNewData("Test03", "010-4321-4321");
    AppendNodeAtTail(&userList02, pNewData);
    
    PrintList(&userList02);
    PrintList(&userList01);

    ReleaseList(&userList01);
    ReleaseList(&userList02);
    PrintList(&userList01);
    PrintList(&userList02);

    return 0;
}

USER_DATA* GenerateNewData(const char* pszName, const char* pszPhone)
{
    USER_DATA* pNewData = (USER_DATA*)malloc(sizeof(USER_DATA));
    memset(pNewData, 0, sizeof(USER_DATA));
    strcpy(pNewData->szName, pszName);
    strcpy(pNewData->szPhone, pszPhone);

    pNewData->GetKey = GetKeyFromUserData;
    pNewData->GetVal = GetValFromUserData;
    
    return pNewData;
}

const char* GetKeyFromUserData(USER_DATA* pUser)
{
    return pUser->szName;
}

const char* GetValFromUserData(USER_DATA* pUser)
{
    return pUser->szPhone;
}

int KeyCompare(void* pUserData, void* pszKey)
{
    USER_DATA* pData = pUserData;
    const char* (*pfGetKey)(USER_DATA*) = NULL;
    pfGetKey = pData->GetKey;

    return strcmp(pfGetKey(pData), (const char*)pszKey);
}

void PrintList(LIST_INFO* pListData)
{
	printf("\nPrintList():\n  g_nSize: %d\n  g_pHead[%p]\n", pListData->nSize, pListData->pHead);
	NODE* pTmp = pListData->pHead;
    const char* (*pfGetKey)(USER_DATA*) = NULL;

	while (pTmp != NULL)
	{
        USER_DATA* pUser = pTmp->pData;
		printf("         [%14p] prev[%14p], name: %15s, phone: %15s, next[%14p]\n",
				        pTmp, pTmp->prev, pUser->GetKey(pUser), pUser->GetVal(pUser), pTmp->next);
		pTmp = pTmp->next;
	}
    printf("  g_pTail[%p]\n\n", pListData->pTail);
}