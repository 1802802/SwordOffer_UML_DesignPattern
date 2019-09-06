// ������37�����л�������
// ��Ŀ����ʵ�������������ֱ��������л��ͷ����л�������

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include "BinaryTree.h"
using namespace std;

/* ����˼·��
��1�����л�����ǰ������У����ַ������ϵز���������#�����������һ��stringתchar*��ͬʱ������Ҫpop���һλ���','
��2�������л�����ǰǰ������У����ϵظ����ַ����������ؽ��������ҷָ��ַ�����������Ҫע���λchar��תint����
*/
// ����ʱ�䣺4ms��ռ���ڴ棺476k

class Solution 
{
public:

	//1.����1��ͨ���������ṹ�������У������Լ�ʵ�֣����ж���׿ӣ�
	char* Serialize(BinaryTreeNode *root) 
	{
		//�׿�1����string��Ϊ����ȫ�ֱ�������newʱ��ʱ��������ջ�ڴ���ڣ��ڽ�����ֵ���⴫��ʱ����������������ݣ�
		string m_prevStr;
		prevTraversal(root, m_prevStr);
		//�׿�2��ע�����Ĵ���ʽ�������һ��','��Ҫɾ��
		if (m_prevStr[m_prevStr.size() - 1] == ',')
			m_prevStr.pop_back();
		//�׿�3��Ҫ��tmp���ڴ�Ū����������ջ��Ļ�return֮�����ݼ�û�ˣ���ô�ⲿ�õ��ľ���û��ֵ��char*�ռ�
		char *tmp = new char[m_prevStr.size()];
		//�׿�4��strcpy_s��ʹ�ã�����ֵchar*������ֵ�ĳ��ȣ�����Ϊ��ֵ��char*����+1����ԭ��ֵchar*��
		strcpy_s(tmp, m_prevStr.size() + 1, m_prevStr.c_str());
		//�׿�5�������Ǵ���char*��Ҳ����ָ�룬��ָ��ʱ����ע�����ĵ�ַ�ǶѵĻ���ջ�ڴ��
		return tmp;
	}
	// ǰ�����ʵ�����л�����
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
			//�׿�6������intתchar���ҵ��������Ƚ�int��to_stringתstring���ٱ���string��Ϊchar���뵽��Ӧstring����
			string tmp = to_string(root->m_nValue);
			for (auto &s : tmp)
				m_prevStr.push_back(s);
			m_prevStr.push_back(',');
		}
		prevTraversal(root->m_pLeft, m_prevStr);
		prevTraversal(root->m_pRight, m_prevStr);
	}

	//2.����2��ͨ�����н��������Ӧ�Ķ�����
	int m_index = 0;
	BinaryTreeNode* Deserialize(char *str)
	{
		m_index = 0;
		return prevTraversal4Deserialize(str, strlen(str));
	}

	BinaryTreeNode* prevTraversal4Deserialize(char *str, int length)
	{
		// ','������Ϊǰ������
		if (str[m_index] == ',')
			m_index++;
		if (str[m_index] != '#' && m_index < length)
		{
			BinaryTreeNode* pRoot = new BinaryTreeNode;

			//�׿�7������char���ͳ����ݵ�תint�ʹ���
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

	//���л��ĺ������ڣ�ʹ��ǰ�����������Ȼ�󽫽�����string��Ϊchar*���ͣ�ע��pop_back)
	char* Serialize(TreeNode *root)
	{
		string save = "";
		travPre(root, save);
		save.pop_back();
		char* tmp = new char[save.size()];
		strcpy(tmp, save.c_str());
		return tmp;
	}

	//�����л��ĺ������ڣ�����char�еݽ��Ĵ������ڵ���ǰ��������ؽ���ʽ���������ң����ô���start��
	//����������ǰ����������ҵ����ԣ�������Ϊ��
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