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

// 연결리스트
void PrintList();
int InsertAtHead(const char* pszData);
int InsertAtTail(const char* pszData);
NODE* FindData(const char* pszData);
int DeleteData(const char* pszData);
void ReleaseList();
void TestList();

// Stack
int PushData(const char* pszData);
int PopData(NODE* pPopNode);
void TestStack();

// Queue
int Enqueue(const char* pszData);
int Dequeue(NODE* pGetNode);
void TestQueue();

