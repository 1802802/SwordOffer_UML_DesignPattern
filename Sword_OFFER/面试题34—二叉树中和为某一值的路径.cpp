// 面试题34—二叉树中和为某一值的路径
// 题目：输入一颗二叉树的根节点和一个整数，打印出二叉树中结点值的和为输入整数的所有路径。
// 路径定义为从树的根结点开始往下一直到叶结点所经过的结点形成一条路径。
// (注意: 在返回值的list中，数组长度大的数组靠前)

#include <iostream>
#include <vector>
#include "BinaryTree.h"
using namespace std;

class Solution 
{
public:
	//vector以栈的方式存路径，递归实现路径查找（某种意义上也就是试探回溯法）运行时间：4ms，占用内存：472k
	//如果该节点是叶节点则判断当前vector内数据是否满足要求，满足则打印，不然则删除该节点（其中需要考虑的是是否需要剪枝）
	vector<vector<int> > FindPath(BinaryTreeNode* root, int expectNumber) 
	{
		if (root == nullptr || expectNumber < 0)
			return vector<vector<int> >();

		vector<vector<int> > totalPath;
		vector<int> path;

		FindPath(root, expectNumber, path, totalPath, 0);

		return totalPath;
	}

	void FindPath(BinaryTreeNode* root, int expectNumber, vector<int>& path, vector<vector<int> >& totalPath, int currentSum)
	{
		//0.每当调用一次函数，则将该函数的数据加入path中（static void函数递归基不必要）
		path.push_back(root->m_nValue);
		currentSum += root->m_nValue;

		//0.5剪枝（提升速度用）
		if (currentSum > expectNumber)
		{
			path.pop_back();
			return;
		}

		//1.判断该节点是否为满足条件的叶节点，是的话就压入数据再回溯，不是的话就直接回溯
		if (root->m_pLeft == nullptr && root->m_pRight == nullptr)
		{
			if(currentSum == expectNumber)
				totalPath.push_back(path);
		}
		//2.如果该节点不是叶节点，则进行枝节点的操作
		else
		{
			if (root->m_pLeft != nullptr)
				FindPath(root->m_pLeft, expectNumber, path, totalPath, currentSum);
			if (root->m_pRight != nullptr)
				FindPath(root->m_pRight, expectNumber, path, totalPath, currentSum);
		}
		//3.无论前面的查找结果如何，最后都要pop回溯
		path.pop_back();
		return;
	}
};

// ====================测试代码====================
static void Test(char* testName, BinaryTreeNode* pRoot, int expectedSum)
{
	if (testName != nullptr)
		printf("%s begins:\n", testName);
	Solution s;
	auto tmp = s.FindPath(pRoot, expectedSum);
	for (auto &s : tmp)
	{
		for (auto &s2 : s)
		{
			cout << s2 << " ";
		}
		cout << endl;
	}

	printf("\n");
}

//            10
//         /      \
//        5        12
//       /\        
//      4  7     
// 有两条路径上的结点和为22
static void Test1()
{
	BinaryTreeNode* pNode10 = CreateBinaryTreeNode(10);
	BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);
	BinaryTreeNode* pNode12 = CreateBinaryTreeNode(12);
	BinaryTreeNode* pNode4 = CreateBinaryTreeNode(4);
	BinaryTreeNode* pNode7 = CreateBinaryTreeNode(7);

	ConnectTreeNodes(pNode10, pNode5, pNode12);
	ConnectTreeNodes(pNode5, pNode4, pNode7);

	printf("Two paths should be found in Test1.\n");
	Test("Test1", pNode10, 22);

	DestroyTree(pNode10);
}

//            10
//         /      \
//        5        12
//       /\        
//      4  7     
// 没有路径上的结点和为15
static void Test2()
{
	BinaryTreeNode* pNode10 = CreateBinaryTreeNode(10);
	BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);
	BinaryTreeNode* pNode12 = CreateBinaryTreeNode(12);
	BinaryTreeNode* pNode4 = CreateBinaryTreeNode(4);
	BinaryTreeNode* pNode7 = CreateBinaryTreeNode(7);

	ConnectTreeNodes(pNode10, pNode5, pNode12);
	ConnectTreeNodes(pNode5, pNode4, pNode7);

	printf("No paths should be found in Test2.\n");
	Test("Test2", pNode10, 15);

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
// 有一条路径上面的结点和为15
static void Test3()
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

	printf("One path should be found in Test3.\n");
	Test("Test3", pNode5, 15);

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
// 没有路径上面的结点和为16
static void Test4()
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

	printf("No paths should be found in Test4.\n");
	Test("Test4", pNode1, 16);

	DestroyTree(pNode1);
}

// 树中只有1个结点
static void Test5()
{
	BinaryTreeNode* pNode1 = CreateBinaryTreeNode(1);

	printf("One path should be found in Test5.\n");
	Test("Test5", pNode1, 1);

	DestroyTree(pNode1);
}

// 树中没有结点
static void Test6()
{
	printf("No paths should be found in Test6.\n");
	Test("Test6", nullptr, 0);
}

int main_offer34(int argc, char* argv[])
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	Test6();

	return 0;
}