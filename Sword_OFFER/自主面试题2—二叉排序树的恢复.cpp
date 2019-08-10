//����ĳ��ԭ��һ�������������������ڵ��Ԫ�ر��������ڲ��ı����Ľṹ������»ָ���ö���������

#include <iostream>
#include <vector>
#include "BinaryTree.h"
using namespace std;

class Solutionzizhu2
	//˼·1�������������Ϊһ�������ֱ�ӱ����ҵ������λ�ü��ɣ����ֿ�������ʵ�֣�
{
public:
	BinaryTreeNode* pre = nullptr;
	BinaryTreeNode* first = nullptr;
	BinaryTreeNode* second = nullptr;
	void Find(BinaryTreeNode* pRoot)
	{
		vector<BinaryTreeNode*> save;
		pre = nullptr; first = nullptr; second = nullptr;
		Midtrav(pRoot, save);
		for (int i = 0; i < save.size(); i++)
		{
			//�����洢֮ǰ�ڵ��pre���������ڵ�save[i]���ϱȽϣ�ע�����ſ����ж�������
			if ((pre != nullptr) && (pre->m_nValue > save[i]->m_nValue))
				(first == nullptr) ? (first = pre, second = save[i]) : (second = save[i]);
			pre = save[i];
		}
		if (first == nullptr || second == nullptr)
			cout << "���������û���ҵ�����Ľڵ�" << endl;
		else
			swap(first->m_nValue, second->m_nValue);
	}
	//ע�����ô�ֵ
	void Midtrav(BinaryTreeNode* pRoot, vector<BinaryTreeNode*>& save)
	{
		if (pRoot == nullptr)
			return;
		Midtrav(pRoot->m_pLeft, save);
		save.push_back(pRoot);
		Midtrav(pRoot->m_pRight, save);
	}

	//˼·2������������Ĺ������ҵ���ͨ��ά���ڵ�ʵ�֣�
	void Find2(BinaryTreeNode* pRoot)
	{
		pre = nullptr; first = nullptr; second = nullptr;
		Midtrav2(pRoot);
		if (first == nullptr || second == nullptr)
			cout << "���������û���ҵ�����Ľڵ�" << endl;
		else
			swap(first->m_nValue, second->m_nValue);
	}

	void Midtrav2(BinaryTreeNode* pRoot)
	{
		if (pRoot == nullptr)
			return;
		Midtrav2(pRoot->m_pLeft);

		if ((pre != nullptr) && (pre->m_nValue > pRoot->m_nValue))
			(first == nullptr) ? (first = pre, second = pRoot) : (second = pRoot);
		pre = pRoot;

		Midtrav2(pRoot->m_pRight);
	}
};

// ====================���Դ���====================
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

	Solutionzizhu2 s;
	s.Find(pRootOfTree);

	PrintTree(pRootOfTree);
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

	swap(pNode4->m_nValue, pNode16->m_nValue);

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

	swap(pNode2->m_nValue, pNode4->m_nValue);

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

int main_zizhu2(int argc, char* argv[])
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();

	return 0;
}