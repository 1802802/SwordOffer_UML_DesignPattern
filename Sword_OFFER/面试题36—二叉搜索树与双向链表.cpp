// ������36��������������˫������
// ��Ŀ������һ����������
// ��ÿ���ڵ����нڵ�ֵ���Լ�����ָ�룬һ��ָ����һ���ڵ㣬��һ������ָ��ָ������һ���ڵ㣬
// ���ؽ��Ϊ���ƺ��������head����ע�⣬���������벻Ҫ���ز����еĽڵ����ã�������������ֱ�ӷ��ؿգ�

#include <iostream>
#include <vector>
#include <map>
#include "BinaryTree.h"
using namespace std;

class Solution 
{
public:
	//���Ų����������˼��ʵ�֣�����ĸ���ʼֵ����Ҫ������ʱ�䣺4ms��ռ���ڴ棺376k
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
		//�ݹ���������ڵ�Ϊnullptrʱ����
		if (pRootOfTree == nullptr)
			return;
		ConvertNode(pRootOfTree->m_pLeft);

		//ֻ��pre�͵�ǰ�ڵ��ָ���������
		if (pre != nullptr)
		{
			pRootOfTree->m_pLeft = pre;
			pre->m_pRight = pRootOfTree;
		}
		pre = pRootOfTree;

		//ͷ�ڵ�Ĵ洢
		if (head == nullptr)
			head = pre;

		ConvertNode(pRootOfTree->m_pRight);
	}
};

// ====================���Դ���====================
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

// ����ֻ��1�����
static void Test4()
{
	BinaryTreeNode* pNode1 = CreateBinaryTreeNode(1);
	Test("Test4", pNode1);

	DestroyList(pNode1);
}

// ����û�н��
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