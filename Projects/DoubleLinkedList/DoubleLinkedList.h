#pragma once
#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct NODE
{
	char szData[64];

	struct NODE* prev;
	struct NODE* next;
}NODE;

// 함수선언
int InitList();
void ReleaseList();
void PrintList();
int IsEmpty();
NODE* FindNode(const char* pszData);
int DeleteNode(const char* pszData);
int InsertAtHead(const char* pszData);
int InsertAtTail(const char* pszData);
int InsertAtIndex(int iIndex, const char* pszData);

NODE* GetAtIndexData(int iIndex);
int GetLength();
int GetSize();
