// ������34���������к�Ϊĳһֵ��·��
// ��Ŀ������һ�Ŷ������ĸ��ڵ��һ����������ӡ���������н��ֵ�ĺ�Ϊ��������������·����
// ·������Ϊ�����ĸ���㿪ʼ����һֱ��Ҷ����������Ľ���γ�һ��·����
// (ע��: �ڷ���ֵ��list�У����鳤�ȴ�����鿿ǰ)

#include <iostream>
#include <vector>
#include "BinaryTree.h"
using namespace std;

class Solution 
{
public:
	//vector��ջ�ķ�ʽ��·�����ݹ�ʵ��·�����ң�ĳ��������Ҳ������̽���ݷ�������ʱ�䣺4ms��ռ���ڴ棺472k
	//����ýڵ���Ҷ�ڵ����жϵ�ǰvector�������Ƿ�����Ҫ���������ӡ����Ȼ��ɾ���ýڵ㣨������Ҫ���ǵ����Ƿ���Ҫ��֦��
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
		//0.ÿ������һ�κ������򽫸ú��������ݼ���path�У�static void�����ݹ������Ҫ��
		path.push_back(root->m_nValue);
		currentSum += root->m_nValue;

		//0.5��֦�������ٶ��ã�
		if (currentSum > expectNumber)
		{
			path.pop_back();
			return;
		}

		//1.�жϸýڵ��Ƿ�Ϊ����������Ҷ�ڵ㣬�ǵĻ���ѹ�������ٻ��ݣ����ǵĻ���ֱ�ӻ���
		if (root->m_pLeft == nullptr && root->m_pRight == nullptr)
		{
			if(currentSum == expectNumber)
				totalPath.push_back(path);
		}
		//2.����ýڵ㲻��Ҷ�ڵ㣬�����֦�ڵ�Ĳ���
		else
		{
			if (root->m_pLeft != nullptr)
				FindPath(root->m_pLeft, expectNumber, path, totalPath, currentSum);
			if (root->m_pRight != nullptr)
				FindPath(root->m_pRight, expectNumber, path, totalPath, currentSum);
		}
		//3.����ǰ��Ĳ��ҽ����Σ����Ҫpop����
		path.pop_back();
		return;
	}
};

// ====================���Դ���====================
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
// ������·���ϵĽ���Ϊ22
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
// û��·���ϵĽ���Ϊ15
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
// ��һ��·������Ľ���Ϊ15
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
// û��·������Ľ���Ϊ16
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

// ����ֻ��1�����
static void Test5()
{
	BinaryTreeNode* pNode1 = CreateBinaryTreeNode(1);

	printf("One path should be found in Test5.\n");
	Test("Test5", pNode1, 1);

	DestroyTree(pNode1);
}

// ����û�н��
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