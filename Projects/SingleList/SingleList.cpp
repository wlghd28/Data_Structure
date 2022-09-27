#include "SingleList.h"

NODE g_head = { 0 };		// 연결리스트 헤드 전역 변수

/*
	연결 리스트 전체 데이터 출력
*/
void PrintList(void)
{
	NODE* pHead = g_head.next;
	while (pHead != NULL)
	{
		printf("[%p] %s, next[%p]\n", pHead, pHead->szData, pHead->next);
		pHead = pHead->next;
	}

	putchar('\n');
}

int IsEmpty()
{
	if (g_head.next == NULL)
		return 1;

	return 0;
}

/*
	연결 리스트 맨 앞 부분 데이터 추가
*/
int InsertAtHead(const char* pszData)
{
	NODE* pNode = (NODE*)malloc(sizeof(NODE));
	if (pNode == NULL) return -1;
	memset(pNode, 0, sizeof(NODE));
	strcpy_s(pNode->szData, sizeof(pNode->szData), pszData);

	if (IsEmpty())
		g_head.next = pNode;
	else 
	{
		pNode->next = g_head.next;
		g_head.next = pNode;
	}

	return 1;
}


/*
	연결 리스트 맨 끝 부분 데이터 추가
*/
int InsertAtTail(const char* pszData)
{
	//마지막 노드를 찾는다.
	NODE* pTmp = &g_head;
	while (pTmp->next != 0)
		pTmp = pTmp->next;

	NODE* pNode = (NODE*)malloc(sizeof(NODE));
	if (pNode == NULL) return -1;
	memset(pNode, 0, sizeof(NODE));
	strcpy_s(pNode->szData, sizeof(pNode->szData), pszData);

	pTmp->next = pNode;

	return 0;
}


/*
	연결 리스트 전체 데이터 삭제
*/
void ReleaseList()
{
	printf("\nReleaseList()\n");
	NODE* pTmp = g_head.next;
	NODE* pDelete = NULL;
	while (pTmp != NULL) 
	{
		pDelete = pTmp;
		pTmp = pDelete->next;

		printf("Delete: [%p] %s\n", pDelete, pDelete->szData);
		free(pDelete);
		pDelete = NULL;
	}

	// 매우중요!!
	// 전역 헤드 변수를 다시 초기화 안해주면 
	// 이미 메모리가 해제된 주소를 가리키고 있기 때문에 치명적인 오류가 발생한다.
	g_head.next = NULL;
							
}

/*
	특정 노드 탐색
*/
int FindData(const char* pszData)
{
	NODE* pCur = g_head.next;
	NODE* pPrev = &g_head;
	while (pCur != NULL)
	{
		if (strcmp(pCur->szData, pszData) == 0)
			return 1;
		pCur = pCur->next;
		pPrev = pPrev->next;
	}

	return 0;
}

/*
	특정 노드 삭제
*/
int DeleteData(const char* pszData)
{
	NODE* pCur = g_head.next;
	NODE* pPrev = &g_head;
	while (pCur != NULL)
	{
		if (strcmp(pCur->szData, pszData) == 0)
		{
			//삭제
			printf("DeleteData(): %s\n", pCur->szData);
			pPrev->next = pCur->next;
			free(pCur);
			return 1;
		}

		pCur = pCur->next;
		pPrev = pPrev->next;
	}

	return 0;
}


/*
	List 테스트를 위한 코드
*/
void TestList()
{
	puts("*** InsertAtHead() ***");
	InsertAtHead("TEST01");
	InsertAtHead("TEST02");
	InsertAtHead("TEST03");
	PrintList();

	if (FindData("TEST01") == 1)
		printf("FindData(): TEST01 found\n");
	if (FindData("TEST02") == 1)
		printf("FindData(): TEST02 found\n");
	if (FindData("TEST03") == 1)
		printf("FindData(): TEST03 found\n");
	putchar('\n');

	DeleteData("TEST01");
	PrintList();
	DeleteData("TEST02");
	PrintList();
	DeleteData("TEST03");
	PrintList();

	puts("*** InsertAtTail() ***");
	InsertAtTail("TEST01");
	InsertAtTail("TEST02");
	InsertAtTail("TEST03");
	PrintList();


	if (FindData("TEST01") == 1)
		printf("FindData(): TEST01 found\n");
	if (FindData("TEST02") == 1)
		printf("FindData(): TEST02 found\n");
	if (FindData("TEST03") == 1)
		printf("FindData(): TEST03 found\n");
	putchar('\n');

	DeleteData("TEST01");
	PrintList();
	DeleteData("TEST02");
	PrintList();
	DeleteData("TEST03");
	PrintList();

	ReleaseList();
}

int main()
{
	TestList();
	return 0;
}