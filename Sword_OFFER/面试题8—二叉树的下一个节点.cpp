#include <iostream>
using namespace std;

//这是牛客网的结构例子，next就是父节点
struct TreeLinkNode
{
	int val;
	struct TreeLinkNode *left;
	struct TreeLinkNode *right;
	struct TreeLinkNode *next;
	TreeLinkNode(int x) :val(x), left(NULL), right(NULL), next(NULL) {}
};

//牛客网3ms，内存380K
class Solution
{
public:
	TreeLinkNode* GetNext(TreeLinkNode* pNode)
	{
		if (pNode == NULL)
			return NULL;
		//1.先判断有无右子树，有则找到右子树的最左节点（注意最左节点定义，如果没有就使用右子树初始点）
		if (pNode->right != NULL)
		{
			pNode = pNode->right;
			while (pNode->left != NULL)
				pNode = pNode->left;
			return pNode;
		}
		//2.再判断自身是父节点的左节点还是右节点还是没有父节点
		else if (pNode->next != NULL)
		{
			//2.1如果自身是父节点左节点，则下任为父节点（后来发现2.1和2.2可以直接合并）
			if (pNode->next->left == pNode)
				return pNode->next;
			//2.2如果自身是父节点右节点，则下任为父节点往上的那个为其父节点的左节点的节点的父节点（这个逻辑仔细读，由于是二叉树，这个点有且只有一个）
			//具体的实现不断地判断自身是否为父节点的左节点，不是就替换直至找到或到父节点为NULL
			while (pNode->next != NULL && pNode != pNode->next->left)
				pNode = pNode->next;
			return pNode->next;
		}
		//3.最后这个没啥用，其实前面的不同情况都自己返回了
		return NULL;
	}
};

int main_offer8()
{
	TreeLinkNode * node1 = new TreeLinkNode(1);
	TreeLinkNode * node2 = new TreeLinkNode(2);
	TreeLinkNode * node3 = new TreeLinkNode(3);
	TreeLinkNode * node4 = new TreeLinkNode(4);
	node1->left = node2;
	node1->right = node3;
	node2->left = node4;
	node2->next = node1;
	node3->next = node1;
	node4->next = node2;

	Solution s;
	cout << s.GetNext(node4)->val << endl;

	return 0;
}