#pragma once
/*
	* ADT(Abstract Data Type) 적용
	- 자료와 관리체계를 분리
	- 연결 리스트의 prev, next 포인터는 관리체계이며 연결 리스트 사용자가 임의로 접근하거나 변경하지 말아야 한다.
*/
#include <stdio.h>
#include <malloc.h>
#include <string.h>

// 테스트용 USERDATA 구조체
typedef struct USERDATA
{
	char szName[64];
	char szPhone[64];
}USERDATA;


// 자료구조 NODE 구조체
typedef struct NODE
{
	// 관리 대상 자료
	USERDATA* pData;

	// 자료 구조
	struct NODE* prev;
	struct NODE* next;
}NODE;




// 함수선언
int InitList();
void ReleaseList();
void PrintList();
int IsEmpty();
NODE* FindNode(const char* pszName);
int DeleteNode(const char* pszName);
int InsertAtHead(USERDATA* pParam);
int InsertAtTail(USERDATA* pParam);
int InsertAtIndex(int iIndex, const char* pszData);

NODE* GetAtIndexData(int iIndex);
int GetLength();
int GetSize();
