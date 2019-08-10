// ������68����������������͹�������
// ��Ŀ��������������㣬�����ǵ���͹������ȡ�

#include <iostream>
#include <list>
#include "BinaryTree.h"
#include "Tree.h"
using namespace std;

//�����ж�Ӧ���ֲ�ͬ�����������ֲ�ͬ�Ľ������
//�ֱ��ǣ����������������и��ڵ����ͨ��������������������ͬ���������и��ڵ����������������������ͬ��

//1.��������������͹�ͬ���ȵĲ��ң����ݶ������������ԣ��Ӹ��ڵ㿪ʼ�ж����Ƿ�������С�Ҵ�ԭ��
BinaryTreeNode* GetLastCommon_BST(BinaryTreeNode* pRoot, const BinaryTreeNode* pNode1, const BinaryTreeNode* pNode2)
{
	//1.�߽��������ж�����Ĳ����Ƿ�Ϊnullptr
	if (pNode1 == pNode2 && pNode1 == nullptr && pNode2 == nullptr)
		return const_cast<BinaryTreeNode*>(pNode1);
	//2.�߽��������жϵ�ǰ����������ڵ�node1��node2�Ƿ�Ϊ���ӽڵ㣬��������ǲ��㹫�����Ȼ����㸸�ڵ���Ǹ�����Ҫ�����
	if (pNode1->m_pLeft == pNode2 || pNode1->m_pRight == pNode2 || pNode2->m_pLeft == pNode1 || pNode2->m_pRight == pNode1)
		return nullptr;
	//3.ѭ������ֱ���ﵽ����
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

//2.���и��ڵ����ͨ����Ѱ�Ҹ��Ը��ڵ�ֱ�����ڵ㣬�γ�nodeΪ�ף�rootΪβ����������
//��¼�䳤�ȣ�Ȼ�����������һ�����ڵ���ң�
TreeNode* GetLastCommon_PT(TreeNode* pNode1, TreeNode* pNode2)
{
	//1.�߽��������ж�����Ĳ����Ƿ�Ϊnullptr
	if (pNode1 == pNode2 && pNode1 == nullptr && pNode2 == nullptr)
		return pNode1;
	int size1 = 0;
	int size2 = 0;
	TreeNode* pRoot = pNode1;
	//2.��ǰ��ѯ������������
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
	//3.�����������abs(size1-size2)λ
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
	//ע�����ص��׿ӣ���һ���������ڵ㲻�ǵ�һ�������ڵ㣬������Ҫ�������ж������ڿ�ʼʱ���Ƿ����
	if (pNode1 != nullptr && pNode1 == pNode2)
	{
		if (pNode1->m_parent != nullptr)
			return pNode1->m_parent;
		else
			return nullptr;
	}

	//4.ʵ��������ĵ�һ�������ڵ����
	while (pNode1 != nullptr && pNode2 != nullptr)
	{
		if (pNode1 == pNode2)
			return pNode1;
		pNode1 = pNode1->m_parent;
		pNode2 = pNode2->m_parent;
	}
	return nullptr;
}

//�����Ǹ���̽���ݷ�
bool GetPath(TreeNode* pRoot, TreeNode* pNode, list<TreeNode*>& pList)
{
	bool flag = false;
	if (pRoot == pNode)
		flag = true;
	//1.��̽�����Ȳ��룬��flagΪtrue������
	pList.push_front(pRoot);	
	for (auto &s : pRoot->m_vChildren)
	{
		if (flag == true)
			break;
		flag = GetPath(s, pNode, pList);
	}
	//2.�ٸ��ݱ�־λ�����߲��ñ�־λ������
	if (!flag)
		pList.pop_front();
	return flag;
}

//3.û�и��ڵ����ͨ������root��ʼ�ҵ�ͨ��node1��node2������ͷ�壩��
//��rootΪβ��nodeΪͷ�����ҵ�һ����ͬ�ڵ㣩
//����ͬһ�����ϵĽڵ㣬��Ӧ���������乲ͬ�ĵ����常�ڵ㣬����54321��4321����5��4��Ϊ3
TreeNode* GetLastCommon_T(TreeNode* pRoot, TreeNode* pNode1, TreeNode* pNode2)
{
	//1.�߽��������ж�����Ĳ����Ƿ�Ϊnullptr
	if (pNode1 == pNode2 || pNode1 == nullptr || pNode2 == nullptr)
		return pNode1;

	list<TreeNode*> list1, list2;
	GetPath(pRoot, pNode1, list1);
	GetPath(pRoot, pNode2, list2);
	int size1 = list1.size(), size2 = list2.size();
	auto index1 = list1.begin(), index2 = list2.begin();

	//2.ʵ�ֵ�һ����ͬ�ڵ�Ĳ��ң��������ڵ㲻������������Ҫ��ͬ������һ�㣩
	int temp = abs(size1 - size2);
	if (size1 > size2)
		while (temp--)
			index1++;
	else if (size1 < size2)
		while (temp--)
			index2++;

	//����ʼ����ȣ���ʾ��ʱ���ڵ㱾���λ��ͬһ�������ϣ���ʱֱ�ӷ������ߵĺ�һλ����
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

// ====================���Դ���====================
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

// ��״��ͨ����
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

// ���˻���һ������
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

// ���˻���һ������һ����㲻������
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

// ����nullptr
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
