#include "DoubleLinkedList.h"

NODE* g_pHeadNode;		// 연결 리스트 헤드 전역 노드
NODE* g_pTailNode;		// 연결 리스트 꼬리 전역 노드
int g_iNodeSize;			// 전체 노드 개수


/*
	리스트 초기화
*/
int InitList()
{
	g_pHeadNode = (NODE*)malloc(sizeof(NODE));
	if (g_pHeadNode == NULL) return -1;
	g_pTailNode = (NODE*)malloc(sizeof(NODE));
	if (g_pTailNode == NULL) return -1;

	memset(g_pHeadNode, 0, sizeof(NODE));
	memset(g_pTailNode, 0, sizeof(NODE));

	strcpy_s(g_pHeadNode->szData, sizeof(g_pHeadNode->szData), "DUMMY HEAD");
	strcpy_s(g_pTailNode->szData, sizeof(g_pTailNode->szData), "DUMMY TAIL");

	g_iNodeSize = 0;

	g_pHeadNode->next = g_pTailNode;
	g_pTailNode->prev = g_pHeadNode;

	return 0;
}	

/*
	전체 노드 삭제
*/
void ReleaseList()
{
	NODE* pTmp = g_pHeadNode;
	NODE* pDelete = NULL;
	while (pTmp != NULL)
	{
		pDelete = pTmp;
		pTmp = pTmp->next;

		printf("free(%p)\n", pDelete);
		free(pDelete);
	}

	g_pHeadNode = NULL;
	g_pTailNode = NULL;
	g_iNodeSize = 0;

	puts("ReleaseList()\n");
}

/*
	전체 노드 리스트 출력
*/
void PrintList()
{
	printf("PrintList(): g_iNodeSize: %d, g_pHeadNode [%p], g_pTailNode [%p]\n"
		, g_iNodeSize, g_pHeadNode, g_pTailNode);

	NODE* pTmp = g_pHeadNode;
	while (pTmp != NULL)
	{
		printf("[%p] %p, %s [%p]\n", pTmp->prev, pTmp, pTmp->szData, pTmp->next);
		pTmp = pTmp->next;
	}
}

/*
	리스트에 데이터 존재 유무를 판단
*/
int IsEmpty()
{
	return GetSize();
}

/*
	Head 쪽으로 데이터 삽입
*/
int InsertAtHead(const char* pszData)
{
	NODE* pNewNode = (NODE*)malloc(sizeof(NODE));
	if (pNewNode == NULL) return -1;
	memset(pNewNode, 0, sizeof(NODE));
	strcpy_s(pNewNode->szData, sizeof(pNewNode->szData), pszData);

	pNewNode->prev = g_pHeadNode;
	pNewNode->next = g_pHeadNode->next;
	g_pHeadNode->next->prev = pNewNode;
	g_pHeadNode->next = pNewNode;

	g_iNodeSize++;

	return 0;
}

/*
	Tail 쪽으로 데이터 삽입
*/
int InsertAtTail(const char* pszData)
{
	NODE* pNewNode = (NODE*)malloc(sizeof(NODE));
	if (pNewNode == NULL) return -1;
	memset(pNewNode, 0, sizeof(NODE));
	strcpy_s(pNewNode->szData, sizeof(pNewNode->szData), pszData);

	pNewNode->prev = g_pTailNode->prev;
	pNewNode->next = g_pTailNode;
	g_pTailNode->prev->next = pNewNode;
	g_pTailNode->prev = pNewNode;

	g_iNodeSize++;

	return g_iNodeSize;
}


/*
	특정 인덱스 차례 노드에 데이터 삽입
*/
int InsertAtIndex(int iIndex, const char* pszData)
{
	int iret = 0;
	if (iIndex == 0)
	{
		iret = InsertAtHead(pszData);
	}
	else if (iIndex >= GetLength())
	{
		iret = InsertAtTail(pszData);
	}
	else
	{

		NODE* pNewNode = (NODE*)malloc(sizeof(NODE));
		if (pNewNode == NULL) return -1;
		memset(pNewNode, 0, sizeof(NODE));
		strcpy_s(pNewNode->szData, sizeof(pNewNode->szData), pszData);

		int i = 0;
		NODE* pTmp = g_pHeadNode->next;
		while (pTmp->next != g_pTailNode)
		{
			if (i == iIndex) break;
			i++;
			pTmp = pTmp->next;
		}

		pNewNode->prev = pTmp->prev;
		pNewNode->next = pTmp;

		pTmp->prev->next = pNewNode;
		pTmp->prev = pNewNode;

		iret = i;
	}

	g_iNodeSize++;

	return iret;
}

/*
	리스트에서 특정 노드 탐색
*/
NODE* FindNode(const char* pszData)
{
	NODE* pTmp = g_pHeadNode->next;
	while (pTmp != g_pTailNode)
	{
		if (strcmp(pTmp->szData, pszData) == 0)
			return pTmp;

		pTmp = pTmp->next;
	}

	return NULL;
}

NODE* GetAtIndexData(int iIndex)
{
	if (iIndex < 0 || iIndex >= GetLength())
	{
		printf("잘못된 인덱스 접근!!\n");
		return NULL;
	}

	int i = 0;
	NODE* pTmp = g_pHeadNode->next;
	while (i != iIndex)
	{
		pTmp = pTmp->next;
		i++;
	}

	return pTmp;
}


/*
	리스트에서 특정 노드 삭제
*/
int DeleteNode(const char* pszData)
{
	NODE* pDelete = FindNode(pszData);

	pDelete->prev->next = pDelete->next;
	pDelete->next->prev = pDelete->prev;

	printf("DeleteNode(): %p\n", pDelete);
	free(pDelete);

	g_iNodeSize--;

	return g_iNodeSize;
}

/*
	리스트의 길이를 구함
*/
int GetLength()
{
	return GetSize();
}

/*
	리스트의 크기를 구함
*/
int GetSize()
{
	return g_iNodeSize;
}



/*
	메인함수
*/
int main()
{
	InitList();

	InsertAtHead("TEST01");
	InsertAtHead("TEST02");
	InsertAtHead("TEST03");
	PrintList();

	printf("FindNode(): [%p]\n", FindNode("TEST01"));
	printf("FindNode(): [%p]\n", FindNode("TEST02"));
	printf("FindNode(): [%p]\n", FindNode("TEST03"));

	DeleteNode("TEST01");
	DeleteNode("TEST03");
	DeleteNode("TEST02");
	PrintList();

	InsertAtTail("TEST01");
	InsertAtTail("TEST02");
	InsertAtTail("TEST03");
	PrintList();


	InsertAtIndex(0, "TEST AT 00");
	PrintList();
	InsertAtIndex(2, "TEST AT 02");
	PrintList();
	InsertAtIndex(1, "TEST AT 01");
	PrintList();
	InsertAtIndex(3, "TEST AT 03");
	PrintList();

	NODE* pNode = GetAtIndexData(0);

	pNode == NULL ? printf("GetAtIndesData(%d): null\n", 0) : printf("GetAtIndesData(%d): %s\n", 0, pNode->szData);
	pNode = GetAtIndexData(1);
	pNode == NULL ? printf("GetAtIndesData(%d): null\n", 1) : printf("GetAtIndesData(%d): %s\n", 1, pNode->szData);
	pNode = GetAtIndexData(2);
	pNode == NULL ? printf("GetAtIndesData(%d): null\n", 2) : printf("GetAtIndesData(%d): %s\n", 2, pNode->szData);

	ReleaseList();

	return 0;
}

