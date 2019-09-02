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

//1.使用stack栈结构来存储数据，然后顺序出栈即可
//时间复杂度O(n)，空间复杂度O(n)，牛客网时间3ms，内存480K
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
	//C++的stack的pop函数为void返回类型，所以需要手动赋值
	while (!m_stack.empty())
	{
		temp.push_back(m_stack.top());
		m_stack.pop();
	}
	return temp;
}

//2.使用递归嵌套，不采用stack来做临时缓存（能避免数据量过大栈溢出的问题）
//时间复杂度O(n)，空间复杂度O(n)(递归适合直接输出，这种还需要存的效果就没那么好了)，牛客网时间4ms，内存480K
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