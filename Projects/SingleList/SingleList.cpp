#include "SingleList.h"

NODE g_head = { 0 };		// 연결리스트 헤드 전역 변수
NODE g_tail = { 0 };		// 연결리스트 마지막 부분 전역 변수

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

/*
	연결 리스트에 데이터가 있는지 없는지 판단
*/
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
		g_tail.next = pNode;
	else 
		pNode->next = g_head.next;

	g_head.next = pNode;

	return 1;
}


/*
	연결 리스트 맨 끝 부분 데이터 추가
*/
int InsertAtTail(const char* pszData)
{
	NODE* pNode = (NODE*)malloc(sizeof(NODE));
	if (pNode == NULL) return -1;
	memset(pNode, 0, sizeof(NODE));
	strcpy_s(pNode->szData, sizeof(pNode->szData), pszData);

	if (IsEmpty())
		g_head.next = pNode;
	else
		g_tail.next->next = pNode;

	g_tail.next = pNode;


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
	// 전역 헤드 변수, 전역 마지막 부분 변수를 다시 초기화 안해주면 
	// 이미 메모리가 해제된 주소를 가리키게 되기 때문에 치명적인 오류가 발생한다.
	g_head.next = NULL;
	g_tail.next = NULL;
}

/*
	특정 노드 탐색
*/
NODE* FindData(const char* pszData)
{
	NODE* pCur = g_head.next;
	NODE* pPrev = &g_head;
	while (pCur != NULL)
	{
		if (strcmp(pCur->szData, pszData) == 0)
			return pPrev;
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
	NODE* pPrev = FindData(pszData);
	NODE* pDelete = NULL;
	if (pPrev != NULL)
	{
		pDelete = pPrev->next;
		pPrev->next = pDelete->next;

		printf("DeleteData(): %s\n", pDelete->szData);

		if (pDelete == g_tail.next)
			g_tail.next = pPrev;

		free(pDelete);
		return 1;
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

	printf("FindData(): %s found\n", FindData("TEST01") == 0 ? 0 : FindData("TEST01")->next->szData);
	printf("FindData(): %s found\n", FindData("TEST02") == 0 ? 0 : FindData("TEST02")->next->szData);
	printf("FindData(): %s found\n", FindData("TEST03") == 0 ? 0 : FindData("TEST03")->next->szData);
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

	printf("FindData(): %s found\n", FindData("TEST01") == 0 ? 0 : FindData("TEST01")->next->szData);
	printf("FindData(): %s found\n", FindData("TEST02") == 0 ? 0 : FindData("TEST02")->next->szData);
	printf("FindData(): %s found\n", FindData("TEST03") == 0 ? 0 : FindData("TEST03")->next->szData);
	putchar('\n');

	DeleteData("TEST01");
	PrintList();
	DeleteData("TEST02");
	PrintList();
	DeleteData("TEST03");
	PrintList();

	ReleaseList();
}



/*
	연결리스트에 Stack 개념으로 데이터 삽입
*/
int PushData(const char* pszData)
{
	return InsertAtHead(pszData);
}

/*
	연결리스트에서 Stack 개념으로 데이터 삭제
*/
int PopData(NODE* pPopNode)
{
	if (IsEmpty())
		return 0;

	NODE* sp = g_head.next;
	memcpy(pPopNode, sp, sizeof(NODE));
	g_head.next = sp->next;
	free(sp);
	sp = NULL;

	return 1;
}

/*
	Stack Test 함수
*/
void TestStack()
{
	// Stack 테스트를 위한 코드
	puts("*** PushData() ***");
	PushData("TEST01");
	PushData("TEST02");
	PushData("TEST03");
	PrintList();

	NODE node = { 0 };
	PopData(&node);
	printf("Pop: %s\n", node.szData);
	PopData(&node);
	printf("Pop: %s\n", node.szData);
	PopData(&node);
	printf("Pop: %s\n", node.szData);

	ReleaseList();
}

/*
	연결리스트에 Queue 개념으로 데이터 삽입
*/
int Enqueue(const char* pszData)
{
	return InsertAtTail(pszData);
}

/*
	연결리스트에서 Queue 개념으로 데이터 삭제
*/
int Dequeue(NODE* pGetNode)
{
	if (IsEmpty())
		return 0;

	NODE* sp = g_head.next;
	memcpy(pGetNode, sp, sizeof(NODE));
	g_head.next = sp->next;
	free(sp);
	sp = NULL;

	return 1;
}

/*
	Queue Test 함수
*/
void TestQueue()
{
	// Queue 테스트를 위한 코드
	puts("*** Enqueue() ***");
	Enqueue("TEST01");
	Enqueue("TEST02");
	Enqueue("TEST03");
	PrintList();

	NODE node = { 0 };
	Dequeue(&node);
	printf("Dequeue: %s\n", node.szData);
	Dequeue(&node);
	printf("Dequeue: %s\n", node.szData);
	Dequeue(&node);
	printf("Dequeue: %s\n", node.szData);

	ReleaseList();

}



/*
	메인함수
*/
int main()
{
	TestList();
	TestStack();
	TestQueue();
	return 0;
}