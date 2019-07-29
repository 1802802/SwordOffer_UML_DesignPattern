// 面试题32.2—从上往下打印二叉树（分行）
// 题目：从上到下按层打印二叉树，同一层结点从左至右输出。每一层输出一行。

#include <iostream>
#include <vector>
#include <queue>
#include "BinaryTree.h"
using namespace std;

class Solution 
{
public:
	//思路：分行打印的常规思路依然是队列实现，但是需要额外变量来实现每行数据存储操作（其实好像直接用另一个队列存就可以了，甚至用一个队列数组来回倒更好）
	//三个变量：一个存当前行，一个存下一行所需要打印的节点和，一个存当前需要打印的节点，运行时间：3ms，占用内存：608k
	vector<vector<int> > Print1(BinaryTreeNode* pRoot) 
	{
		if (pRoot == nullptr)
			return vector<vector<int> >();

		queue<BinaryTreeNode*> saveQueue;
		vector<vector<int> > saveVector(1);

		int currentLevelNodes = 1;
		int nextLevelNodes = 0;
		int currentLevel = 0;

		saveQueue.push(pRoot);
		while (!saveQueue.empty())
		{
			pRoot = saveQueue.front(); saveQueue.pop();
			saveVector[currentLevel].push_back(pRoot->m_nValue);
			currentLevelNodes--;
			if (pRoot->m_pLeft != nullptr)
			{
				saveQueue.push(pRoot->m_pLeft);
				nextLevelNodes++;
			}
			if (pRoot->m_pRight != nullptr)
			{
				saveQueue.push(pRoot->m_pRight);
				nextLevelNodes++;
			}
			if (currentLevelNodes == 0)
			{
				currentLevelNodes = nextLevelNodes;
				nextLevelNodes = 0;
				currentLevel++;
				//防止多插入一行
				if (!saveQueue.empty())
				{
					currentLevel++;
					saveVector.push_back(vector<int>());
				}
			}
		}
		return saveVector;
	}

	//尝试用两个队列来存
	vector<vector<int> > Print(BinaryTreeNode* pRoot)
	{
		if (pRoot == nullptr)
			return vector<vector<int> >();

		queue<BinaryTreeNode*> saveQueue;
		queue<BinaryTreeNode*> nextQueue;
		vector<vector<int> > saveVector(1);

		int currentLevel = 0;

		saveQueue.push(pRoot);
		while (!saveQueue.empty())
		{
			pRoot = saveQueue.front(); saveQueue.pop();
			saveVector[currentLevel].push_back(pRoot->m_nValue);
			if (pRoot->m_pLeft != nullptr)
				nextQueue.push(pRoot->m_pLeft);
			if (pRoot->m_pRight != nullptr)
				nextQueue.push(pRoot->m_pRight);
			if (saveQueue.empty())
			{
				while (!nextQueue.empty())
				{
					saveQueue.push(nextQueue.front());
					nextQueue.pop();
				}		
				//防止多插入一行
				if (!saveQueue.empty())
				{
					currentLevel++;
					saveVector.push_back(vector<int>());
				}
			}
		}
		return saveVector;
	}
};

// ====================测试代码====================
static void Test(char* testName, BinaryTreeNode* pRoot)
{
	if (testName != nullptr)
		printf("%s begins: \n", testName);

	PrintTree(pRoot);

	Solution s;
	printf("The nodes from top to bottom, from left to right are: \n");
	vector<vector<int> >  tmp = s.Print(pRoot);
	for (auto &s1 : tmp)
	{
		for (auto &s2 : s1)
			cout << s2 << " ";
		cout << endl;
	}

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

// 树中只有1个结点
static void Test4()
{
	BinaryTreeNode* pNode1 = CreateBinaryTreeNode(1);
	Test("Test4", pNode1);

	DestroyTree(pNode1);
}

// 树中没有结点
static void Test5()
{
	Test("Test5", nullptr);
}

int main_offer32_2(int argc, char* argv[])
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();

	return 0;
}