// ������23�������л�����ڽ��
// ��Ŀ����һ�����������а����������ҳ�������Ļ�����ڽ�㣬�������null��

#include <iostream>
#include "List.h"
using namespace std;


class Solution 
{
	//˼·��1��ȷ���������Ƿ��л�����ָ����2��������ָ����1������ָ����׷���˿�ָ�룬���ʾ�л���
	//2��ȷ��������ڵķ�ʽ����������Ļ���n���ڵ㣬��ָ��P1���ƶ���n-1��λ�ã�Ȼ��ָ��P1��ָ��P2ͬ���ƶ�����ָ���غ�ʱ������ڽڵ㣩
	//3��ȷ�����еĽڵ���Ŀ��1�еĿ���ָ������ʱλ�ڻ��У���������һָ�������ǰ�����ٴ�����ʱȡ����ֵ��
	//4��������������ͨ����ѧ�Ƶ������Է���1����ָ����������λ�ã�����2��ָ��P1Ӧ��Ҫ�ƶ�����n-1λ��

public:
	//������������4�����Ĵ����Ż�������ʱ�䣺3ms��ռ���ڴ棺572k
	ListNode* EntryNodeOfLoop(ListNode* pHead)
	{
		if (pHead == nullptr || pHead->m_pNext == nullptr || pHead->m_pNext->m_pNext == nullptr)
			return nullptr;
		//ע���ʼֵ��������ǰ��һ������Ȼ�����ѭ����ֱ�ӱ�����
		ListNode* pFast = pHead->m_pNext->m_pNext;
		ListNode* pSlow = pHead->m_pNext;
		//1.�ж��Ƿ��л��������������õ������ڵ���ཻλ��
		while (pFast != pSlow)
		{
			if (pFast->m_pNext != nullptr && pFast->m_pNext->m_pNext != nullptr)
				pFast = pFast->m_pNext->m_pNext;
			else
				return nullptr;

			if (pSlow->m_pNext != nullptr)
				pSlow = pSlow->m_pNext;
			else
				return nullptr;
		}
		//2.��ָ��������λ�ã�����n-1����λ�ã����Բ��ü����������ֱ�ӽ�slow�ص��ײ���ʼͬ���ƶ�����
		pSlow = pHead;
		while (pSlow != pFast)
		{
			pFast = pFast->m_pNext;
			pSlow = pSlow->m_pNext;
		}
		return pFast;
	}

	ListNode* EntryNodeOfLoop2(ListNode* pHead)
	{
		if (pHead == nullptr || pHead->m_pNext == nullptr || pHead->m_pNext->m_pNext == nullptr)
			return nullptr;
		//ע���ʼֵ��������ǰ��һ������Ȼ�����ѭ����ֱ�ӱ�����
		ListNode* pFast = pHead->m_pNext->m_pNext;
		ListNode* pSlow = pHead->m_pNext;
		//1.�ж��Ƿ��л��������������õ������ڵ���ཻλ��
		while (pFast != pSlow)
		{
			if (pFast->m_pNext != nullptr && pFast->m_pNext->m_pNext != nullptr)
				pFast = pFast->m_pNext->m_pNext;
			else
				return nullptr;

			if (pSlow->m_pNext != nullptr)
				pSlow = pSlow->m_pNext;
			else
				return nullptr;
		}
		//2.���㻷�Ľڵ�����ע�������ѭ����������Ȼ�ֻ�����ȥ��
		int num = 1;
		pSlow = pSlow->m_pNext;
		while (pFast != pSlow)
		{
			pSlow = pSlow->m_pNext;
			num++;
		}
		//3.���ݻ��Ľڵ�����������ڽڵ����
		pFast = pHead;
		pSlow = pHead;
		while (num--)
			pFast = pFast->m_pNext;
		while (pFast != pSlow)
		{
			pFast = pFast->m_pNext;
			pSlow = pSlow->m_pNext;
		}
		return pFast;
	}


};

// ==================== Test Code ====================
static void Test(char* testName, ListNode* pHead, ListNode* entryNode)
{
	if (testName != nullptr)
		printf("%s begins: ", testName);

	Solution s;
	if (s.EntryNodeOfLoop(pHead) == entryNode)
		printf("Passed.\n");
	else
		printf("FAILED.\n");
}

