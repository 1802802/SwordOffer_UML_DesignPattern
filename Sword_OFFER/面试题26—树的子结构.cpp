// ������26�������ӽṹ
// ��Ŀ���������ö�����A��B���ж�B�ǲ���A���ӽṹ����ps������Լ��������������һ�������ӽṹ��

#include <iostream>
#include <string>
#include "List.h"
using namespace std;


struct BinaryTreeNode
{
	double                 m_dbValue;
	BinaryTreeNode*        m_pLeft;
	BinaryTreeNode*        m_pRight;
};

class Solution 
{
public:
	//˼·����ͳ��ǰ�������������Root1�ı���������Root1��Root2����ֵ�Ƚϣ�
	//�ڱ����бȽϸ��ڵ��Ƿ���ͬ�������ͬ����иýڵ�ĵݹ����������жϣ�����ʱ�䣺3ms��ռ���ڴ棺480k
	bool HasSubtree(BinaryTreeNode* pRoot1, BinaryTreeNode* pRoot2)
	{
		if (pRoot1 == nullptr || pRoot2 == nullptr)
			return false;
		bool result = false;
		//���ڵ�����ȼ���
		if (abs(pRoot1->m_dbValue - pRoot2->m_dbValue) < 0.00000001)
			result = SearchHasSubtree(pRoot1, pRoot2);
		//�������ļ��㣬��resultΪfalseʱ������Ϊtrueʱ����
		if(!result)
			result = HasSubtree(pRoot1->m_pLeft, pRoot2);
		//�������ļ��㣬��resultΪfalseʱ������Ϊtrueʱ����
		if (!result)
			result = HasSubtree(pRoot1->m_pRight, pRoot2);

		return result;
	}

	//�Ƚ�Root1��Root2��������Root2�Ƿ�ΪRoot1�����������ڲ��ҹ����У���Ҫȷ�����ڵ����������������
	bool SearchHasSubtree(BinaryTreeNode* pRoot1, BinaryTreeNode* pRoot2)
	{
		//1.1�ݹ�����������ҵ���ͷʱ����ǰ��ĸ��ڵ㶼��ȣ����ùܸ�����û���ҵ���ͷ��
		if (pRoot2 == nullptr)
			return true;
		//1.2�ݹ�����������ҵ���ͷ����������û�ҵ���ͷʱΪfalse
		if (pRoot1 == nullptr && pRoot2 != nullptr)
			return false;
		//2.����жϣ������ʱ����false�����ʱ��ʼ���������ݹ������ע����Ҫ���Ҷ����㣬������&&��
		if (abs(pRoot1->m_dbValue - pRoot2->m_dbValue) > 0.00000001)
			return false;
		else
			return SearchHasSubtree(pRoot1->m_pLeft, pRoot2->m_pLeft) && 
			SearchHasSubtree(pRoot1->m_pRight, pRoot2->m_pRight);
	}
};

// ====================�������Դ���====================
BinaryTreeNode* CreateBinaryTreeNode(double dbValue)
{
	BinaryTreeNode* pNode = new BinaryTreeNode();
	pNode->m_dbValue = dbValue;
	pNode->m_pLeft = nullptr;
	pNode->m_pRight = nullptr;

	return pNode;
}

static void ConnectTreeNodes(BinaryTreeNode* pParent, BinaryTreeNode* pLeft, BinaryTreeNode* pRight)
{
	if (pParent != nullptr)
	{
		pParent->m_pLeft = pLeft;
		pParent->m_pRight = pRight;
	}
}

static void DestroyTree(BinaryTreeNode* pRoot)
{
	if (pRoot != nullptr)
	{
		BinaryTreeNode* pLeft = pRoot->m_pLeft;
		BinaryTreeNode* pRight = pRoot->m_pRight;

		delete pRoot;
		pRoot = nullptr;

		DestroyTree(pLeft);
		DestroyTree(pRight);
	}
}

// ====================���Դ���====================
static void Test(char* testName, BinaryTreeNode* pRoot1, BinaryTreeNode* pRoot2, bool expected)
{
	Solution s;
	if (s.HasSubtree(pRoot1, pRoot2) == expected)
		printf("%s passed.\n", testName);
	else
		printf("%s failed.\n", testName);
}

