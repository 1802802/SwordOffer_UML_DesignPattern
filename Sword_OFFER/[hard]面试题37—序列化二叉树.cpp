// 面试题37—序列化二叉树
// 题目：请实现两个函数，分别用来序列化和反序列化二叉树

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include "BinaryTree.h"
using namespace std;

/* 基本思路：
（1）序列化：在前序遍历中，对字符串不断地插入数据与#，到最后再做一下string转char*的同时，还需要pop最后一位多的','
（2）反序列化：在前前序遍历中，不断地根据字符串的数据重建（根左右分割字符串），其中要注意多位char的转int处理
*/
// 运行时间：4ms，占用内存：476k

class Solution 
{
public:

	//1.函数1，通过二叉树结构建立序列（本人自己实现，其中多个雷坑）
	char* Serialize(BinaryTreeNode *root) 
	{
		//雷坑1：当string作为类内全局变量（不new时）时，其是以栈内存存在，在进行数值向外传递时，可能造成垃圾传递；
		string m_prevStr;
		prevTraversal(root, m_prevStr);
		//雷坑2：注意后面的处理方式，最后会多一个','，要删掉
		if (m_prevStr[m_prevStr.size() - 1] == ',')
			m_prevStr.pop_back();
		//雷坑3：要将tmp的内存弄到堆里，如果在栈里的话return之后数据即没了，那么外部拿到的就是没有值的char*空间
		char *tmp = new char[m_prevStr.size()];
		//雷坑4：strcpy_s的使用（被赋值char*，被赋值的长度（往往为赋值的char*长度+1），原赋值char*）
		strcpy_s(tmp, m_prevStr.size() + 1, m_prevStr.c_str());
		//雷坑5：函数是传的char*，也就是指针，传指针时万万注意其存的地址是堆的还是栈内存的
		return tmp;
	}
	// 前序遍历实现序列化操作
	void prevTraversal(BinaryTreeNode *root, string& m_prevStr)
	{
		if (root == nullptr)
		{
			m_prevStr.push_back('#');
			m_prevStr.push_back(',');
			return;
		}
		else
		{
			//雷坑6：对于int转char，我的做法是先将int用to_string转string，再遍历string成为char插入到对应string后面
			string tmp = to_string(root->m_nValue);
			for (auto &s : tmp)
				m_prevStr.push_back(s);
			m_prevStr.push_back(',');
		}
		prevTraversal(root->m_pLeft, m_prevStr);
		prevTraversal(root->m_pRight, m_prevStr);
	}

	//2.函数2，通过序列建立出其对应的二叉树
	int m_index = 0;
	BinaryTreeNode* Deserialize(char *str)
	{
		m_index = 0;
		return prevTraversal4Deserialize(str, strlen(str));
	}

	BinaryTreeNode* prevTraversal4Deserialize(char *str, int length)
	{
		// ','符号作为前进符号
		if (str[m_index] == ',')
			m_index++;
		if (str[m_index] != '#' && m_index < length)
		{
			BinaryTreeNode* pRoot = new BinaryTreeNode;

			//雷坑7：对于char类型长数据的转int型处理
			string tmp; int val = 0;
			while (str[m_index] != ',')
				tmp.push_back(str[m_index++]);	
			for (int i = tmp.size() - 1; i >= 0; i--)
				val += pow(10, tmp.size() - 1 - i)*(tmp[i] - '0');
			pRoot->m_nValue = val;

			pRoot->m_pLeft = prevTraversal4Deserialize(str, length);
			pRoot->m_pRight = prevTraversal4Deserialize(str, length);
			return pRoot;
		}
		else
		{
			m_index++;
			return nullptr;
		}	
	}
};


