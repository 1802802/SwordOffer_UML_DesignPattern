// 面试题35—复杂链表的复制
// 题目：输入一个复杂链表
// （每个节点中有节点值，以及两个指针，一个指向下一个节点，另一个特殊指针指向任意一个节点，
// 返回结果为复制后复杂链表的head。（注意，输出结果中请不要返回参数中的节点引用，否则判题程序会直接返回空）

#include <iostream>
#include <vector>
#include <map>
#include "List.h"
using namespace std;

struct RandomListNode 
{
	int label;
	struct RandomListNode *next, *random;
	RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
};

struct ComplexListNode
{
	int                 m_nValue;
	ComplexListNode*    m_pNext;
	ComplexListNode*    m_pSibling;
};

ComplexListNode* CreateNode(int nValue)
{
	ComplexListNode* pNode = new ComplexListNode();

	pNode->m_nValue = nValue;
	pNode->m_pNext = nullptr;
	pNode->m_pSibling = nullptr;

	return pNode;
}

static void BuildNodes(ComplexListNode* pNode, ComplexListNode* pNext, ComplexListNode* pSibling)
{
	if (pNode != nullptr)
	{
		pNode->m_pNext = pNext;
		pNode->m_pSibling = pSibling;
	}
}

static void PrintList(ComplexListNode* pHead)
{
	ComplexListNode* pNode = pHead;
	while (pNode != nullptr)
	{
		printf("The value of this node is: %d.\n", pNode->m_nValue);

		if (pNode->m_pSibling != nullptr)
			printf("The value of its sibling is: %d.\n", pNode->m_pSibling->m_nValue);
		else
			printf("This node does not have a sibling.\n");

		printf("\n");

		pNode = pNode->m_pNext;
	}
}

class Solution 
{
public:
	//1.书上的高级做法，分为三个函数（这个算法的思想可以好好理解，但是手撕的话可能难度真的较大）
	ComplexListNode* Clone(ComplexListNode* pHead)
	{
		CloneNodes(pHead);
		ConnectSiblingNodes(pHead);
		return ReconnectNodes(pHead);
	}
	//1.1第一个函数，实现复制原始链表的任意节点N并创建新节点N'，再把N'链接到N的后面
	void CloneNodes(ComplexListNode* pHead)
	{
		ComplexListNode* pNode = pHead;
		while (pNode != nullptr)
		{
			ComplexListNode* pCloned = new ComplexListNode();
			pCloned->m_nValue = pNode->m_nValue;
			pCloned->m_pNext = pNode->m_pNext;
			pCloned->m_pSibling = nullptr;
		
			pNode->m_pNext = pCloned;
			pNode = pCloned->m_pNext;
		}
	}
	//1.2建立第二个函数，实现原始链表上N指向S的Sibling，成为N'指向S'的Sibling（不断地后移变化）
	void ConnectSiblingNodes(ComplexListNode* pHead)
	{
		ComplexListNode* pNode = pHead;
		while (pNode != nullptr)
		{
			ComplexListNode* pClone = pNode->m_pNext;
			if (pNode->m_pSibling != nullptr)
				pClone->m_pSibling = pNode->m_pSibling->m_pNext;
			else
				pClone->m_pSibling = nullptr;
			pNode = pClone->m_pNext;
		}
	}
	//1.3 建立第三个函数，将已经完成的克隆表从现在的双表结构中删除出来（从0开始算，偶数位置的为原表，奇数位置的为克隆表）
	ComplexListNode* ReconnectNodes(ComplexListNode* pHead)
	{
		ComplexListNode* pNode = pHead;
		ComplexListNode* pCloneHead = nullptr;
		ComplexListNode* pCloneNode = nullptr;

		//完成首元素的记录操作与后移
		if (pNode != nullptr)
		{
			pCloneHead = pCloneNode = pNode->m_pNext;
			pNode->m_pNext = pCloneHead->m_pNext;
			pNode = pNode->m_pNext;
		}
		//while循环实现链表分离（里面涉及到两个元素交换和next指向交换，要多留心思考）
		while (pNode != nullptr)
		{
			pCloneNode->m_pNext = pNode->m_pNext;
			pCloneNode = pCloneNode->m_pNext;
			pNode->m_pNext = pCloneNode->m_pNext;
			pNode = pNode->m_pNext;
		}
		return pCloneHead;
	}


	//2.采用map存clone与原node的对应关系，实现O(n)时间O(n)空间的实现方式（写的很杂乱，说实话不好看懂）
	//运行时间：4ms，占用内存：608k
	ComplexListNode* Clone2(ComplexListNode* pHead)
	{
		//1.1边界条件
		if (pHead == nullptr)
			return nullptr;
		//1.2链表克隆操作
		map<ComplexListNode*, ComplexListNode*> node2node;
		ComplexListNode* pClone = new ComplexListNode();     pClone->m_nValue = pHead->m_nValue;
		ComplexListNode* pCloneHead = pClone;
		ComplexListNode* pBackHead = pHead;
		node2node.insert({ pBackHead ,pCloneHead });
		pHead = pHead->m_pNext;
		while (pHead != nullptr)
		{
			ComplexListNode* pNode = new ComplexListNode();  pNode->m_nValue = pHead->m_nValue;
			node2node.insert({ pHead ,pNode });
			pHead = pHead->m_pNext;
			pClone->m_pNext = pNode;
			pClone = pNode;		
		}
		//1.3通过map实现两表的sibl复制
		for (auto &s : node2node)
		{
			if (s.first->m_pSibling != nullptr)
				s.second->m_pSibling = node2node[s.first->m_pSibling];
			else
				s.second->m_pSibling = nullptr;
		}
		return pCloneHead;
	}


