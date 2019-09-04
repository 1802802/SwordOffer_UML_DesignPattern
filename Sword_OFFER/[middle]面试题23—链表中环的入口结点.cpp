// 面试题23—链表中环的入口结点
// 题目：给一个链表，若其中包含环，请找出该链表的环的入口结点，否则，输出null。

#include <iostream>
#include "List.h"
using namespace std;


class Solution 
{
	//思路：1、确定链表中是否有环（快指针走2两步，慢指针走1步，慢指针若追上了快指针，则表示有环）
	//2、确定环的入口的方式（假设链表的环有n个节点，则指针P1先移动到n-1的位置，然后指针P1与指针P2同步移动，两指针重合时到达入口节点）
	//3、确定环中的节点数目（1中的快慢指针相遇时位于环中，相遇后任一指针计数向前，当再次相遇时取计数值）
	//4、（隐藏条件）通过数学推导，可以发现1中两指针所相遇的位置，正是2中指针P1应该要移动到的n-1位置

public:
	//根据隐藏条件4，做的代码优化，运行时间：3ms，占用内存：572k
	ListNode* EntryNodeOfLoop(ListNode* pHead)
	{
		if (pHead == nullptr || pHead->m_pNext == nullptr || pHead->m_pNext->m_pNext == nullptr)
			return nullptr;
		//注意初始值，必须先前移一步，不然下面的循环会直接被跳过
		ListNode* pFast = pHead->m_pNext->m_pNext;
		ListNode* pSlow = pHead->m_pNext;
		//1.判断是否有环，如果有则会计算得到快慢节点的相交位置
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
		//2.两指针相遇的位置，正是n-1处的位置，所以不用计算出环长，直接将slow回到首部开始同步移动即可
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
		//注意初始值，必须先前移一步，不然下面的循环会直接被跳过
		ListNode* pFast = pHead->m_pNext->m_pNext;
		ListNode* pSlow = pHead->m_pNext;
		//1.判断是否有环，如果有则会计算得到快慢节点的相交位置
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
		//2.计算环的节点数（注意这里的循环条件，不然又会跳过去）
		int num = 1;
		pSlow = pSlow->m_pNext;
		while (pFast != pSlow)
		{
			pSlow = pSlow->m_pNext;
			num++;
		}
		//3.根据环的节点数，进行入口节点计算
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