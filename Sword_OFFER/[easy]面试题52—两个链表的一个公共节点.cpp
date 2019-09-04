// 面试题52—两个链表的一个公共节点
// 题目：输入两个链表，找出它们的第一个公共结点。

#include <map>
#include <unordered_map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
#include "List.h"
using namespace std;

//struct ListNode
//{
//	int val;
//	struct ListNode *next;
//	ListNode(int x) : val(x), next(NULL) {}
//};

class Solution 
{
public:
	//1.方法1，从两个辅助栈，从尾节点开始比较，时间复杂度O(m+n)，空间复杂度O(m+n)
	//运行时间：3ms，占用内存：612k
	ListNode* FindFirstCommonNode1(ListNode* pHead1, ListNode* pHead2) 
	{
		if (pHead1 == nullptr || pHead2 == nullptr)
			return nullptr;
		stack<ListNode*> astack;
		stack<ListNode*> bstack;
		ListNode* save = nullptr;
		while (pHead1 != nullptr)
		{
			astack.push(pHead1);
			pHead1 = pHead1->m_pNext;
		}
		while (pHead2 != nullptr)
		{
			bstack.push(pHead2);
			pHead2 = pHead2->m_pNext;
		}
		while (!astack.empty() && !bstack.empty())
		{
			//从后往前找，相同则存，无论是否相同都出栈，直到某个栈为空
			if (astack.top() == bstack.top())
				save = astack.top();
			astack.pop(); 
			bstack.pop();
		}
		return save;
	}

	//方法2：先遍历测得两个链表的长度，然后根据短的大小截断长的，再开始比较，时间复杂度O(m+n)，空间复杂度O(1)
	//运行时间：4ms，占用内存：488k
	ListNode* FindFirstCommonNode2(ListNode* pHead1, ListNode* pHead2)
	{
		if (pHead1 == nullptr || pHead2 == nullptr)
			return nullptr;
		int asize = 0;
		int bsize = 0;
		ListNode* Atmp = pHead1;
		ListNode* Btmp = pHead2;
		while (Atmp != nullptr)
		{
			asize++;
			Atmp = Atmp->m_pNext;
		}
		while (Btmp != nullptr)
		{
			bsize++;
			Btmp = Btmp->m_pNext;
		}
		if (asize >= bsize)
		{
			for (int i = 0; i < asize - bsize; i++)
				pHead1 = pHead1->m_pNext;
		}
		else
		{
			for (int i = 0; i < bsize - asize; i++)
				pHead2 = pHead2->m_pNext;
		}
		while (pHead1 != nullptr && pHead2 != nullptr)
		{
			if (pHead1 == pHead2)
				return pHead1;
			pHead1 = pHead1->m_pNext;
			pHead2 = pHead2->m_pNext;
		}
		return nullptr;
	}
};

// ====================测试代码====================
static void DestroyNode(ListNode* pNode);

static void Test(char* testName, ListNode* pHead1, ListNode* pHead2, ListNode* pExpected)
{
	if (testName != nullptr)
		printf("%s begins: ", testName);
	Solution s;
	ListNode* pResult = s.FindFirstCommonNode2(pHead1, pHead2);
	if (pResult == pExpected)
		printf("Passed.\n");
	else
		printf("Failed.\n");
}

// 第一个公共结点在链表中间
// 1 - 2 - 3 \
//            6 - 7
//     4 - 5 /
static void Test1()
{
	ListNode* pNode1 = CreateListNode(1);
	ListNode* pNode2 = CreateListNode(2);
	ListNode* pNode3 = CreateListNode(3);
	ListNode* pNode4 = CreateListNode(4);
	ListNode* pNode5 = CreateListNode(5);
	ListNode* pNode6 = CreateListNode(6);
	ListNode* pNode7 = CreateListNode(7);

	ConnectListNodes(pNode1, pNode2);
	ConnectListNodes(pNode2, pNode3);
	ConnectListNodes(pNode3, pNode6);
	ConnectListNodes(pNode4, pNode5);
	ConnectListNodes(pNode5, pNode6);
	ConnectListNodes(pNode6, pNode7);

	Test("Test1", pNode1, pNode4, pNode6);

	DestroyNode(pNode1);
	DestroyNode(pNode2);
	DestroyNode(pNode3);
	DestroyNode(pNode4);
	DestroyNode(pNode5);
	DestroyNode(pNode6);
	DestroyNode(pNode7);
}

// 没有公共结点
// 1 - 2 - 3 - 4
//            
// 5 - 6 - 7
static void Test2()
{
	ListNode* pNode1 = CreateListNode(1);
	ListNode* pNode2 = CreateListNode(2);
	ListNode* pNode3 = CreateListNode(3);
	ListNode* pNode4 = CreateListNode(4);
	ListNode* pNode5 = CreateListNode(5);
	ListNode* pNode6 = CreateListNode(6);
	ListNode* pNode7 = CreateListNode(7);

	ConnectListNodes(pNode1, pNode2);
	ConnectListNodes(pNode2, pNode3);
	ConnectListNodes(pNode3, pNode4);
	ConnectListNodes(pNode5, pNode6);
	ConnectListNodes(pNode6, pNode7);

	Test("Test2", pNode1, pNode5, nullptr);

	DestroyList(pNode1);
	DestroyList(pNode5);
}

// 公共结点是最后一个结点
// 1 - 2 - 3 - 4 \
//                7
//         5 - 6 /
static void Test3()
{
	ListNode* pNode1 = CreateListNode(1);
	ListNode* pNode2 = CreateListNode(2);
	ListNode* pNode3 = CreateListNode(3);
	ListNode* pNode4 = CreateListNode(4);
	ListNode* pNode5 = CreateListNode(5);
	ListNode* pNode6 = CreateListNode(6);
	ListNode* pNode7 = CreateListNode(7);

	ConnectListNodes(pNode1, pNode2);
	ConnectListNodes(pNode2, pNode3);
	ConnectListNodes(pNode3, pNode4);
	ConnectListNodes(pNode4, pNode7);
	ConnectListNodes(pNode5, pNode6);
	ConnectListNodes(pNode6, pNode7);

	Test("Test3", pNode1, pNode5, pNode7);

	DestroyNode(pNode1);
	DestroyNode(pNode2);
	DestroyNode(pNode3);
	DestroyNode(pNode4);
	DestroyNode(pNode5);
	DestroyNode(pNode6);
	DestroyNode(pNode7);
}

// 公共结点是第一个结点
// 1 - 2 - 3 - 4 - 5
// 两个链表完全重合   
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

	Test("Test4", pNode1, pNode1, pNode1);

	DestroyList(pNode1);
}

// 输入的两个链表有一个空链表
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

	Test("Test5", nullptr, pNode1, nullptr);

	DestroyList(pNode1);
}

// 输入的两个链表有一个空链表
static void Test6()
{
	Test("Test6", nullptr, nullptr, nullptr);
}

static void DestroyNode(ListNode* pNode)
{
	delete pNode;
	pNode = nullptr;
}

int main_offer52(int argc, char* argv[])
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	Test6();

	return 0;
}