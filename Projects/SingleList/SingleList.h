#pragma once
#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct NODE 
{
	char szData[64];
	struct NODE* next;
} NODE;

// 함수 선언
void PrintList();
int InsertAtHead(const char* pszData);
int InsertAtTail(const char* pszData);
int FindData(const char* pszData);
int DeleteData(const char* pszData);
void ReleaseList();

void TestList();