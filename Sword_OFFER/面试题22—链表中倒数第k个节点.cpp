/*
������22�������еĵ�����k���ڵ�
��Ŀ������һ����������������е�����k����㡣
*/

#include <iostream>
#include <vector>
#include "List.h"
using namespace std;

//��һ������˫ָ���������ʵ��һ�α���������⣨������k-1��ʵ�ֵ���k�ڵ����⣬����������һ�����м�ڵ����⣩

//˫ָ���н�����ָ��1�ߵ���k-1���ڵ��ָ��2���ſ�ʼ�ߣ���ָ��1�ߵ���n���ڵ��ָ��2�ߵ��˵�n-k+1���ڵ�
//����ʱ�䣺4ms��ռ���ڴ棺468k
ListNode* FindKthToTail(ListNode* pListHead, unsigned int k)
{
	if (pListHead == nullptr || k == 0)
		return nullptr;
	ListNode* node1 = pListHead;
	ListNode* node2 = nullptr;
	//�޷�����0��1�����k���޴�����ֱ���ڿ�ʼʱ��k=0����
	int num = k - 1;

	while (num--)
	{
		//��סʹnode1���nullptr��num��������
		if (node1->m_pNext == nullptr && num >= 0)
			return nullptr;
		node1 = node1->m_pNext;
	}

	node2 = pListHead;

	while (node1->m_pNext != nullptr)
	{
		node1 = node1->m_pNext;
		node2 = node2->m_pNext;
	}

	return node2;

}

// ====================���Դ���====================
// ����Ҫ�ҵĽ���������м�
static void Test1()
{
	printf("=====Test1 starts:=====\n");
	ListNode* pNode1 = CreateListNode(1);
	ListNode* pNode2 = CreateListNode(2);
	ListNode* pNode3 = CreateListNode(3);
	ListNode* pNode4 = CreateListNode(4);
	ListNode* pNode5 = CreateListNode(5);

	ConnectListNodes(pNode1, pNode2);
	ConnectListNodes(pNode2, pNode3);
	ConnectListNodes(pNode3, pNode4);
	ConnectListNodes(pNode4, pNode5);

	printf("expected result: 4.\n");
	ListNode* pNode = FindKthToTail(pNode1, 2);
	PrintListNode(pNode);

	DestroyList(pNode1);
}

// ����Ҫ�ҵĽ���������β���
static void Test2()
{
	printf("=====Test2 starts:=====\n");
	ListNode* pNode1 = CreateListNode(1);
	ListNode* pNode2 = CreateListNode(2);
	ListNode* pNode3 = CreateListNode(3);
	ListNode* pNode4 = CreateListNode(4);
	ListNode* pNode5 = CreateListNode(5);

	ConnectListNodes(pNode1, pNode2);
	ConnectListNodes(pNode2, pNode3);
	ConnectListNodes(pNode3, pNode4);
	ConnectListNodes(pNode4, pNode5);

	printf("expected result: 5.\n");
	ListNode* pNode = FindKthToTail(pNode1, 1);
	PrintListNode(pNode);

	DestroyList(pNode1);
}

// ����Ҫ�ҵĽ���������ͷ���
static void Test3()
{
	printf("=====Test3 starts:=====\n");
	ListNode* pNode1 = CreateListNode(1);
	ListNode* pNode2 = CreateListNode(2);
	ListNode* pNode3 = CreateListNode(3);
	ListNode* pNode4 = CreateListNode(4);
	ListNode* pNode5 = CreateListNode(5);

	ConnectListNodes(pNode1, pNode2);
	ConnectListNodes(pNode2, pNode3);
	ConnectListNodes(pNode3, pNode4);
	ConnectListNodes(pNode4, pNode5);

	printf("expected result: 1.\n");
	ListNode* pNode = FindKthToTail(pNode1, 5);
	PrintListNode(pNode);

	DestroyList(pNode1);
}

// ���Կ�����
static void Test4()
{
	printf("=====Test4 starts:=====\n");
	printf("expected result: nullptr.\n");
	ListNode* pNode = FindKthToTail(nullptr, 100);
	PrintListNode(pNode);
}

// ��������ĵڶ���������������Ľ������
static void Test5()
{
	printf("=====Test5 starts:=====\n");
	ListNode* pNode1 = CreateListNode(1);
	ListNode* pNode2 = CreateListNode(2);
	ListNode* pNode3 = CreateListNode(3);
	ListNode* pNode4 = CreateListNode(4);
	ListNode* pNode5 = CreateListNode(5);

	ConnectListNodes(pNode1, pNode2);
	ConnectListNodes(pNode2, pNode3);
	ConnectListNodes(pNode3, pNode4);
	ConnectListNodes(pNode4, pNode5);

	printf("expected result: nullptr.\n");
	ListNode* pNode = FindKthToTail(pNode1, 6);
	PrintListNode(pNode);

	DestroyList(pNode1);
}

// ��������ĵڶ�������Ϊ0
static void Test6()
{
	printf("=====Test6 starts:=====\n");
	ListNode* pNode1 = CreateListNode(1);
	ListNode* pNode2 = CreateListNode(2);
	ListNode* pNode3 = CreateListNode(3);
	ListNode* pNode4 = CreateListNode(4);
	ListNode* pNode5 = CreateListNode(5);

	ConnectListNodes(pNode1, pNode2);
	ConnectListNodes(pNode2, pNode3);
	ConnectListNodes(pNode3, pNode4);
	ConnectListNodes(pNode4, pNode5);

	printf("expected result: nullptr.\n");
	ListNode* pNode = FindKthToTail(pNode1, 0);
	PrintListNode(pNode);

	DestroyList(pNode1);
}

int main_offer22(int argc, char* argv[])
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	Test6();

	return 0;
}