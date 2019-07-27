// 面试题24—反转链表
// 题目：输入一个链表，反转链表后，输出新链表的表头。

#include <iostream>
#include <string>
#include "List.h"
using namespace std;

class Solution 
{
public:
	//为了保证链表在反转时不断裂，需要记录三个节点：当前节点，当前节点的前一节点与后一节点
	//运行时间：3ms，占用内存：456k
	ListNode* ReverseList(ListNode* pHead) 
	{
		if (pHead == nullptr)
			return nullptr;

		ListNode* pPrevNode = nullptr;
		ListNode* pNode = pHead;
		ListNode* pPostNode = nullptr;

		while (pNode != nullptr)
		{
			pPostNode = pNode->m_pNext;
			pNode->m_pNext = pPrevNode;
			pPrevNode = pNode;
			pNode = pPostNode;
		}
		//最后分析可得，当达到pNode为nullptr时，其前节点为最后的头节点
		return pPrevNode;
	}
};

// ====================测试代码====================
ListNode* Test(ListNode* pHead)
{
	printf("The original list is: \n");
	PrintList(pHead);
	Solution s;
	ListNode* pReversedHead = s.ReverseList(pHead);

	printf("The reversed list is: \n");
	PrintList(pReversedHead);

	return pReversedHead;
}

// 输入的链表有多个结点
static void Test1()
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

	ListNode* pReversedHead = Test(pNode1);

	DestroyList(pReversedHead);
}

// 输入的链表只有一个结点
static void Test2()
{
	ListNode* pNode1 = CreateListNode(1);

	ListNode* pReversedHead = Test(pNode1);

	DestroyList(pReversedHead);
}

// 输入空链表
static void Test3()
{
	Test(nullptr);
}

int main_offer24(int argc, char* argv[])
{
	Test1();
	Test2();
	Test3();

	return 0;
}