// A list has a node, without a loop
static void Test1()
{
	ListNode* pNode1 = CreateListNode(1);

	Test("Test1", pNode1, nullptr);

	DestroyList(pNode1);
}

// A list has a node, with a loop
static void Test2()
{
	ListNode* pNode1 = CreateListNode(1);
	ConnectListNodes(pNode1, pNode1);

	Test("Test2", pNode1, pNode1);

	delete pNode1;
	pNode1 = nullptr;
}

// A list has multiple nodes, with a loop 
static void Test3()
{
	ListNode* pNode1 = CreateListNode(1);
	ListNode* pNode2 = CreateListNode(2);
	ListNode* pNode3 = CreateListNode(3);
	ListNode* pNode4 = CreateListNode(4);
	ListNode* pNode5 = CreateListNode(5);

	ConnectListNodes(pNode1, pNode2);
	ConnectListNodes(pNode2, pNode3);
	ConnectListNodes(pNode3, pNode4);
	ConnectListNodes(pNode4, pNode5);
	ConnectListNodes(pNode5, pNode3);

	Test("Test3", pNode1, pNode3);

	delete pNode1;
	pNode1 = nullptr;
	delete pNode2;
	pNode2 = nullptr;
	delete pNode3;
	pNode3 = nullptr;
	delete pNode4;
	pNode4 = nullptr;
	delete pNode5;
	pNode5 = nullptr;
}

// A list has multiple nodes, with a loop 
static void Test4()
{
	ListNode* pNode1 = CreateListNode(1);
	ListNode* pNode2 = CreateListNode(2);
	ListNode* pNode3 = CreateListNode(3);
	ListNode* pNode4 = CreateListNode(4);
	ListNode* pNode5 = CreateListNode(5);

	ConnectListNodes(pNode1, pNode2);
	ConnectListNodes(pNode2, pNode3);
	ConnectListNodes(pNode3, pNode4);
	ConnectListNodes(pNode4, pNode5);
	ConnectListNodes(pNode5, pNode1);

	Test("Test4", pNode1, pNode1);

	delete pNode1;
	pNode1 = nullptr;
	delete pNode2;
	pNode2 = nullptr;
	delete pNode3;
	pNode3 = nullptr;
	delete pNode4;
	pNode4 = nullptr;
	delete pNode5;
	pNode5 = nullptr;
}

// A list has multiple nodes, with a loop 
static void Test5()
{
	ListNode* pNode1 = CreateListNode(1);
	ListNode* pNode2 = CreateListNode(2);
	ListNode* pNode3 = CreateListNode(3);
	ListNode* pNode4 = CreateListNode(4);
	ListNode* pNode5 = CreateListNode(5);

	ConnectListNodes(pNode1, pNode2);
	ConnectListNodes(pNode2, pNode3);
	ConnectListNodes(pNode3, pNode4);
	ConnectListNodes(pNode4, pNode5);
	ConnectListNodes(pNode5, pNode5);

	Test("Test5", pNode1, pNode5);

	delete pNode1;
	pNode1 = nullptr;
	delete pNode2;
	pNode2 = nullptr;
	delete pNode3;
	pNode3 = nullptr;
	delete pNode4;
	pNode4 = nullptr;
	delete pNode5;
	pNode5 = nullptr;
}

// A list has multiple nodes, without a loop 
static void Test6()
{
	ListNode* pNode1 = CreateListNode(1);
	ListNode* pNode2 = CreateListNode(2);
	ListNode* pNode3 = CreateListNode(3);
	ListNode* pNode4 = CreateListNode(4);
	ListNode* pNode5 = CreateListNode(5);

	ConnectListNodes(pNode1, pNode2);
	ConnectListNodes(pNode2, pNode3);
	ConnectListNodes(pNode3, pNode4);
	ConnectListNodes(pNode4, pNode5);

	Test("Test6", pNode1, nullptr);

	DestroyList(pNode1);
}

// Empty list
static void Test7()
{
	Test("Test7", nullptr, nullptr);
}

int main_offer23(int argc, char* argv[])
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	Test6();
	Test7();

	return 0;
}