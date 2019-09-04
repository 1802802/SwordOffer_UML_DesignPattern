// ������55.2��ƽ�������
// ��Ŀ������һ�ö������ĸ���㣬�жϸ����ǲ���ƽ������������ĳ��������
// ��������������������������1����ô������һ��ƽ���������

#include <map>
#include <unordered_map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
#include "BinaryTree.h"
using namespace std;

class Solution55_2 
{
public:
	//��ȱ���ʵ�֣�����ʱ�䣺4ms��ռ���ڴ棺480k
	bool IsBalanced_Solution(BinaryTreeNode* pRoot) 
	{
		TreeDepth(pRoot);
		return flag;
	}

	int TreeDepth(BinaryTreeNode* pRoot)
	{
		//��ʾ���������
		if (pRoot == nullptr)
			return 0;
		int nLeft = TreeDepth(pRoot->m_pLeft);
		int nRight = TreeDepth(pRoot->m_pRight);
		//cout << "nLeft:" << nLeft << endl;
		//cout << "nRight:" << nRight << endl;
		if (abs(nLeft - nRight) > 1)
			flag = false;
		return 1 + max(nLeft, nRight);
	}
private:
	bool flag = true;
};

// ====================���Դ���====================
static void Test(const char* testName, BinaryTreeNode* pRoot, bool expected)
{
	if (testName != nullptr)
		printf("%s begins:\n", testName);

	Solution55_2 s;
	printf("Solution1 begins: ");
	if (s.IsBalanced_Solution(pRoot) == expected)
		printf("Passed.\n");
	else
		printf("Failed.\n");

	//printf("Solution2 begins: ");
	//if (IsBalanced_Solution2(pRoot) == expected)
	//	printf("Passed.\n");
	//else
	//	printf("Failed.\n");
}

// ��ȫ������
//             1
//         /      \
//        2        3
//       /\       / \
//      4  5     6   7
static void Test1()
{
	BinaryTreeNode* pNode1 = CreateBinaryTreeNode(1);
	BinaryTreeNode* pNode2 = CreateBinaryTreeNode(2);
	BinaryTreeNode* pNode3 = CreateBinaryTreeNode(3);
	BinaryTreeNode* pNode4 = CreateBinaryTreeNode(4);
	BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);
	BinaryTreeNode* pNode6 = CreateBinaryTreeNode(6);
	BinaryTreeNode* pNode7 = CreateBinaryTreeNode(7);

	ConnectTreeNodes(pNode1, pNode2, pNode3);
	ConnectTreeNodes(pNode2, pNode4, pNode5);
	ConnectTreeNodes(pNode3, pNode6, pNode7);

	Test("Test1", pNode1, true);

	DestroyTree(pNode1);
}

// ������ȫ������������ƽ�������
//             1
//         /      \
//        2        3
//       /\         \
//      4  5         6
//        /
//       7
static void Test2()
{
	BinaryTreeNode* pNode1 = CreateBinaryTreeNode(1);
	BinaryTreeNode* pNode2 = CreateBinaryTreeNode(2);
	BinaryTreeNode* pNode3 = CreateBinaryTreeNode(3);
	BinaryTreeNode* pNode4 = CreateBinaryTreeNode(4);
	BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);
	BinaryTreeNode* pNode6 = CreateBinaryTreeNode(6);
	BinaryTreeNode* pNode7 = CreateBinaryTreeNode(7);

	ConnectTreeNodes(pNode1, pNode2, pNode3);
	ConnectTreeNodes(pNode2, pNode4, pNode5);
	ConnectTreeNodes(pNode3, nullptr, pNode6);
	ConnectTreeNodes(pNode5, pNode7, nullptr);

	Test("Test2", pNode1, true);

	DestroyTree(pNode1);
}

// ����ƽ�������
//             1
//         /      \
//        2        3
//       /\         
//      4  5        
//        /
//       6
static void Test3()
{
	BinaryTreeNode* pNode1 = CreateBinaryTreeNode(1);
	BinaryTreeNode* pNode2 = CreateBinaryTreeNode(2);
	BinaryTreeNode* pNode3 = CreateBinaryTreeNode(3);
	BinaryTreeNode* pNode4 = CreateBinaryTreeNode(4);
	BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);
	BinaryTreeNode* pNode6 = CreateBinaryTreeNode(6);

	ConnectTreeNodes(pNode1, pNode2, pNode3);
	ConnectTreeNodes(pNode2, pNode4, pNode5);
	ConnectTreeNodes(pNode5, pNode6, nullptr);

	Test("Test3", pNode1, false);

	DestroyTree(pNode1);
}


//               1
//              /
//             2
//            /
//           3
//          /
//         4
//        /
//       5
static void Test4()
{
	BinaryTreeNode* pNode1 = CreateBinaryTreeNode(1);
	BinaryTreeNode* pNode2 = CreateBinaryTreeNode(2);
	BinaryTreeNode* pNode3 = CreateBinaryTreeNode(3);
	BinaryTreeNode* pNode4 = CreateBinaryTreeNode(4);
	BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);

	ConnectTreeNodes(pNode1, pNode2, nullptr);
	ConnectTreeNodes(pNode2, pNode3, nullptr);
	ConnectTreeNodes(pNode3, pNode4, nullptr);
	ConnectTreeNodes(pNode4, pNode5, nullptr);

	Test("Test4", pNode1, false);

	DestroyTree(pNode1);
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
static void Test5()
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

	Test("Test5", pNode1, false);

	DestroyTree(pNode1);
}

// ����ֻ��1�����
static void Test6()
{
	BinaryTreeNode* pNode1 = CreateBinaryTreeNode(1);
	Test("Test6", pNode1, true);

	DestroyTree(pNode1);
}

// ����û�н��
static void Test7()
{
	Test("Test7", nullptr, true);
}

int main_offer55_2(int argc, char* argv[])
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	Test6();
	Test7();

	return 0;
}