// ���н�㺬�зֲ棬��B����A���ӽṹ
//                  8                8
//              /       \           / \
//             8         7         9   2
//           /   \
//          9     2
//               / \
//              4   7
static void Test1()
{
	BinaryTreeNode* pNodeA1 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNodeA2 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNodeA3 = CreateBinaryTreeNode(7);
	BinaryTreeNode* pNodeA4 = CreateBinaryTreeNode(9);
	BinaryTreeNode* pNodeA5 = CreateBinaryTreeNode(2);
	BinaryTreeNode* pNodeA6 = CreateBinaryTreeNode(4);
	BinaryTreeNode* pNodeA7 = CreateBinaryTreeNode(7);

	ConnectTreeNodes(pNodeA1, pNodeA2, pNodeA3);
	ConnectTreeNodes(pNodeA2, pNodeA4, pNodeA5);
	ConnectTreeNodes(pNodeA5, pNodeA6, pNodeA7);

	BinaryTreeNode* pNodeB1 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNodeB2 = CreateBinaryTreeNode(9);
	BinaryTreeNode* pNodeB3 = CreateBinaryTreeNode(2);

	ConnectTreeNodes(pNodeB1, pNodeB2, pNodeB3);

	Test("Test1", pNodeA1, pNodeB1, true);

	DestroyTree(pNodeA1);
	DestroyTree(pNodeB1);
}

// ���н�㺬�зֲ棬��B������A���ӽṹ
//                  8                8
//              /       \           / \
//             8         7         9   2
//           /   \
//          9     3
//               / \
//              4   7
static void Test2()
{
	BinaryTreeNode* pNodeA1 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNodeA2 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNodeA3 = CreateBinaryTreeNode(7);
	BinaryTreeNode* pNodeA4 = CreateBinaryTreeNode(9);
	BinaryTreeNode* pNodeA5 = CreateBinaryTreeNode(3);
	BinaryTreeNode* pNodeA6 = CreateBinaryTreeNode(4);
	BinaryTreeNode* pNodeA7 = CreateBinaryTreeNode(7);

	ConnectTreeNodes(pNodeA1, pNodeA2, pNodeA3);
	ConnectTreeNodes(pNodeA2, pNodeA4, pNodeA5);
	ConnectTreeNodes(pNodeA5, pNodeA6, pNodeA7);

	BinaryTreeNode* pNodeB1 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNodeB2 = CreateBinaryTreeNode(9);
	BinaryTreeNode* pNodeB3 = CreateBinaryTreeNode(2);

	ConnectTreeNodes(pNodeB1, pNodeB2, pNodeB3);

	Test("Test2", pNodeA1, pNodeB1, false);

	DestroyTree(pNodeA1);
	DestroyTree(pNodeB1);
}

// ���н��ֻ�����ӽ�㣬��B����A���ӽṹ
//                8                  8
//              /                   / 
//             8                   9   
//           /                    /
//          9                    2
//         /      
//        2        
//       /
//      5
static void Test3()
{
	BinaryTreeNode* pNodeA1 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNodeA2 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNodeA3 = CreateBinaryTreeNode(9);
	BinaryTreeNode* pNodeA4 = CreateBinaryTreeNode(2);
	BinaryTreeNode* pNodeA5 = CreateBinaryTreeNode(5);

	ConnectTreeNodes(pNodeA1, pNodeA2, nullptr);
	ConnectTreeNodes(pNodeA2, pNodeA3, nullptr);
	ConnectTreeNodes(pNodeA3, pNodeA4, nullptr);
	ConnectTreeNodes(pNodeA4, pNodeA5, nullptr);

	BinaryTreeNode* pNodeB1 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNodeB2 = CreateBinaryTreeNode(9);
	BinaryTreeNode* pNodeB3 = CreateBinaryTreeNode(2);

	ConnectTreeNodes(pNodeB1, pNodeB2, nullptr);
	ConnectTreeNodes(pNodeB2, pNodeB3, nullptr);

	Test("Test3", pNodeA1, pNodeB1, true);

	DestroyTree(pNodeA1);
	DestroyTree(pNodeB1);
}

// ���н��ֻ�����ӽ�㣬��B������A���ӽṹ
//                8                  8
//              /                   / 
//             8                   9   
//           /                    /
//          9                    3
//         /      
//        2        
//       /
//      5
static void Test4()
{
	BinaryTreeNode* pNodeA1 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNodeA2 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNodeA3 = CreateBinaryTreeNode(9);
	BinaryTreeNode* pNodeA4 = CreateBinaryTreeNode(2);
	BinaryTreeNode* pNodeA5 = CreateBinaryTreeNode(5);

	ConnectTreeNodes(pNodeA1, pNodeA2, nullptr);
	ConnectTreeNodes(pNodeA2, pNodeA3, nullptr);
	ConnectTreeNodes(pNodeA3, pNodeA4, nullptr);
	ConnectTreeNodes(pNodeA4, pNodeA5, nullptr);

	BinaryTreeNode* pNodeB1 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNodeB2 = CreateBinaryTreeNode(9);
	BinaryTreeNode* pNodeB3 = CreateBinaryTreeNode(3);

	ConnectTreeNodes(pNodeB1, pNodeB2, nullptr);
	ConnectTreeNodes(pNodeB2, pNodeB3, nullptr);

	Test("Test4", pNodeA1, pNodeB1, false);

	DestroyTree(pNodeA1);
	DestroyTree(pNodeB1);
}

