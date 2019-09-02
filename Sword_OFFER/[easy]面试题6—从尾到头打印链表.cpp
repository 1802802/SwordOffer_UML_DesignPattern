#include <iostream>
#include <vector>
#include <stack>
using namespace std;

struct ListNode 
{
      int val;
      struct ListNode *next;
	  ListNode(int x) :val(x), next(NULL) {}
};

//1.ʹ��stackջ�ṹ���洢���ݣ�Ȼ��˳���ջ����
//ʱ�临�Ӷ�O(n)���ռ临�Ӷ�O(n)��ţ����ʱ��3ms���ڴ�480K
vector<int> printListFromTailToHead1(ListNode* head) 
{
	ListNode* node = head;
	stack<int> m_stack;
	while (node != NULL)
	{
		m_stack.push(node->val);
		node = node->next;
	}
	vector<int> temp;
	//C++��stack��pop����Ϊvoid�������ͣ�������Ҫ�ֶ���ֵ
	while (!m_stack.empty())
	{
		temp.push_back(m_stack.top());
		m_stack.pop();
	}
	return temp;
}

//2.ʹ�õݹ�Ƕ�ף�������stack������ʱ���棨�ܱ�������������ջ��������⣩
//ʱ�临�Ӷ�O(n)���ռ临�Ӷ�O(n)(�ݹ��ʺ�ֱ����������ֻ���Ҫ���Ч����û��ô����)��ţ����ʱ��4ms���ڴ�480K
vector<int> temp2;
vector<int> printListFromTailToHead(ListNode* head)
{
	if (head != NULL)
	{
		printListFromTailToHead(head->next);
		temp2.push_back(head->val);
	}
	return temp2;
}