#include <iostream>
using namespace std;

//����ţ�����Ľṹ���ӣ�next���Ǹ��ڵ�
struct TreeLinkNode
{
	int val;
	struct TreeLinkNode *left;
	struct TreeLinkNode *right;
	struct TreeLinkNode *next;
	TreeLinkNode(int x) :val(x), left(NULL), right(NULL), next(NULL) {}
};

//ţ����3ms���ڴ�380K
class Solution
{
public:
	TreeLinkNode* GetNext(TreeLinkNode* pNode)
	{
		if (pNode == NULL)
			return NULL;
		//1.���ж������������������ҵ�������������ڵ㣨ע������ڵ㶨�壬���û�о�ʹ����������ʼ�㣩
		if (pNode->right != NULL)
		{
			pNode = pNode->right;
			while (pNode->left != NULL)
				pNode = pNode->left;
			return pNode;
		}
		//2.���ж������Ǹ��ڵ����ڵ㻹���ҽڵ㻹��û�и��ڵ�
		else if (pNode->next != NULL)
		{
			//2.1��������Ǹ��ڵ���ڵ㣬������Ϊ���ڵ㣨��������2.1��2.2����ֱ�Ӻϲ���
			if (pNode->next->left == pNode)
				return pNode->next;
			//2.2��������Ǹ��ڵ��ҽڵ㣬������Ϊ���ڵ����ϵ��Ǹ�Ϊ�丸�ڵ����ڵ�Ľڵ�ĸ��ڵ㣨����߼���ϸ���������Ƕ����������������ֻ��һ����
			//�����ʵ�ֲ��ϵ��ж������Ƿ�Ϊ���ڵ����ڵ㣬���Ǿ��滻ֱ���ҵ��򵽸��ڵ�ΪNULL
			while (pNode->next != NULL && pNode != pNode->next->left)
				pNode = pNode->next;
			return pNode->next;
		}
		//3.������ûɶ�ã���ʵǰ��Ĳ�ͬ������Լ�������
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