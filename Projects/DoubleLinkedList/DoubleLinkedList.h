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
	// 멤버 함수 포인터
	const char* (*GetKey)(USERDATA*);

	char szName[64];			// key
	char szPhone[64];
}USERDATA;


// 자료구조 NODE 구조체
typedef struct NODE
{
	// 관리 대상 자료
	void* pData;

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
int InsertAtHead(void* pParam);
int InsertAtTail(void* pParam);
int InsertAtIndex(int iIndex, void* pParam);

NODE* GetAtIndexData(int iIndex);
int GetLength();
int GetSize();

const char* GetKeyFromUserData(USERDATA* pUser);
USERDATA* CreateUserData(const char* pszName, const char* pszPhone);