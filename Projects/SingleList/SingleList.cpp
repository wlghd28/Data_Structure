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
	�����Լ�
*/
int main()
{
	TestList();
	TestStack();
	TestQueue();
	return 0;
}