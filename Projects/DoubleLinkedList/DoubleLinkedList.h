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
	char szName[64];
	char szPhone[64];
}USERDATA;


// �ڷᱸ�� NODE ����ü
typedef struct NODE
{
	// ���� ��� �ڷ�
	USERDATA* pData;

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
int InsertAtHead(USERDATA* pParam);
int InsertAtTail(USERDATA* pParam);
int InsertAtIndex(int iIndex, const char* pszData);

NODE* GetAtIndexData(int iIndex);
int GetLength();
int GetSize();
