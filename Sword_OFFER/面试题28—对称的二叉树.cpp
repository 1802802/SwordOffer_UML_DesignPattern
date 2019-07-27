// 面试题28—对称的二叉树
// 题目：请实现一个函数，用来判断一颗二叉树是不是对称的。
// 注意，如果一个二叉树同此二叉树的镜像是同样的，定义其为对称的。

#include <iostream>
#include <vector>
#include "BinaryTree.h"
using namespace std;

//思路：对称的二叉树，其采用"根右左"读取方式得到的结果即为其镜像二叉树采用"根左右"读取方式得到的结果
//1.下面为使用了辅助空间vector的版本，主要用来理清思路，但是其实可以不使用辅助空间而直接操作
static void travPre(BinaryTreeNode* pRoot, vector<int>& travPreSave)
{
	if (pRoot == nullptr)
	{
		travPreSave.push_back(0);
		return;
	}
	travPreSave.push_back(pRoot->m_nValue);
	travPre(pRoot->m_pLeft, travPreSave);
	travPre(pRoot->m_pRight, travPreSave);
}

static void StravPre(BinaryTreeNode* pRoot, vector<int>& StravPreSave)
{
	if (pRoot == nullptr)
	{
		StravPreSave.push_back(0);
		return;
	}
	StravPreSave.push_back(pRoot->m_nValue);
	StravPre(pRoot->m_pRight, StravPreSave);
	StravPre(pRoot->m_pLeft, StravPreSave);
}

bool isSymmetrical2(BinaryTreeNode* pRoot)
{
	//这里需要问清楚，没有节点的树到底算对称的还是不对称的
	if (pRoot == nullptr)
		return true;

	vector<int> travPreSave;
	travPre(pRoot, travPreSave);

	vector<int> StravPreSave;
	StravPre(pRoot, StravPreSave);

	for (int i = 0; i < travPreSave.size(); i++)
		if (travPreSave[i] != StravPreSave[i])
			return false;
	return true;
}

//2.不使用辅助空间，直接在递归循环中完成参数对比（根左右与根右左）
//运行时间：3ms，占用内存：480k
bool isSymmetrical(BinaryTreeNode* pRoot1, BinaryTreeNode* pRoot2)
{
	//2.1递归基（这里的三个递归基写的很有技巧）
	//表示root1和root2现在都为空指针（即都到了叶节点的下一节点，返回true）
	if (pRoot1 == nullptr && pRoot2 == nullptr)
		return true;
	//表示root1和root2只有一个到了叶节点，明显不符合对称性质1（位置相同），返回false
	if (pRoot1 == nullptr || pRoot2 == nullptr)
		return false;
	//表示root1和root2有值不同，明显不符合对称性质2（值相同），返回false
	if (pRoot1->m_nValue != pRoot2->m_nValue)
		return false;
	//2.2递归函数（左右判断与右左判断）
	return isSymmetrical(pRoot1->m_pLeft, pRoot2->m_pRight) 
		&& isSymmetrical(pRoot1->m_pRight, pRoot2->m_pLeft);
}

bool isSymmetrical(BinaryTreeNode* pRoot)
{
	if (pRoot == nullptr)
		return true;
	return isSymmetrical(pRoot, pRoot);
}

// ====================测试代码====================
static void Test(char* testName, BinaryTreeNode* pRoot, bool expected)
{
	if (testName != nullptr)
		printf("%s begins: ", testName);

	if (isSymmetrical(pRoot) == expected)
		printf("Passed.\n");
	else
		printf("FAILED.\n");
}

//            8
//        6      6
//       5 7    7 5
static void Test1()
{
	BinaryTreeNode* pNode8 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNode61 = CreateBinaryTreeNode(6);
	BinaryTreeNode* pNode62 = CreateBinaryTreeNode(6);
	BinaryTreeNode* pNode51 = CreateBinaryTreeNode(5);
	BinaryTreeNode* pNode71 = CreateBinaryTreeNode(7);
	BinaryTreeNode* pNode72 = CreateBinaryTreeNode(7);
	BinaryTreeNode* pNode52 = CreateBinaryTreeNode(5);

	ConnectTreeNodes(pNode8, pNode61, pNode62);
	ConnectTreeNodes(pNode61, pNode51, pNode71);
	ConnectTreeNodes(pNode62, pNode72, pNode52);

	Test("Test1", pNode8, true);

	DestroyTree(pNode8);
}

