/*
面试题22—链表中的倒数第k个节点
题目：输入一个链表，输出该链表中倒数第k个结点。
*/

#include <iostream>
#include <vector>
#include "List.h"
using namespace std;

//举一反三：双指针遍历链表实现一次遍历解决问题（如先走k-1步实现倒数k节点问题，走两步与走一步的中间节点问题）

//双指针行进法：指针1走到第k-1个节点后，指针2跟着开始走；当指针1走到第n个节点后，指针2走到了第n-k+1个节点
//运行时间：4ms，占用内存：468k
ListNode* FindKthToTail(ListNode* pListHead, unsigned int k)
{
	if (pListHead == nullptr || k == 0)
		return nullptr;
	ListNode* node1 = pListHead;
	ListNode* node2 = nullptr;
	//无符号数0减1会造成k无限大，所以直接在开始时将k=0拦死
	int num = k - 1;

	while (num--)
	{
		//拦住使node1变成nullptr与num过大的情况
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

// ====================测试代码====================
// 测试要找的结点在链表中间
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

// 测试要找的结点是链表的尾结点
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

// 测试要找的结点是链表的头结点
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

// 测试空链表
static void Test4()
{
	printf("=====Test4 starts:=====\n");
	printf("expected result: nullptr.\n");
	ListNode* pNode = FindKthToTail(nullptr, 100);
	PrintListNode(pNode);
}

// 测试输入的第二个参数大于链表的结点总数
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

// 测试输入的第二个参数为0
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