// ���н��ֻ�����ӽ�㣬��B����A���ӽṹ
//       8                   8
//        \                   \ 
//         8                   9   
//          \                   \
//           9                   2
//            \      
//             2        
//              \
//               5
static void Test5()
{
	BinaryTreeNode* pNodeA1 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNodeA2 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNodeA3 = CreateBinaryTreeNode(9);
	BinaryTreeNode* pNodeA4 = CreateBinaryTreeNode(2);
	BinaryTreeNode* pNodeA5 = CreateBinaryTreeNode(5);

	ConnectTreeNodes(pNodeA1, nullptr, pNodeA2);
	ConnectTreeNodes(pNodeA2, nullptr, pNodeA3);
	ConnectTreeNodes(pNodeA3, nullptr, pNodeA4);
	ConnectTreeNodes(pNodeA4, nullptr, pNodeA5);

	BinaryTreeNode* pNodeB1 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNodeB2 = CreateBinaryTreeNode(9);
	BinaryTreeNode* pNodeB3 = CreateBinaryTreeNode(2);

	ConnectTreeNodes(pNodeB1, nullptr, pNodeB2);
	ConnectTreeNodes(pNodeB2, nullptr, pNodeB3);

	Test("Test5", pNodeA1, pNodeB1, true);

	DestroyTree(pNodeA1);
	DestroyTree(pNodeB1);
}

// ��A�н��ֻ�����ӽ�㣬��B������A���ӽṹ
//       8                   8
//        \                   \ 
//         8                   9   
//          \                 / \
//           9               3   2
//            \      
//             2        
//              \
//               5
static void Test6()
{
	BinaryTreeNode* pNodeA1 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNodeA2 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNodeA3 = CreateBinaryTreeNode(9);
	BinaryTreeNode* pNodeA4 = CreateBinaryTreeNode(2);
	BinaryTreeNode* pNodeA5 = CreateBinaryTreeNode(5);

	ConnectTreeNodes(pNodeA1, nullptr, pNodeA2);
	ConnectTreeNodes(pNodeA2, nullptr, pNodeA3);
	ConnectTreeNodes(pNodeA3, nullptr, pNodeA4);
	ConnectTreeNodes(pNodeA4, nullptr, pNodeA5);

	BinaryTreeNode* pNodeB1 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNodeB2 = CreateBinaryTreeNode(9);
	BinaryTreeNode* pNodeB3 = CreateBinaryTreeNode(3);
	BinaryTreeNode* pNodeB4 = CreateBinaryTreeNode(2);

	ConnectTreeNodes(pNodeB1, nullptr, pNodeB2);
	ConnectTreeNodes(pNodeB2, pNodeB3, pNodeB4);

	Test("Test6", pNodeA1, pNodeB1, false);

	DestroyTree(pNodeA1);
	DestroyTree(pNodeB1);
}

// ��AΪ����
static void Test7()
{
	BinaryTreeNode* pNodeB1 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNodeB2 = CreateBinaryTreeNode(9);
	BinaryTreeNode* pNodeB3 = CreateBinaryTreeNode(3);
	BinaryTreeNode* pNodeB4 = CreateBinaryTreeNode(2);

	ConnectTreeNodes(pNodeB1, nullptr, pNodeB2);
	ConnectTreeNodes(pNodeB2, pNodeB3, pNodeB4);

	Test("Test7", nullptr, pNodeB1, false);

	DestroyTree(pNodeB1);
}

// ��BΪ����
static void Test8()
{
	BinaryTreeNode* pNodeA1 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNodeA2 = CreateBinaryTreeNode(9);
	BinaryTreeNode* pNodeA3 = CreateBinaryTreeNode(3);
	BinaryTreeNode* pNodeA4 = CreateBinaryTreeNode(2);

	ConnectTreeNodes(pNodeA1, nullptr, pNodeA2);
	ConnectTreeNodes(pNodeA2, pNodeA3, pNodeA4);

	Test("Test8", pNodeA1, nullptr, false);

	DestroyTree(pNodeA1);
}

// ��A����B��Ϊ��
static void Test9()
{
	Test("Test9", nullptr, nullptr, false);
}

int main_offer26(int argc, char* argv[])
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

	return 0;
}