	//3尝试基础解法，即O(n2)时间复杂度，O(1)空间复杂度的操作（时间过程太蠢了，选择不实现）
	ComplexListNode* Clone3(ComplexListNode* pHead)
	{
		//1.1边界条件
		if (pHead == nullptr)
			return nullptr;
		//1.2链表克隆操作
		ComplexListNode* pClone = new ComplexListNode();
		pClone->m_nValue = pHead->m_nValue;
		ComplexListNode* pCloneHead = pClone;
		ComplexListNode* pBackHead = pHead;
		pHead = pHead->m_pNext;
		while (pHead != nullptr)
		{
			ComplexListNode* pNode = new ComplexListNode();
			pNode->m_nValue = pHead->m_nValue;
			pHead = pHead->m_pNext;
			pClone->m_pNext = pNode;
			pClone = pNode;
		}
		//1.3实现m_pSibling
		pClone = pCloneHead;
		pHead = pBackHead;
		while (pHead != nullptr)
		{
			ComplexListNode* pNode = pHead->m_pSibling;
			if (pNode != nullptr)
			{
				int n = 0;
				pHead = pHead->m_pNext;
				while (pHead != nullptr)
				{
					if (pNode == pHead->m_pSibling)
						break;
					pHead = pHead->m_pNext;
					n++;
				}
			}
		}
	}
};


// ====================测试代码====================
static void Test(const char* testName, ComplexListNode* pHead)
{
	if (testName != nullptr)
		printf("%s begins:\n", testName);

	printf("The original list is:\n");
	PrintList(pHead);

	Solution s;
	ComplexListNode* pClonedHead = s.Clone(pHead);

	printf("The cloned list is:\n");
	PrintList(pClonedHead);
}

//          -----------------
//         \|/              |
//  1-------2-------3-------4-------5
//  |       |      /|\             /|\
//  --------+--------               |
//          -------------------------
static void Test1()
{
	ComplexListNode* pNode1 = CreateNode(1);
	ComplexListNode* pNode2 = CreateNode(2);
	ComplexListNode* pNode3 = CreateNode(3);
	ComplexListNode* pNode4 = CreateNode(4);
	ComplexListNode* pNode5 = CreateNode(5);

	BuildNodes(pNode1, pNode2, pNode3);
	BuildNodes(pNode2, pNode3, pNode5);
	BuildNodes(pNode3, pNode4, nullptr);
	BuildNodes(pNode4, pNode5, pNode2);

	Test("Test1", pNode1);
}

// m_pSibling指向结点自身
//          -----------------
//         \|/              |
//  1-------2-------3-------4-------5
//         |       | /|\           /|\
//         |       | --             |
//         |------------------------|
static void Test2()
{
	ComplexListNode* pNode1 = CreateNode(1);
	ComplexListNode* pNode2 = CreateNode(2);
	ComplexListNode* pNode3 = CreateNode(3);
	ComplexListNode* pNode4 = CreateNode(4);
	ComplexListNode* pNode5 = CreateNode(5);

	BuildNodes(pNode1, pNode2, nullptr);
	BuildNodes(pNode2, pNode3, pNode5);
	BuildNodes(pNode3, pNode4, pNode3);
	BuildNodes(pNode4, pNode5, pNode2);

	Test("Test2", pNode1);
}

// m_pSibling形成环
//          -----------------
//         \|/              |
//  1-------2-------3-------4-------5
//          |              /|\
//          |               |
//          |---------------|
static void Test3()
{
	ComplexListNode* pNode1 = CreateNode(1);
	ComplexListNode* pNode2 = CreateNode(2);
	ComplexListNode* pNode3 = CreateNode(3);
	ComplexListNode* pNode4 = CreateNode(4);
	ComplexListNode* pNode5 = CreateNode(5);

	BuildNodes(pNode1, pNode2, nullptr);
	BuildNodes(pNode2, pNode3, pNode4);
	BuildNodes(pNode3, pNode4, nullptr);
	BuildNodes(pNode4, pNode5, pNode2);

	Test("Test3", pNode1);
}

// 只有一个结点
static void Test4()
{
	ComplexListNode* pNode1 = CreateNode(1);
	BuildNodes(pNode1, nullptr, pNode1);

	Test("Test4", pNode1);
}

// 鲁棒性测试
static void Test5()
{
	Test("Test5", nullptr);
}

int main_offer35(int argc, char* argv[])
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();

	return 0;
}

//int main()
//{
//	ComplexListNode* n1 = new ComplexListNode();
//	ComplexListNode* n2 = new ComplexListNode();
//	ComplexListNode* n3 = new ComplexListNode();
//	ComplexListNode* n4 = new ComplexListNode();
//
//	n1->m_nValue = 1;
//	n2->m_nValue = 2;
//	n3->m_nValue = 3;
//	n4->m_nValue = 4;
//
//	n1->m_pNext = n2;
//	n2->m_pNext = n3;
//	n3->m_pNext = n4;
//
//	Solution s;
//	s.Clone(n1);
//}



//if (pHead == nullptr)
//return nullptr;
//ComplexListNode* pClone = new ComplexListNode();
//pClone->m_nValue = pHead->m_nValue;
//pHead = pHead->m_pNext;
//while (pHead != nullptr)
//{
//	ComplexListNode* pNode = new ComplexListNode();
//	pNode->m_nValue = pHead->m_nValue;
//	pClone->m_pNext = pNode;
//	pClone = pNode;
//}