//            8
//        6      9
//       5 7    7 5
static void Test2()
{
	BinaryTreeNode* pNode8 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNode61 = CreateBinaryTreeNode(6);
	BinaryTreeNode* pNode9 = CreateBinaryTreeNode(9);
	BinaryTreeNode* pNode51 = CreateBinaryTreeNode(5);
	BinaryTreeNode* pNode71 = CreateBinaryTreeNode(7);
	BinaryTreeNode* pNode72 = CreateBinaryTreeNode(7);
	BinaryTreeNode* pNode52 = CreateBinaryTreeNode(5);

	ConnectTreeNodes(pNode8, pNode61, pNode9);
	ConnectTreeNodes(pNode61, pNode51, pNode71);
	ConnectTreeNodes(pNode9, pNode72, pNode52);

	Test("Test2", pNode8, false);

	DestroyTree(pNode8);
}

//            8
//        6      6
//       5 7    7
static void Test3()
{
	BinaryTreeNode* pNode8 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNode61 = CreateBinaryTreeNode(6);
	BinaryTreeNode* pNode62 = CreateBinaryTreeNode(6);
	BinaryTreeNode* pNode51 = CreateBinaryTreeNode(5);
	BinaryTreeNode* pNode71 = CreateBinaryTreeNode(7);
	BinaryTreeNode* pNode72 = CreateBinaryTreeNode(7);

	ConnectTreeNodes(pNode8, pNode61, pNode62);
	ConnectTreeNodes(pNode61, pNode51, pNode71);
	ConnectTreeNodes(pNode62, pNode72, nullptr);

	Test("Test3", pNode8, false);

	DestroyTree(pNode8);
}

//               5
//              / \
//             3   3
//            /     \
//           4       4
//          /         \
//         2           2
//        /             \
//       1               1
static void Test4()
{
	BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);
	BinaryTreeNode* pNode31 = CreateBinaryTreeNode(3);
	BinaryTreeNode* pNode32 = CreateBinaryTreeNode(3);
	BinaryTreeNode* pNode41 = CreateBinaryTreeNode(4);
	BinaryTreeNode* pNode42 = CreateBinaryTreeNode(4);
	BinaryTreeNode* pNode21 = CreateBinaryTreeNode(2);
	BinaryTreeNode* pNode22 = CreateBinaryTreeNode(2);
	BinaryTreeNode* pNode11 = CreateBinaryTreeNode(1);
	BinaryTreeNode* pNode12 = CreateBinaryTreeNode(1);

	ConnectTreeNodes(pNode5, pNode31, pNode32);
	ConnectTreeNodes(pNode31, pNode41, nullptr);
	ConnectTreeNodes(pNode32, nullptr, pNode42);
	ConnectTreeNodes(pNode41, pNode21, nullptr);
	ConnectTreeNodes(pNode42, nullptr, pNode22);
	ConnectTreeNodes(pNode21, pNode11, nullptr);
	ConnectTreeNodes(pNode22, nullptr, pNode12);

	Test("Test4", pNode5, true);

	DestroyTree(pNode5);
}


//               5
//              / \
//             3   3
//            /     \
//           4       4
//          /         \
//         6           2
//        /             \
//       1               1
static void Test5()
{
	BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);
	BinaryTreeNode* pNode31 = CreateBinaryTreeNode(3);
	BinaryTreeNode* pNode32 = CreateBinaryTreeNode(3);
	BinaryTreeNode* pNode41 = CreateBinaryTreeNode(4);
	BinaryTreeNode* pNode42 = CreateBinaryTreeNode(4);
	BinaryTreeNode* pNode6 = CreateBinaryTreeNode(6);
	BinaryTreeNode* pNode22 = CreateBinaryTreeNode(2);
	BinaryTreeNode* pNode11 = CreateBinaryTreeNode(1);
	BinaryTreeNode* pNode12 = CreateBinaryTreeNode(1);

	ConnectTreeNodes(pNode5, pNode31, pNode32);
	ConnectTreeNodes(pNode31, pNode41, nullptr);
	ConnectTreeNodes(pNode32, nullptr, pNode42);
	ConnectTreeNodes(pNode41, pNode6, nullptr);
	ConnectTreeNodes(pNode42, nullptr, pNode22);
	ConnectTreeNodes(pNode6, pNode11, nullptr);
	ConnectTreeNodes(pNode22, nullptr, pNode12);

	Test("Test5", pNode5, false);

	DestroyTree(pNode5);
}

