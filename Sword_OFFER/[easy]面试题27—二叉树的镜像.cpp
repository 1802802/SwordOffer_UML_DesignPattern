// 面试题27—二叉树的镜像
// 题目：题目描述操作给定的二叉树，将其变换为源二叉树的镜像。

#include <iostream>
#include <string>
#include "BinaryTree.h"
using namespace std;

//思路：在前序遍历的过程中，如果当前节点有子节点，则交换其左右子节点（也说明了叶节点不交换）
//运行时间：3ms，占用内存：592k
static void MirrorRecursively(BinaryTreeNode *pRoot)
{
	if (pRoot == nullptr)
		return;
	if (pRoot->m_pLeft != nullptr || pRoot->m_pRight != nullptr)
		swap(pRoot->m_pLeft, pRoot->m_pRight);
	MirrorRecursively(pRoot->m_pLeft);
	MirrorRecursively(pRoot->m_pRight);
}

//运行时间：3ms，占用内存：600k，思路更清晰，可见这题很简单
void Mirror(BinaryTreeNode *pRoot)
{
	if (pRoot == nullptr)
		return;
	if (pRoot->m_pLeft != pRoot->m_pRight)
		swap(pRoot->m_pLeft, pRoot->m_pRight);
	Mirror(pRoot->m_pLeft);
	Mirror(pRoot->m_pLeft);
}

// ====================测试代码====================
// 测试完全二叉树：除了叶子节点，其他节点都有两个子节点
//            8
//        6      10
//       5 7    9  11
static void Test1()
{
	printf("=====Test1 starts:=====\n");
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

	PrintTree(pNode8);

	printf("=====Test1: MirrorRecursively=====\n");
	MirrorRecursively(pNode8);
	PrintTree(pNode8);

	DestroyTree(pNode8);
}

// 测试二叉树：出叶子结点之外，左右的结点都有且只有一个左子结点
//            8
//          7   
//        6 
//      5
//    4
static void Test2()
{
	printf("=====Test2 starts:=====\n");
	BinaryTreeNode* pNode8 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNode7 = CreateBinaryTreeNode(7);
	BinaryTreeNode* pNode6 = CreateBinaryTreeNode(6);
	BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);
	BinaryTreeNode* pNode4 = CreateBinaryTreeNode(4);

	ConnectTreeNodes(pNode8, pNode7, nullptr);
	ConnectTreeNodes(pNode7, pNode6, nullptr);
	ConnectTreeNodes(pNode6, pNode5, nullptr);
	ConnectTreeNodes(pNode5, pNode4, nullptr);

	PrintTree(pNode8);

	printf("=====Test2: MirrorRecursively=====\n");
	MirrorRecursively(pNode8);
	PrintTree(pNode8);

	DestroyTree(pNode8);
}

// 测试二叉树：出叶子结点之外，左右的结点都有且只有一个右子结点
//            8
//             7   
//              6 
//               5
//                4
static void Test3()
{
	printf("=====Test3 starts:=====\n");
	BinaryTreeNode* pNode8 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNode7 = CreateBinaryTreeNode(7);
	BinaryTreeNode* pNode6 = CreateBinaryTreeNode(6);
	BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);
	BinaryTreeNode* pNode4 = CreateBinaryTreeNode(4);

	ConnectTreeNodes(pNode8, nullptr, pNode7);
	ConnectTreeNodes(pNode7, nullptr, pNode6);
	ConnectTreeNodes(pNode6, nullptr, pNode5);
	ConnectTreeNodes(pNode5, nullptr, pNode4);

	PrintTree(pNode8);

	printf("=====Test3: MirrorRecursively=====\n");
	MirrorRecursively(pNode8);
	PrintTree(pNode8);

	DestroyTree(pNode8);
}

// 测试空二叉树：根结点为空指针
static void Test4()
{
	printf("=====Test4 starts:=====\n");
	BinaryTreeNode* pNode = nullptr;

	PrintTree(pNode);

	printf("=====Test4: MirrorRecursively=====\n");
	MirrorRecursively(pNode);
	PrintTree(pNode);
}

// 测试只有一个结点的二叉树
static void Test5()
{
	printf("=====Test5 starts:=====\n");
	BinaryTreeNode* pNode8 = CreateBinaryTreeNode(8);

	PrintTree(pNode8);

	printf("=====Test4: MirrorRecursively=====\n");
	MirrorRecursively(pNode8);
	PrintTree(pNode8);

}

int main_offer27(int argc, char* argv[])
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();

	return 0;
}