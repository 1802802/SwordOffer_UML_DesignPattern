// ������32.1���������´�ӡ�������������У�
// ��Ŀ���������´�ӡ����������ÿ���ڵ㣬ͬ��ڵ�������Ҵ�ӡ��

#include <iostream>
#include <vector>
#include <queue>
#include "BinaryTree.h"
using namespace std;

class Solution 
{
public:
	//˼·���ܼ򵥵�һ���ö���ʵ�ֵĲ������������ʱ�䣺4ms��ռ���ڴ棺472k
	vector<int> PrintFromTopToBottom(BinaryTreeNode* root) 
	{
		queue<BinaryTreeNode*> saveQueue;
		vector<int> saveVector;

		if (root == nullptr)
			return saveVector;

		saveQueue.push(root);
		while (!saveQueue.empty())
		{
			root = saveQueue.front(); saveQueue.pop();
			saveVector.push_back(root->m_nValue);
			if (root->m_pLeft != nullptr)
				saveQueue.push(root->m_pLeft);
			if (root->m_pRight != nullptr)
				saveQueue.push(root->m_pRight);
		}
		return saveVector;
	}
};

// ====================���Դ���====================
static void Test(char* testName, BinaryTreeNode* pRoot)
{
	if (testName != nullptr)
		printf("%s begins: \n", testName);

	PrintTree(pRoot);

	Solution s;
	printf("The nodes from top to bottom, from left to right are: \n");
	vector<int> tmp = s.PrintFromTopToBottom(pRoot);
	for (auto &s : tmp)
		cout << s << " ";
	cout << endl;

	printf("\n\n");
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

	DestroyTree(pNode10);
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

	DestroyTree(pNode5);
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

	DestroyTree(pNode1);
}

// ����ֻ��1�����
static void Test4()
{
	BinaryTreeNode* pNode1 = CreateBinaryTreeNode(1);
	Test("Test4", pNode1);

	DestroyTree(pNode1);
}

// ����û�н��
static void Test5()
{
	Test("Test5", nullptr);
}

int main_offer32_1(int argc, char* argv[])
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();

	return 0;
}