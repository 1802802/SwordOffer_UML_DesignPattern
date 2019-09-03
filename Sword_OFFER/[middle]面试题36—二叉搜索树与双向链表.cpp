// 面试题36—二叉搜索树与双向链表
// 题目：输入一个复杂链表
// （每个节点中有节点值，以及两个指针，一个指向下一个节点，另一个特殊指针指向任意一个节点，
// 返回结果为复制后复杂链表的head。（注意，输出结果中请不要返回参数中的节点引用，否则判题程序会直接返回空）

#include <iostream>
#include <vector>
#include <map>
#include "BinaryTree.h"
using namespace std;

class Solution 
{
public:
	//试着采用中序遍历思想实现（这里的赋初始值很重要）运行时间：4ms，占用内存：376k
	BinaryTreeNode* pre = nullptr;
	BinaryTreeNode* head = nullptr;
	BinaryTreeNode* Convert(BinaryTreeNode* pRootOfTree)
	{
		if (pRootOfTree == nullptr)
			return nullptr;
		ConvertNode(pRootOfTree);
		return head;
	}
	void ConvertNode(BinaryTreeNode* pRootOfTree)
	{
		//递归基，当根节点为nullptr时返回
		if (pRootOfTree == nullptr)
			return;
		ConvertNode(pRootOfTree->m_pLeft);

		//只将pre和当前节点的指向进行重连
		if (pre != nullptr)
		{
			pRootOfTree->m_pLeft = pre;
			pre->m_pRight = pRootOfTree;
		}
		pre = pRootOfTree;

		//头节点的存储
		if (head == nullptr)
			head = pre;

		ConvertNode(pRootOfTree->m_pRight);
	}
};

// ====================测试代码====================
static void PrintDoubleLinkedList(BinaryTreeNode* pHeadOfList)
{
	BinaryTreeNode* pNode = pHeadOfList;

	printf("The nodes from left to right are:\n");
	while (pNode != nullptr)
	{
		printf("%d\t", pNode->m_nValue);

		if (pNode->m_pRight == nullptr)
			break;
		pNode = pNode->m_pRight;
	}

	printf("\nThe nodes from right to left are:\n");
	while (pNode != nullptr)
	{
		printf("%d\t", pNode->m_nValue);

		if (pNode->m_pLeft == nullptr)
			break;
		pNode = pNode->m_pLeft;
	}

	printf("\n");
}

static void DestroyList(BinaryTreeNode* pHeadOfList)
{
	BinaryTreeNode* pNode = pHeadOfList;
	while (pNode != nullptr)
	{
		BinaryTreeNode* pNext = pNode->m_pRight;

		delete pNode;
		pNode = pNext;
	}
}

static void Test(char* testName, BinaryTreeNode* pRootOfTree)
{
	if (testName != nullptr)
		printf("%s begins:\n", testName);

	PrintTree(pRootOfTree);

	Solution s;
	BinaryTreeNode* pHeadOfList = s.Convert(pRootOfTree);

	PrintDoubleLinkedList(pHeadOfList);
}

//            10
//         /      \
//        6        14
//       /\        /\
//      4  8     12  16
static void Test1()
{
	BinaryTreeNode* pNode10 = CreateBinaryTreeNode(10);
	BinaryTreeNode* pNode6 = CreateBinaryTreeNode(6);
	BinaryTreeNode* pNode14 = CreateBinaryTreeNode(14);
	BinaryTreeNode* pNode4 = CreateBinaryTreeNode(4);
	BinaryTreeNode* pNode8 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNode12 = CreateBinaryTreeNode(12);
	BinaryTreeNode* pNode16 = CreateBinaryTreeNode(16);

	ConnectTreeNodes(pNode10, pNode6, pNode14);
	ConnectTreeNodes(pNode6, pNode4, pNode8);
	ConnectTreeNodes(pNode14, pNode12, pNode16);

	Test("Test1", pNode10);

	DestroyList(pNode4);
}

//               5
//              /
//             4
//            /
//           3
//          /
//         2
//        /
//       1
static void Test2()
{
	BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);
	BinaryTreeNode* pNode4 = CreateBinaryTreeNode(4);
	BinaryTreeNode* pNode3 = CreateBinaryTreeNode(3);
	BinaryTreeNode* pNode2 = CreateBinaryTreeNode(2);
	BinaryTreeNode* pNode1 = CreateBinaryTreeNode(1);

	ConnectTreeNodes(pNode5, pNode4, nullptr);
	ConnectTreeNodes(pNode4, pNode3, nullptr);
	ConnectTreeNodes(pNode3, pNode2, nullptr);
	ConnectTreeNodes(pNode2, pNode1, nullptr);

	Test("Test2", pNode5);

	DestroyList(pNode1);
}

// 1
//  \
//   2
//    \
//     3
//      \
//       4
//        \
//         5
static void Test3()
{
	BinaryTreeNode* pNode1 = CreateBinaryTreeNode(1);
	BinaryTreeNode* pNode2 = CreateBinaryTreeNode(2);
	BinaryTreeNode* pNode3 = CreateBinaryTreeNode(3);
	BinaryTreeNode* pNode4 = CreateBinaryTreeNode(4);
	BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);

	ConnectTreeNodes(pNode1, nullptr, pNode2);
	ConnectTreeNodes(pNode2, nullptr, pNode3);
	ConnectTreeNodes(pNode3, nullptr, pNode4);
	ConnectTreeNodes(pNode4, nullptr, pNode5);

	Test("Test3", pNode1);

	DestroyList(pNode1);
}

// 树中只有1个结点
static void Test4()
{
	BinaryTreeNode* pNode1 = CreateBinaryTreeNode(1);
	Test("Test4", pNode1);

	DestroyList(pNode1);
}

// 树中没有结点
static void Test5()
{
	Test("Test5", nullptr);
}

int main_offer36(int argc, char* argv[])
{
	Test1();
	Test2(); 
	Test3();
	Test4();
	Test5();

	return 0;
}