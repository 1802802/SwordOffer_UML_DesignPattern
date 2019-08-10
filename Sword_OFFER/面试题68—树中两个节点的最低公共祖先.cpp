// 面试题68：树中两个结点的最低公共祖先
// 题目：输入两个树结点，求它们的最低公共祖先。

#include <iostream>
#include <list>
#include "BinaryTree.h"
#include "Tree.h"
using namespace std;

//此题有对应三种不同的树，有三种不同的解决方案
//分别是：二叉搜索树，带有父节点的普通树（解决方案与二叉树相同），不带有父节点的树（解决方案与二叉树相同）

//1.二叉搜索树的最低共同祖先的查找，根据二叉搜索树特性，从根节点开始判断其是否满足左小右大原则
BinaryTreeNode* GetLastCommon_BST(BinaryTreeNode* pRoot, const BinaryTreeNode* pNode1, const BinaryTreeNode* pNode2)
{
	//1.边界条件，判断输入的参数是否为nullptr
	if (pNode1 == pNode2 && pNode1 == nullptr && pNode2 == nullptr)
		return const_cast<BinaryTreeNode*>(pNode1);
	//2.边界条件，判断当前输入的两个节点node1与node2是否互为父子节点，这种情况是不算公共祖先还是算父节点的那个？需要问清楚
	if (pNode1->m_pLeft == pNode2 || pNode1->m_pRight == pNode2 || pNode2->m_pLeft == pNode1 || pNode2->m_pRight == pNode1)
		return nullptr;
	//3.循环查找直到达到条件
	while (pRoot != nullptr)
	{
		if (pRoot->m_nValue < pNode1->m_nValue && pRoot->m_nValue < pNode2->m_nValue)
			pRoot = pRoot->m_pRight;
		else if (pRoot->m_nValue > pNode1->m_nValue && pRoot->m_nValue > pNode2->m_nValue)
			pRoot = pRoot->m_pLeft;
		else
			return pRoot;
	}
}

int main_offer68_1()
{
	BinaryTreeNode* pNode8 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNode6 = CreateBinaryTreeNode(6);
	BinaryTreeNode* pNode10 = CreateBinaryTreeNode(10);
	BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);
	BinaryTreeNode* pNode7 = CreateBinaryTreeNode(7);
	BinaryTreeNode* pNode9 = CreateBinaryTreeNode(9);
	BinaryTreeNode* pNode11 = CreateBinaryTreeNode(11);
	BinaryTreeNode* pNode3 = CreateBinaryTreeNode(3);

	ConnectTreeNodes(pNode8, pNode6, pNode10);
	ConnectTreeNodes(pNode6, pNode5, pNode7);
	ConnectTreeNodes(pNode10, pNode9, pNode11);
	ConnectTreeNodes(pNode5, pNode3, nullptr);

	auto temp = GetLastCommon_BST(pNode8, pNode3, pNode5);
	if (temp == nullptr)
		cout << "don't find" << endl;
	else
		cout << temp->m_nValue << endl;
	DestroyTree(pNode8);

	printf("\n\n");

	return 0;
}

//2.带有父节点的普通树（寻找各自父节点直到根节点，形成node为首，root为尾的两条链表，
//记录其长度，然后按照两链表第一公共节点查找）
TreeNode* GetLastCommon_PT(TreeNode* pNode1, TreeNode* pNode2)
{
	//1.边界条件，判断输入的参数是否为nullptr
	if (pNode1 == pNode2 && pNode1 == nullptr && pNode2 == nullptr)
		return pNode1;
	int size1 = 0;
	int size2 = 0;
	TreeNode* pRoot = pNode1;
	//2.向前查询，建立链表长度
	while (pRoot != nullptr)
	{
		pRoot = pRoot->m_parent;
		size1++;
	}
	pRoot = pNode2;
	while (pRoot != nullptr)
	{
		pRoot = pRoot->m_parent;
		size2++;
	}
	//3.长的链表后移abs(size1-size2)位
	if (size1 > size2)
	{
		int temp = size1 - size2;
		while (temp--)
			pNode1 = pNode1->m_parent;
	}
	else if (size1 < size2)
	{
		int temp = size2 - size1;
		while (temp--)
			pNode2 = pNode2->m_parent;
	}
	//注意隐藏的雷坑，第一个公共父节点不是第一个公共节点，所以需要在这里判断两者在开始时就是否相等
	if (pNode1 != nullptr && pNode1 == pNode2)
	{
		if (pNode1->m_parent != nullptr)
			return pNode1->m_parent;
		else
			return nullptr;
	}

	//4.实现两链表的第一个公共节点查找
	while (pNode1 != nullptr && pNode2 != nullptr)
	{
		if (pNode1 == pNode2)
			return pNode1;
		pNode1 = pNode1->m_parent;
		pNode2 = pNode2->m_parent;
	}
	return nullptr;
}

//这里是个试探回溯法
bool GetPath(TreeNode* pRoot, TreeNode* pNode, list<TreeNode*>& pList)
{
	bool flag = false;
	if (pRoot == pNode)
		flag = true;
	//1.试探回溯先插入，当flag为true后跳出
	pList.push_front(pRoot);	
	for (auto &s : pRoot->m_vChildren)
	{
		if (flag == true)
			break;
		flag = GetPath(s, pNode, pList);
	}
	//2.再根据标志位（或者不用标志位）回溯
	if (!flag)
		pList.pop_front();
	return flag;
}

