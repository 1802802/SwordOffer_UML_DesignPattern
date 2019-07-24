#include <iostream>
#include <vector>
using namespace std;

struct TreeNode 
{
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

//ǰ�����/������� �Ƶ��� ���ڵ㣬��������Ƶ����������������������ݷֲ�

//˼·����ǰ���������������������ָ�Ϊ�����������ڵ�����������ɵ����飬ͨ�����ϵصݹ�ָ�ʵ�ֶ������ع�
class Solution 
{
public:
	TreeNode * reConstructBinaryTree(const vector<int> &pre,const vector<int> &vin)
	{
		return reConstructBinaryTree(pre, 0, pre.size() - 1, vin, 0, vin.size() - 1);
	}
	//���ǵ�һ���汾��ǰ�б����������ع�����Ȼ˼����ȷ�����Ǵ����Ϊ����
	//ţ��������6ms���ڴ�612K
	TreeNode * reConstructBinaryTree1(const vector<int> &pre, int preStart, int preEnd, const vector<int> &vin, int midStart, int midEnd)
	{
		//0.�ݹ��������ǰ����ֵ�Ѿ�ʧЧʱ������NULL
		if (preStart > preEnd || midStart > midEnd)
			return NULL;
		//1.�����������ǰ��������У��õ���ǰ���ĸ��ڵ�
		TreeNode * root = new TreeNode(pre[preStart]);
		//1.1�жϵ�ǰ��ǰ������Ƿ�ֻ��һ����������ֱ�ӷ��ظ��ڵ�
		if (preStart == preEnd)
			return root;
		//2.����������������ҵ���������β����������ͷ��ͨ�����ڵ�ָ���������
		//2.1����ע��������εĳ���ѡ����ǰ���������ȵ�ѡȡϢϢ���
		int midLeftTreeEnd = 0;
		int midRightTreeStart = 0;
		int leftTreeSize = 0;
		int rightTreeSize = 0;
		for (int i = midStart; i <= midEnd; i++)
		{
			if (vin[i] == root->val)
			{
				midLeftTreeEnd = i - 1;
				midRightTreeStart = i + 1;
				leftTreeSize = i - midStart;
				rightTreeSize = midEnd - i;
				break;
			}
		}
		//3.ͨ����������β����������ͷ���Ե�ǰ�ڵ���еݹ��ع�
		root->left = reConstructBinaryTree(pre, preStart + 1, preStart + leftTreeSize, vin, midStart, midLeftTreeEnd);
		root->right = reConstructBinaryTree(pre, preStart + leftTreeSize + 1, preEnd, vin, midRightTreeStart, midEnd);

		return root;
	}

	//�ڶ����汾�Ķ������ع����Ż�����ṹ��ȥ�����ಿ��
	//ţ��������4ms���ڴ�608K
	TreeNode * reConstructBinaryTree(const vector<int> &pre, int preStart, int preEnd, const vector<int> &vin, int midStart, int midEnd)
	{
		if (preStart > preEnd || midStart > midEnd)  //�ݹ���������ݲ��Ϸ�ʱ����NULL
			return NULL;
		TreeNode * root = new TreeNode(pre[preStart]);
		for (int i = midStart; i <= midEnd; i++)
		{
			if (vin[i] == root->val)
			{
				//������1��������ʱ����ȡ����ֱ�Ӵ���ݹ�ʽ��
				root->left = reConstructBinaryTree(pre, preStart + 1, preStart + i - midStart, vin, midStart, i - 1);
				root->right = reConstructBinaryTree(pre, preStart + i - midStart + 1, preEnd, vin, i + 1, midEnd);
				break;
			}
		}
		return root;
	}

	TreeNode* travPos_Recursion(TreeNode* node)
	{
		if (node == NULL)
			return NULL;
		cout << node->val << " ";
		travPos_Recursion(node->left);
		travPos_Recursion(node->right);
		
	}
};

int main_offer7()
{
	vector<int> pre = { 1,2,4,7,3,5,6,8 };
	vector<int> vin = { 4,7,2,1,5,3,8,6 };
	Solution s;
	s.travPos_Recursion(s.reConstructBinaryTree(pre, vin));
	cout << endl;

	return 0;
}