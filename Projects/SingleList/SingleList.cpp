#include "SingleList.h"

NODE g_head = { 0 };		// ���Ḯ��Ʈ ��� ���� ����
NODE g_tail = { 0 };		// ���Ḯ��Ʈ ������ �κ� ���� ����

/*
	���� ����Ʈ ��ü ������ ���
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
	���Ḯ��Ʈ ���, ������ �κ� ���� ������ next �� ���
*/
void PrintHeadTail()
{
	printf("g_head.next: [%p], g_tail.next: [%p]\n", g_head.next, g_tail.next);
}

/*
	���� ����Ʈ�� �����Ͱ� �ִ��� ������ �Ǵ�
*/
int IsEmpty()
{
	if (g_head.next == NULL)
		return 1;

	return 0;
}

/*
	���� ����Ʈ �� �� �κ� ������ �߰�
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
	���� ����Ʈ �� �� �κ� ������ �߰�
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
	���� ����Ʈ ��ü ������ ����
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

	// �ſ��߿�!!
	// ���� ��� ����, ���� ������ �κ� ������ �ٽ� �ʱ�ȭ �����ָ� 
	// �̹� �޸𸮰� ������ �ּҸ� ����Ű�� �Ǳ� ������ ġ������ ������ �߻��Ѵ�.
	g_head.next = NULL;
	g_tail.next = NULL;
}

/*
	Ư�� ��� Ž��
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
	Ư�� ��� ����
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

		if (g_head.next == NULL)
			g_tail.next = NULL;

		free(pDelete);
		return 1;
	}
	return 0;
}

/*
	List �׽�Ʈ�� ���� �ڵ�
*/
void TestList()
{
	puts("*** InsertAtHead() ***");
	InsertAtHead("TEST01");
	PrintHeadTail();
	InsertAtHead("TEST02");
	PrintHeadTail();
	InsertAtHead("TEST03");
	PrintHeadTail();
	PrintList();

	printf("FindData(): %s found\n", FindData("TEST01") == 0 ? 0 : FindData("TEST01")->next->szData);
	printf("FindData(): %s found\n", FindData("TEST02") == 0 ? 0 : FindData("TEST02")->next->szData);
	printf("FindData(): %s found\n", FindData("TEST03") == 0 ? 0 : FindData("TEST03")->next->szData);
	putchar('\n');

	DeleteData("TEST01");
	PrintHeadTail();
	PrintList();
	DeleteData("TEST02");
	PrintHeadTail();
	PrintList();
	DeleteData("TEST03");
	PrintHeadTail();
	PrintList();

	puts("*** InsertAtTail() ***");
	InsertAtTail("TEST01");
	PrintHeadTail();
	InsertAtTail("TEST02");
	PrintHeadTail();
	InsertAtTail("TEST03");
	PrintHeadTail();
	PrintList();

	printf("FindData(): %s found\n", FindData("TEST01") == 0 ? 0 : FindData("TEST01")->next->szData);
	printf("FindData(): %s found\n", FindData("TEST02") == 0 ? 0 : FindData("TEST02")->next->szData);
	printf("FindData(): %s found\n", FindData("TEST03") == 0 ? 0 : FindData("TEST03")->next->szData);
	putchar('\n');

	DeleteData("TEST01");
	PrintHeadTail();
	PrintList();
	DeleteData("TEST02");
	PrintHeadTail();
	PrintList();
	DeleteData("TEST03");
	PrintHeadTail();
	PrintList();

	ReleaseList();
}



/*
	���Ḯ��Ʈ�� Stack �������� ������ ����
*/
int PushData(const char* pszData)
{
	return InsertAtHead(pszData);
}

/*
	���Ḯ��Ʈ���� Stack �������� ������ ����
*/
int PopData(NODE* pPopNode)
{
	if (IsEmpty())
		return 0;

	NODE* sp = g_head.next;
	memcpy(pPopNode, sp, sizeof(NODE));
	g_head.next = sp->next;

	if (g_head.next == NULL || sp == g_tail.next)
		g_tail.next = NULL;

	printf("Pop: %s\n", sp->szData);
	free(sp);
	sp = NULL;

	return 1;
}

/*
	Stack Test �Լ�
*/
void TestStack()
{
	// Stack �׽�Ʈ�� ���� �ڵ�
	puts("*** PushData() ***");
	PushData("TEST01");
	PrintHeadTail();
	PushData("TEST02");
	PrintHeadTail();
	PushData("TEST03");
	PrintHeadTail();
	PrintList();

	NODE node = { 0 };
	PopData(&node);
	PrintHeadTail();
	PopData(&node);
	PrintHeadTail();
	PopData(&node);
	PrintHeadTail();

	ReleaseList();
}

/*
	���Ḯ��Ʈ�� Queue �������� ������ ����
*/
int Enqueue(const char* pszData)
{
	return InsertAtTail(pszData);
}

/*
	���Ḯ��Ʈ���� Queue �������� ������ ����
*/
int Dequeue(NODE* pGetNode)
{
	if (IsEmpty())
		return 0;

	NODE* sp = g_head.next;
	memcpy(pGetNode, sp, sizeof(NODE));
	g_head.next = sp->next;

	if (g_head.next == NULL || sp == g_tail.next)
		g_tail.next = NULL;

	printf("Dequeue: %s\n", sp->szData);
	free(sp);
	sp = NULL;

	return 1;
}

/*
	Queue Test �Լ�
*/
void TestQueue()
{
	// Queue �׽�Ʈ�� ���� �ڵ�
	puts("*** Enqueue() ***");
	Enqueue("TEST01");
	PrintHeadTail();
	Enqueue("TEST02");
	PrintHeadTail();
	Enqueue("TEST03");
	PrintHeadTail();
	PrintList();

	NODE node = { 0 };
	Dequeue(&node);
	PrintHeadTail();
	Dequeue(&node);
	PrintHeadTail();
	Dequeue(&node);
	PrintHeadTail();

	ReleaseList();

}



/*
	�����Լ�
*/
int main()
{
	TestList();
	TestStack();
	TestQueue();
	return 0;
}