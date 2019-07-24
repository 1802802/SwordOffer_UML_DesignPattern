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

//前序遍历/后序遍历 推导出 根节点，中序遍历推导出左子树和右子树的数据分布

//思路：将前序遍历数组和中序遍历数组分割为左子树、根节点与右子树组成的数组，通过不断地递归分割实现二叉树重构
class Solution 
{
public:
	TreeNode * reConstructBinaryTree(const vector<int> &pre,const vector<int> &vin)
	{
		return reConstructBinaryTree(pre, 0, pre.size() - 1, vin, 0, vin.size() - 1);
	}
	//这是第一个版本的前中遍历二叉树重构，虽然思想正确，但是代码较为冗余
	//牛客网运行6ms，内存612K
	TreeNode * reConstructBinaryTree1(const vector<int> &pre, int preStart, int preEnd, const vector<int> &vin, int midStart, int midEnd)
	{
		//0.递归基，当当前的数值已经失效时，返回NULL
		if (preStart > preEnd || midStart > midEnd)
			return NULL;
		//1.根据所传入的前序遍历序列，得到当前树的根节点
		TreeNode * root = new TreeNode(pre[preStart]);
		//1.1判断当前的前序遍历是否只有一个数，有则直接返回根节点
		if (preStart == preEnd)
			return root;
		//2.在中序遍历序列中找到左子树的尾和右子树的头（通过根节点分割左右树）
		//2.1这里注意各个区段的长度选择，与前面两个长度的选取息息相关
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
		//3.通过左子树的尾和右子树的头，对当前节点进行递归重构
		root->left = reConstructBinaryTree(pre, preStart + 1, preStart + leftTreeSize, vin, midStart, midLeftTreeEnd);
		root->right = reConstructBinaryTree(pre, preStart + leftTreeSize + 1, preEnd, vin, midRightTreeStart, midEnd);

		return root;
	}

	//第二个版本的二叉树重构，优化代码结构，去除冗余部分
	//牛客网运行4ms，内存608K
	TreeNode * reConstructBinaryTree(const vector<int> &pre, int preStart, int preEnd, const vector<int> &vin, int midStart, int midEnd)
	{
		if (preStart > preEnd || midStart > midEnd)  //递归基，当数据不合法时返回NULL
			return NULL;
		TreeNode * root = new TreeNode(pre[preStart]);
		for (int i = midStart; i <= midEnd; i++)
		{
			if (vin[i] == root->val)
			{
				//将方法1的所有临时数据取消，直接代入递归式子
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