struct TreeNode 
{
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution
{
public:
	void travPre(TreeNode *root, string &save)
	{
		if (root == nullptr)
		{
			save.append("#!");
			return;
		}
		save.append(to_string(root->val) + "!");
		travPre(root->left, save);
		travPre(root->right, save);
	}

	//序列化的核心在于：使用前序遍历建立，然后将建立的string变为char*类型（注意pop_back)
	char* Serialize(TreeNode *root)
	{
		string save = "";
		travPre(root, save);
		save.pop_back();
		char* tmp = new char[save.size()];
		strcpy(tmp, save.c_str());
		return tmp;
	}

	//反序列化的核心在于：对于char中递进的处理，对于单个前序遍历的重建方式（先左再右，引用传递start）
	//这里利用了前序遍历根左右的特性，先左后必为右
	TreeNode* Deserialize(char *str, int &start, int &end)
	{
		if (str[start] == '!')
			start++;
		if (start < end && str[start] != '#')
		{
			int val = 0; int minus = 1;
			if (str[start] == '-')
			{
				minus = -1;
				start++;
			}
			if (str[start] == '+')
			{
				minus = 1;
				start++;
			}
			while (str[start] != '!')
			{
				val = 10 * val + minus*(str[start] - '0');
				start++;
			}
			TreeNode* pNode = new TreeNode(val);
			pNode->left = Deserialize(str, start, end);
			pNode->right = Deserialize(str, start, end);
			return pNode;
		}
		else
		{
			start++;
			return nullptr;
		}
	}

	TreeNode* Deserialize(char *str)
	{
		if (str == nullptr)
			return nullptr;
		int start = 0; int end = strlen(str);
		return Deserialize(str, start, end);
	}
};

// ==================== Test Code ====================
bool isSameTree(const BinaryTreeNode* pRoot1, const BinaryTreeNode* pRoot2)
{
	if (pRoot1 == nullptr && pRoot2 == nullptr)
		return true;

	if (pRoot1 == nullptr || pRoot2 == nullptr)
		return false;

	if (pRoot1->m_nValue != pRoot2->m_nValue)
		return false;

	return isSameTree(pRoot1->m_pLeft, pRoot2->m_pLeft) &&
		isSameTree(pRoot1->m_pRight, pRoot2->m_pRight);
}

static void Test(const char* testName, BinaryTreeNode* pRoot)
{
	Solution s;
	cout << testName << ":" << endl;
	char* tmp = s.Serialize(pRoot);
	cout << tmp << endl;
	if (isSameTree(s.Deserialize(tmp), pRoot))
		cout << testName << " is Same Tree" << endl;
	else
		cout << testName << " not the Same Tree" << endl;
}

//            8
//        6      10
//       5 7    9  11
static void Test1()
{
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

	Test("Test1", pNode8);

	DestroyTree(pNode8);
}

//            5
//          4
//        3
//      2
static void Test2()
{
	BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);
	BinaryTreeNode* pNode4 = CreateBinaryTreeNode(4);
	BinaryTreeNode* pNode3 = CreateBinaryTreeNode(3);
	BinaryTreeNode* pNode2 = CreateBinaryTreeNode(2);

	ConnectTreeNodes(pNode5, pNode4, nullptr);
	ConnectTreeNodes(pNode4, pNode3, nullptr);
	ConnectTreeNodes(pNode3, pNode2, nullptr);

	Test("Test2", pNode5);

	DestroyTree(pNode5);
}

//        5
//         4
//          3
//           2
static void Test3()
{
	BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);
	BinaryTreeNode* pNode4 = CreateBinaryTreeNode(4);
	BinaryTreeNode* pNode3 = CreateBinaryTreeNode(3);
	BinaryTreeNode* pNode2 = CreateBinaryTreeNode(2);

	ConnectTreeNodes(pNode5, nullptr, pNode4);
	ConnectTreeNodes(pNode4, nullptr, pNode3);
	ConnectTreeNodes(pNode3, nullptr, pNode2);

	Test("Test3", pNode5);

	DestroyTree(pNode5);
}

static void Test4()
{
	BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);

	Test("Test4", pNode5);

	DestroyTree(pNode5);
}

static void Test5()
{
	Test("Test5", nullptr);
}

//        5
//         5
//          5
//         5
//        5
//       5 5
//      5   5
static void Test6()
{
	BinaryTreeNode* pNode1 = CreateBinaryTreeNode(5);
	BinaryTreeNode* pNode2 = CreateBinaryTreeNode(5);
	BinaryTreeNode* pNode3 = CreateBinaryTreeNode(5);
	BinaryTreeNode* pNode4 = CreateBinaryTreeNode(5);
	BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);
	BinaryTreeNode* pNode61 = CreateBinaryTreeNode(5);
	BinaryTreeNode* pNode62 = CreateBinaryTreeNode(5);
	BinaryTreeNode* pNode71 = CreateBinaryTreeNode(5);
	BinaryTreeNode* pNode72 = CreateBinaryTreeNode(5);

	ConnectTreeNodes(pNode1, nullptr, pNode2);
	ConnectTreeNodes(pNode2, nullptr, pNode3);
	ConnectTreeNodes(pNode3, pNode4, nullptr);
	ConnectTreeNodes(pNode4, pNode5, nullptr);
	ConnectTreeNodes(pNode5, pNode61, pNode62);
	ConnectTreeNodes(pNode61, pNode71, nullptr);
	ConnectTreeNodes(pNode62, nullptr, pNode72);

	Test("Test6", pNode1);

	DestroyTree(pNode1);
}

int main_offer37(int argc, char* argv[])
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	Test6();

	return 0;
}