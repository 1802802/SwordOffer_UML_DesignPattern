// 面试题32.3—之字形打印二叉树
// 题目：请实现一个函数按照之字形打印二叉树，即第一行按照从左到右的顺序打印，第二层按照从右至左的顺序打印，
// 第三行按照从左到右的顺序打印，其他行以此类推。

/*

总结：这种二叉树打印题，对应于最普通的层序遍历，一个队列queue即可，对于接下来的两种，各有两种解法：
（1）按行顺序打印：使用双队列queue（或者队列数组）、当前行数实现
使用单队列queue、当前行数目标记、下一行数目标记实现、当前行数实现；
（2）按行之字型打印：使用双栈stack（或者栈数组）、当前行数实现
使用单队列deque、当前行数目标记、下一行数目标记实现、当前行数实现（奇数时，数据头部存入尾部读出；偶数时，数据头部读出尾部存入）

*/

#include <iostream>
#include <vector>
#include <stack>
#include "BinaryTree.h"
using namespace std;

class Solution2
{
public:
	//思路：之字形打印的特点是其结构已经类似于栈，用传统的队列不好操作，所以使用两个栈来实现伪队列即可
	//并且，使用栈进行来回倒，避免了栈之间的数据传递，运行时间：5ms，占用内存：504k
	vector<vector<int> > Print(BinaryTreeNode* pRoot)
	{
		if (pRoot == nullptr)
			return vector<vector<int> >();

		stack<BinaryTreeNode*> LevelStack[2];   //栈数组，初始化时[0]为当前行，[1]为下一行，之后来回倒
		vector<vector<int> > saveVector(1);

		int currentLevel = 0;
		int index = 0;  //实现来回倒

		LevelStack[index].push(pRoot);
		while (!LevelStack[index].empty() || !LevelStack[1 - index].empty())
		{
			pRoot = LevelStack[index].top(); LevelStack[index].pop();
			saveVector[currentLevel].push_back(pRoot->m_nValue);
			//根据奇偶选择栈的左右节点的前后push策略
			if (currentLevel & 0x1)
			{
				if (pRoot->m_pRight != nullptr)
					LevelStack[1 - index].push(pRoot->m_pRight);
				if (pRoot->m_pLeft != nullptr)
					LevelStack[1 - index].push(pRoot->m_pLeft);
			}
			else
			{
				if (pRoot->m_pLeft != nullptr)
					LevelStack[1 - index].push(pRoot->m_pLeft);
				if (pRoot->m_pRight != nullptr)
					LevelStack[1 - index].push(pRoot->m_pRight);
			}

			if (LevelStack[index].empty())
			{
				index = 1 - index;  //来回倒的具体实现
				if (!LevelStack[index].empty())
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

	Solution2 s;
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

int main_offer32_3(int argc, char* argv[])
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();

	return 0;
}