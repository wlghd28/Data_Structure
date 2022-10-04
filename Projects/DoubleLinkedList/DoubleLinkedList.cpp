#include "DoubleLinkedList.h"

NODE* g_pHeadNode;		// ���� ����Ʈ ��� ���� ���
NODE* g_pTailNode;		// ���� ����Ʈ ���� ���� ���
int g_iNodeSize;			// ��ü ��� ����


/*
	����Ʈ �ʱ�ȭ
*/
int InitList()
{
	g_pHeadNode = (NODE*)malloc(sizeof(NODE));
	if (g_pHeadNode == NULL) return -1;
	g_pTailNode = (NODE*)malloc(sizeof(NODE));
	if (g_pTailNode == NULL) return -1;

	memset(g_pHeadNode, 0, sizeof(NODE));
	memset(g_pTailNode, 0, sizeof(NODE));

	g_iNodeSize = 0;

	g_pHeadNode->next = g_pTailNode;
	g_pTailNode->prev = g_pHeadNode;

	return 0;
}	

/*
	��ü ��� ����
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
		free(pDelete->pData);
		free(pDelete);
	}

	g_pHeadNode = NULL;
	g_pTailNode = NULL;
	g_iNodeSize = 0;

	puts("ReleaseList()\n");
}

/*
	��ü ��� ����Ʈ ���
*/
void PrintList()
{
	printf("PrintList(): g_iNodeSize: %d, g_pHeadNode [%p], g_pTailNode [%p]\n"
		, g_iNodeSize, g_pHeadNode, g_pTailNode);

	int i = 0;
	NODE* pTmp = g_pHeadNode;
	while (pTmp != NULL)
	{
		if (pTmp == g_pHeadNode || pTmp == g_pTailNode)
		{
			puts("[DUMMY]");
		}
		else
		{
			printf("Index: %d %s, %s\n", i, pTmp->pData->szName, pTmp->pData->szPhone);
			i++;
		}
		pTmp = pTmp->next;
	}
}

/*
	����Ʈ�� ������ ���� ������ �Ǵ�
*/
int IsEmpty()
{
	return GetSize();
}

/*
	Head ������ ������ ����
	pParam : ȣ���ڰ� �޸𸮸� ���� �Ҵ� + �� �������� �ؼ� ���� 
*/
int InsertAtHead(USERDATA* pParam)
{
	NODE* pNewNode = (NODE*)malloc(sizeof(NODE));
	if (pNewNode == NULL) return -1;
	memset(pNewNode, 0, sizeof(NODE));
	//strcpy_s(pNewNode->szData, sizeof(pNewNode->szData), pszData);

	pNewNode->pData = pParam;

	pNewNode->prev = g_pHeadNode;
	pNewNode->next = g_pHeadNode->next;
	g_pHeadNode->next->prev = pNewNode;
	g_pHeadNode->next = pNewNode;

	g_iNodeSize++;

	return 0;
}

/*
	Tail ������ ������ ����
*/
int InsertAtTail(USERDATA* pParam)
{
	NODE* pNewNode = (NODE*)malloc(sizeof(NODE));
	if (pNewNode == NULL) return -1;
	memset(pNewNode, 0, sizeof(NODE));
	//strcpy_s(pNewNode->szData, sizeof(pNewNode->szData), pszData);

	pNewNode->pData = pParam;

	pNewNode->prev = g_pTailNode->prev;
	pNewNode->next = g_pTailNode;
	g_pTailNode->prev->next = pNewNode;
	g_pTailNode->prev = pNewNode;

	g_iNodeSize++;

	return g_iNodeSize;
}


/*
	Ư�� �ε��� ���� ��忡 ������ ����
*/
int InsertAtIndex(int iIndex, USERDATA* pParam)
{
	int iret = 0;
	if (iIndex == 0)
	{
		iret = InsertAtHead(pParam);
	}
	else if (iIndex >= GetLength())
	{
		iret = InsertAtTail(pParam);
	}
	else
	{

		NODE* pNewNode = (NODE*)malloc(sizeof(NODE));
		if (pNewNode == NULL) return -1;
		memset(pNewNode, 0, sizeof(NODE));
		//strcpy_s(pNewNode->szData, sizeof(pNewNode->szData), pszData);
		pNewNode->pData = pParam;

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
	����Ʈ���� Ư�� ��� Ž��
*/
NODE* FindNode(const char* pszName)
{
	NODE* pTmp = g_pHeadNode->next;
	while (pTmp != g_pTailNode)
	{
		if (strcmp(pTmp->pData->szName, pszName) == 0)
			return pTmp;

		pTmp = pTmp->next;
	}

	return NULL;
}

NODE* GetAtIndexData(int iIndex)
{
	if (iIndex < 0 || iIndex >= GetLength())
	{
		printf("�߸��� �ε��� ����!!\n");
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
	����Ʈ���� Ư�� ��� ����
*/
int DeleteNode(const char* pszName)
{
	NODE* pDelete = FindNode(pszName);

	pDelete->prev->next = pDelete->next;
	pDelete->next->prev = pDelete->prev;

	printf("DeleteNode(): %p\n", pDelete);

	free(pDelete->pData);
	free(pDelete);

	g_iNodeSize--;

	return g_iNodeSize;
}

/*
	����Ʈ�� ���̸� ����
*/
int GetLength()
{
	return GetSize();
}

/*
	����Ʈ�� ũ�⸦ ����
*/
int GetSize()
{
	return g_iNodeSize;
}



/*
	�����Լ�
*/
int main()
{
	InitList();

	USERDATA* pNewData = NULL;

	pNewData = (USERDATA*)malloc(sizeof(USERDATA));
	if (pNewData == NULL) return -1;
	memset(pNewData, 0, sizeof(USERDATA));
	strcpy_s(pNewData->szName, sizeof(pNewData->szName), "Ji-hong");
	strcpy_s(pNewData->szPhone, sizeof(pNewData->szPhone), "010-1234-1234");
	InsertAtTail(pNewData);

	pNewData = (USERDATA*)malloc(sizeof(USERDATA));
	if (pNewData == NULL) return -1;
	memset(pNewData, 0, sizeof(USERDATA));
	strcpy_s(pNewData->szName, sizeof(pNewData->szName), "TEST");
	strcpy_s(pNewData->szPhone, sizeof(pNewData->szPhone), "010-1111-2222");
	InsertAtTail(pNewData);


	PrintList();
	ReleaseList();

	return 0;
}