//               5
//              / \
//             3   3
//            /     \
//           4       4
//          /         \
//         2           2
//                      \
//                       1
static void Test6()
{
	BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);
	BinaryTreeNode* pNode31 = CreateBinaryTreeNode(3);
	BinaryTreeNode* pNode32 = CreateBinaryTreeNode(3);
	BinaryTreeNode* pNode41 = CreateBinaryTreeNode(4);
	BinaryTreeNode* pNode42 = CreateBinaryTreeNode(4);
	BinaryTreeNode* pNode21 = CreateBinaryTreeNode(2);
	BinaryTreeNode* pNode22 = CreateBinaryTreeNode(2);
	BinaryTreeNode* pNode12 = CreateBinaryTreeNode(1);

	ConnectTreeNodes(pNode5, pNode31, pNode32);
	ConnectTreeNodes(pNode31, pNode41, nullptr);
	ConnectTreeNodes(pNode32, nullptr, pNode42);
	ConnectTreeNodes(pNode41, pNode21, nullptr);
	ConnectTreeNodes(pNode42, nullptr, pNode22);
	ConnectTreeNodes(pNode21, nullptr, nullptr);
	ConnectTreeNodes(pNode22, nullptr, pNode12);

	Test("Test6", pNode5, false);

	DestroyTree(pNode5);
}

// 只有一个结点
static void Test7()
{
	BinaryTreeNode* pNode1 = CreateBinaryTreeNode(1);
	Test("Test7", pNode1, true);

	DestroyTree(pNode1);
}

// 没有结点
static void Test8()
{
	Test("Test8", nullptr, true);
}

// 所有结点都有相同的值，树对称
//               5
//              / \
//             5   5
//            /     \
//           5       5
//          /         \
//         5           5
static void Test9()
{
	BinaryTreeNode* pNode1 = CreateBinaryTreeNode(5);
	BinaryTreeNode* pNode21 = CreateBinaryTreeNode(5);
	BinaryTreeNode* pNode22 = CreateBinaryTreeNode(5);
	BinaryTreeNode* pNode31 = CreateBinaryTreeNode(5);
	BinaryTreeNode* pNode32 = CreateBinaryTreeNode(5);
	BinaryTreeNode* pNode41 = CreateBinaryTreeNode(5);
	BinaryTreeNode* pNode42 = CreateBinaryTreeNode(5);

	ConnectTreeNodes(pNode1, pNode21, pNode22);
	ConnectTreeNodes(pNode21, pNode31, nullptr);
	ConnectTreeNodes(pNode22, nullptr, pNode32);
	ConnectTreeNodes(pNode31, pNode41, nullptr);
	ConnectTreeNodes(pNode32, nullptr, pNode42);
	ConnectTreeNodes(pNode41, nullptr, nullptr);
	ConnectTreeNodes(pNode42, nullptr, nullptr);

	Test("Test9", pNode1, true);

	DestroyTree(pNode1);
}

// 所有结点都有相同的值，树不对称
//               5
//              / \
//             5   5
//            /     \
//           5       5
//          /       /
//         5       5
static void Test10()
{
	BinaryTreeNode* pNode1 = CreateBinaryTreeNode(5);
	BinaryTreeNode* pNode21 = CreateBinaryTreeNode(5);
	BinaryTreeNode* pNode22 = CreateBinaryTreeNode(5);
	BinaryTreeNode* pNode31 = CreateBinaryTreeNode(5);
	BinaryTreeNode* pNode32 = CreateBinaryTreeNode(5);
	BinaryTreeNode* pNode41 = CreateBinaryTreeNode(5);
	BinaryTreeNode* pNode42 = CreateBinaryTreeNode(5);

	ConnectTreeNodes(pNode1, pNode21, pNode22);
	ConnectTreeNodes(pNode21, pNode31, nullptr);
	ConnectTreeNodes(pNode22, nullptr, pNode32);
	ConnectTreeNodes(pNode31, pNode41, nullptr);
	ConnectTreeNodes(pNode32, pNode42, nullptr);
	ConnectTreeNodes(pNode41, nullptr, nullptr);
	ConnectTreeNodes(pNode42, nullptr, nullptr);

	Test("Test10", pNode1, false);

	DestroyTree(pNode1);
}

void main_offer28(int argc, char* argv[])
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	Test6();
	Test7();
	Test8();
	Test9();
	Test10();
}