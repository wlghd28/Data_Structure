#pragma once
/*
	* ADT(Abstract Data Type) ����
	- �ڷ�� ����ü�踦 �и�
	- ���� ����Ʈ�� prev, next �����ʹ� ����ü���̸� ���� ����Ʈ ����ڰ� ���Ƿ� �����ϰų� �������� ���ƾ� �Ѵ�.
*/
#include <stdio.h>
#include <malloc.h>
#include <string.h>

// �׽�Ʈ�� USERDATA ����ü
typedef struct USERDATA
{
	// ��� �Լ� ������
	const char* (*GetKey)(USERDATA*);

	char szName[64];			// key
	char szPhone[64];
}USERDATA;


// �ڷᱸ�� NODE ����ü
typedef struct NODE
{
	// ���� ��� �ڷ�
	void* pData;

	// �ڷ� ����
	struct NODE* prev;
	struct NODE* next;
}NODE;




// �Լ�����
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