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
		free(pDelete->pData);
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
			USERDATA* pUser = (USERDATA*)(pTmp->pData);
			printf("Index: %d %s\n", i, pUser->GetKey(pUser));
			i++;
		}
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
	pParam : 호출자가 메모리를 동적 할당 + 값 설정까지 해서 전달 
*/
int InsertAtHead(void* pParam)
{
	NODE* pNewNode = (NODE*)malloc(sizeof(NODE));
	if (pNewNode == NULL) return -1;
	memset(pNewNode, 0, sizeof(NODE));
	//strcpy_s(pNewNode->szData, sizeof(pNewNode->szData), pszData);

	// 관리 대상 자료에 관한 초기화
	pNewNode->pData = pParam;

	// 연결 리스트에 관한 초기화
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
int InsertAtTail(void* pParam)
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
	특정 인덱스 차례 노드에 데이터 삽입
*/
int InsertAtIndex(int iIndex, void* pParam)
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
	리스트에서 특정 노드 탐색
*/
NODE* FindNode(const char* pszKey)
{
	NODE* pTmp = g_pHeadNode->next;
	const char* (*pfGetKey)(void*) = NULL;
	while (pTmp != g_pTailNode)
	{
		// 관리 대상 데이터 구조체 첫 번째 멤버가 함수 포인터임을 가정
		pfGetKey = (const char* (*)(void*))pTmp->pData;
		if (strcmp(pfGetKey(pTmp->pData), pszKey) == 0)
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
int DeleteNode(const char* pszKey)
{
	NODE* pDelete = FindNode(pszKey);

	pDelete->prev->next = pDelete->next;
	pDelete->next->prev = pDelete->prev;

	printf("DeleteNode(): %p\n", pDelete);

	free(pDelete->pData);
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
	USERDATA 데이터의 Key(이름) 값을 반환
*/
const char* GetKeyFromUserData(USERDATA* pUser)
{
	return pUser->szName;
}

/*
	새로운 USERDATA 데이터 생성
*/
USERDATA* CreateUserData(const char* pszName, const char* pszPhone)
{
	USERDATA* pNewData = NULL;
	pNewData = (USERDATA*)malloc(sizeof(USERDATA));
	if (pNewData == NULL) return NULL;
	memset(pNewData, 0, sizeof(USERDATA));

	strcpy_s(pNewData->szName, sizeof(pNewData->szName), pszName);
	strcpy_s(pNewData->szPhone, sizeof(pNewData->szPhone), pszPhone);

	// 구조체 멤버 함수 포인터 초기화
	pNewData->GetKey = GetKeyFromUserData;

	return pNewData;
}

/*
	메인함수
*/
int main()
{
	InitList();
	USERDATA* pNewData = NULL;
	pNewData = CreateUserData("Ji-hong", "010-1234-1234");
	InsertAtTail(pNewData);
	pNewData = CreateUserData("TEST", "010-1111-2222");
	InsertAtTail(pNewData);
	PrintList();
	ReleaseList();

	return 0;
}