//3.没有父节点的普通树（从root开始找到通往node1与node2的链表（头插），
//以root为尾，node为头，查找第一个共同节点）
//对于同一链表上的节点，其应该往上找其共同的的意义父节点，比如54321和4321，找5和4的为3
TreeNode* GetLastCommon_T(TreeNode* pRoot, TreeNode* pNode1, TreeNode* pNode2)
{
	//1.边界条件，判断输入的参数是否为nullptr
	if (pNode1 == pNode2 || pNode1 == nullptr || pNode2 == nullptr)
		return pNode1;

	list<TreeNode*> list1, list2;
	GetPath(pRoot, pNode1, list1);
	GetPath(pRoot, pNode2, list2);
	int size1 = list1.size(), size2 = list2.size();
	auto index1 = list1.begin(), index2 = list2.begin();

	//2.实现第一个共同节点的查找（公共父节点不包括自身，所以要找同条的上一层）
	int temp = abs(size1 - size2);
	if (size1 > size2)
		while (temp--)
			index1++;
	else if (size1 < size2)
		while (temp--)
			index2++;

	//如果最开始就相等，表示此时两节点本身就位于同一条链表上，此时直接返回两者的后一位即可
	if (index1 != list1.end() && *index1 == *index2)
	{
		if (index1 != list1.end() && (++index1) != list1.end())
			return *index1;
		else
			return nullptr;
	}

	while (index1 != list1.end() && index2 != list2.end())
	{
		if (*index1 == *index2)
			return *index1;
		index1++; index2++;
	}
	return nullptr;
}

// ====================测试代码====================
static void Test(const char* testName, TreeNode* pRoot, TreeNode* pNode1, TreeNode* pNode2, TreeNode* pExpected)
{
	if (testName != nullptr)
		printf("%s begins: ", testName);

	const TreeNode* pResult = GetLastCommon_T(pRoot, pNode1, pNode2);

	if ((pExpected == nullptr && pResult == nullptr) ||
		(pExpected != nullptr && pResult != nullptr && pResult->m_nValue == pExpected->m_nValue))
		printf("Passed.\n");
	else
		printf("Failed.\n");
}

// 形状普通的树
//              1
//            /   \
//           2     3
//       /       \
//      4         5
//     / \      / |  \
//    6   7    8  9  10
static void Test1()
{
	TreeNode* pNode1 = CreateTreeNode(1);
	TreeNode* pNode2 = CreateTreeNode(2);
	TreeNode* pNode3 = CreateTreeNode(3);
	TreeNode* pNode4 = CreateTreeNode(4);
	TreeNode* pNode5 = CreateTreeNode(5);
	TreeNode* pNode6 = CreateTreeNode(6);
	TreeNode* pNode7 = CreateTreeNode(7);
	TreeNode* pNode8 = CreateTreeNode(8);
	TreeNode* pNode9 = CreateTreeNode(9);
	TreeNode* pNode10 = CreateTreeNode(10);

	ConnectTreeNodes(pNode1, pNode2);
	ConnectTreeNodes(pNode1, pNode3);

	ConnectTreeNodes(pNode2, pNode4);
	ConnectTreeNodes(pNode2, pNode5);

	ConnectTreeNodes(pNode4, pNode6);
	ConnectTreeNodes(pNode4, pNode7);

	ConnectTreeNodes(pNode5, pNode8);
	ConnectTreeNodes(pNode5, pNode9);
	ConnectTreeNodes(pNode5, pNode10);

	Test("Test1", pNode1, pNode6, pNode8, pNode2);
}

// 树退化成一个链表
//               1
//              /
//             2
//            /
//           3
//          /
//         4
//        /
//       5
static void Test2()
{
	TreeNode* pNode1 = CreateTreeNode(1);
	TreeNode* pNode2 = CreateTreeNode(2);
	TreeNode* pNode3 = CreateTreeNode(3);
	TreeNode* pNode4 = CreateTreeNode(4);
	TreeNode* pNode5 = CreateTreeNode(5);

	ConnectTreeNodes(pNode1, pNode2);
	ConnectTreeNodes(pNode2, pNode3);
	ConnectTreeNodes(pNode3, pNode4);
	ConnectTreeNodes(pNode4, pNode5);

	Test("Test2", pNode1, pNode5, pNode4, pNode3);
}

// 树退化成一个链表，一个结点不在树中
//               1
//              /
//             2
//            /
//           3
//          /
//         4
//        /
//       5
static void Test3()
{
	TreeNode* pNode1 = CreateTreeNode(1);
	TreeNode* pNode2 = CreateTreeNode(2);
	TreeNode* pNode3 = CreateTreeNode(3);
	TreeNode* pNode4 = CreateTreeNode(4);
	TreeNode* pNode5 = CreateTreeNode(5);

	ConnectTreeNodes(pNode1, pNode2);
	ConnectTreeNodes(pNode2, pNode3);
	ConnectTreeNodes(pNode3, pNode4);
	ConnectTreeNodes(pNode4, pNode5);

	TreeNode* pNode6 = CreateTreeNode(6);

	Test("Test3", pNode1, pNode5, pNode6, nullptr);
}

// 输入nullptr
static void Test4()
{
	Test("Test4", nullptr, nullptr, nullptr, nullptr);
}

int main_offer68_2(int argc, char* argv[])
{
	Test1();
	Test2();
	Test3();
	Test4();

	return 0;
}
