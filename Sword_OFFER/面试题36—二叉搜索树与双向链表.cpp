// ������36��������������˫������
// ��Ŀ������һ����������
// ��ÿ���ڵ����нڵ�ֵ���Լ�����ָ�룬һ��ָ����һ���ڵ㣬��һ������ָ��ָ������һ���ڵ㣬
// ���ؽ��Ϊ���ƺ��������head����ע�⣬���������벻Ҫ���ز����еĽڵ����ã�������������ֱ�ӷ��ؿգ�

#include <iostream>
#include <vector>
#include <map>
#include "BinaryTree.h"
using namespace std;

class Solution 
{
public:
	//���Ų����������˼��ʵ��
	BinaryTreeNode* pre = nullptr;
	BinaryTreeNode* head = nullptr;
	BinaryTreeNode* Convert(BinaryTreeNode* pRootOfTree)
	{
		if (pRootOfTree == nullptr)
			return nullptr;
		ConvertNode(pRootOfTree);
		return head;
	}
	void ConvertNode(BinaryTreeNode* pRootOfTree)
	{
		if (pRootOfTree == nullptr)
			return;
		ConvertNode(pRootOfTree->m_pLeft);
	}
};