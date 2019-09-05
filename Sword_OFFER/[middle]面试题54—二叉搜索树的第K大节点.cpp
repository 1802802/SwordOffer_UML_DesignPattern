// ������54�������������ĵ�K��ڵ�
// ��Ŀ������һ�ö��������������ҳ����еĵ�kС�Ľ�㡣
// ���磬��5��3��7��2��4��6��8���У��������ֵ��С˳�����С����ֵΪ4��

#include <map>
#include <unordered_map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
#include "BinaryTree.h"
using namespace std;

//���ڶ�����������������������м�Ϊһ���������У������������˳��ʵ�ּ���
//ע���0��Ӧ��Ϊ-1����0�������ڣ���Ҫ�ӵ�һ����ʼ����
class Solution
{
public:
	//1.������
	BinaryTreeNode* KthNode(BinaryTreeNode* pRoot, int k)
	{
		pNode = nullptr;
		if (pRoot == nullptr || k == 0)
			return pNode;
		//travMid_Recursion(pRoot, k);
		travMid_Circulate(pRoot, k);
		return pNode;
	}

	//2.��������ݹ麯��������ʱ�䣺4ms��ռ���ڴ棺476k
	void travMid_Recursion(BinaryTreeNode* pRoot, int& k)
	{
		if (pRoot->m_pLeft != nullptr)
			travMid_Recursion(pRoot->m_pLeft, k);

		//���������ÿ�˲���
		if (k == 1)
			pNode = pRoot;
		k--;
		//��֦
		if (k == 0)
			return;

		if (pRoot->m_pRight != nullptr)
			travMid_Recursion(pRoot->m_pRight, k);
	}

	//3.�������ѭ�������������ң���������Ϊ�ڵ�Ϊnullptr��ջΪ�գ�
	void travMid_Circulate(BinaryTreeNode* pRoot, int& k)
	{
		stack<BinaryTreeNode*> m_stack;

		do
		{
			while (pRoot != nullptr)
			{
				m_stack.push(pRoot);
				pRoot = pRoot->m_pLeft;
			}
			if (!m_stack.empty())
			{
				pRoot = m_stack.top(); m_stack.pop();
				//ÿ�˲������ж�kֵ��ȷ��node���֦��
				if (k == 1)
					pNode = pRoot;
				k--;
				if (k == 0)
					return;
				pRoot = pRoot->m_pRight;
			}
		} while (!m_stack.empty() || pRoot != nullptr);
	}

private:
	BinaryTreeNode* pNode;
};

// ====================���Դ���====================
static void Test(const char* testName, BinaryTreeNode* pRoot, unsigned int k, bool isNull, int expected)
{
	if (testName != nullptr)
		printf("%s begins: ", testName);

	Solution s;

	const BinaryTreeNode* pTarget = s.KthNode(pRoot, k);
	if ((isNull && pTarget == nullptr) || (!isNull && pTarget->m_nValue == expected))
		printf("Passed.\n");
	else
		printf("FAILED.\n");
}

//            8
//        6      10
//       5 7    9  11
static void TestA()
{
	BinaryTreeNode* pNode8 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNode6 = CreateBinaryTreeNode(6);
	BinaryTreeNode* pNode10 = CreateBinaryTreeNode(10);
	BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);
	BinaryTreeNode* pNode7 = CreateBinaryTreeNode(7);
	BinaryTreeNode* pNode9 = CreateBinaryTreeNode(9);
	BinaryTreeNode* pNode11 = CreateBinaryTreeNode(11);

	ConnectTreeNodes(pNode8, pNode6, pNode10);
	ConnectTreeNodes(pNode6, pNode5, pNode7);
	ConnectTreeNodes(pNode10, pNode9, pNode11);

	Test("TestA0", pNode8, 0, true, -1);
	Test("TestA1", pNode8, 1, false, 5);
	Test("TestA2", pNode8, 2, false, 6);
	Test("TestA3", pNode8, 3, false, 7);
	Test("TestA4", pNode8, 4, false, 8);
	Test("TestA5", pNode8, 5, false, 9);
	Test("TestA6", pNode8, 6, false, 10);
	Test("TestA7", pNode8, 7, false, 11);
	Test("TestA8", pNode8, 8, true, -1);

	DestroyTree(pNode8);

	printf("\n\n");
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
static void TestB()
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

	Test("TestB0", pNode5, 0, true, -1);
	Test("TestB1", pNode5, 1, false, 1);
	Test("TestB2", pNode5, 2, false, 2);
	Test("TestB3", pNode5, 3, false, 3);
	Test("TestB4", pNode5, 4, false, 4);
	Test("TestB5", pNode5, 5, false, 5);
	Test("TestB6", pNode5, 6, true, -1);

	DestroyTree(pNode5);

	printf("\n\n");
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
static void TestC()
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

	Test("TestC0", pNode1, 0, true, -1);
	Test("TestC1", pNode1, 1, false, 1);
	Test("TestC2", pNode1, 2, false, 2);
	Test("TestC3", pNode1, 3, false, 3);
	Test("TestC4", pNode1, 4, false, 4);
	Test("TestC5", pNode1, 5, false, 5);
	Test("TestC6", pNode1, 6, true, -1);

	DestroyTree(pNode1);

	printf("\n\n");
}

// There is only one node in a tree
static void TestD()
{
	BinaryTreeNode* pNode1 = CreateBinaryTreeNode(1);

	Test("TestD0", pNode1, 0, true, -1);
	Test("TestD1", pNode1, 1, false, 1);
	Test("TestD2", pNode1, 2, true, -1);

	DestroyTree(pNode1);

	printf("\n\n");
}

// empty tree
static void TestE()
{
	Test("TestE0", nullptr, 0, true, -1);
	Test("TestE1", nullptr, 1, true, -1);

	printf("\n\n");
}

int main_offer54(int argc, char* argv[])
{
	TestA();
	TestB();
	TestC();
	TestD();
	TestE();

	return 0;
}