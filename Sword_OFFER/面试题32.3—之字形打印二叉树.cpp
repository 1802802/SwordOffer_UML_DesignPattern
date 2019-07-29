// ������32.3��֮���δ�ӡ������
// ��Ŀ����ʵ��һ����������֮���δ�ӡ������������һ�а��մ����ҵ�˳���ӡ���ڶ��㰴�մ��������˳���ӡ��
// �����а��մ����ҵ�˳���ӡ���������Դ����ơ�

/*

�ܽ᣺���ֶ�������ӡ�⣬��Ӧ������ͨ�Ĳ��������һ������queue���ɣ����ڽ����������֣��������ֽⷨ��
��1������˳���ӡ��ʹ��˫����queue�����߶������飩����ǰ����ʵ��
ʹ�õ�����queue����ǰ����Ŀ��ǡ���һ����Ŀ���ʵ�֡���ǰ����ʵ�֣�
��2������֮���ʹ�ӡ��ʹ��˫ջstack������ջ���飩����ǰ����ʵ��
ʹ�õ�����deque����ǰ����Ŀ��ǡ���һ����Ŀ���ʵ�֡���ǰ����ʵ�֣�����ʱ������ͷ������β��������ż��ʱ������ͷ������β�����룩

*/

#include <iostream>
#include <vector>
#include <stack>
#include "BinaryTree.h"
using namespace std;

class Solution2
{
public:
	//˼·��֮���δ�ӡ���ص�����ṹ�Ѿ�������ջ���ô�ͳ�Ķ��в��ò���������ʹ������ջ��ʵ��α���м���
	//���ң�ʹ��ջ�������ص���������ջ֮������ݴ��ݣ�����ʱ�䣺5ms��ռ���ڴ棺504k
	vector<vector<int> > Print(BinaryTreeNode* pRoot)
	{
		if (pRoot == nullptr)
			return vector<vector<int> >();

		stack<BinaryTreeNode*> LevelStack[2];   //ջ���飬��ʼ��ʱ[0]Ϊ��ǰ�У�[1]Ϊ��һ�У�֮�����ص�
		vector<vector<int> > saveVector(1);

		int currentLevel = 0;
		int index = 0;  //ʵ�����ص�

		LevelStack[index].push(pRoot);
		while (!LevelStack[index].empty() || !LevelStack[1 - index].empty())
		{
			pRoot = LevelStack[index].top(); LevelStack[index].pop();
			saveVector[currentLevel].push_back(pRoot->m_nValue);
			//������żѡ��ջ�����ҽڵ��ǰ��push����
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
				index = 1 - index;  //���ص��ľ���ʵ��
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

// ====================���Դ���====================
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

int main_offer32_3(int argc, char* argv[])
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();

	return 0;
}