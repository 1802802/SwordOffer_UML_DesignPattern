// 面试题24—反转链表
// 题目：输入一个链表，反转链表后，输出新链表的表头。

#include <iostream>
#include <string>
#include "List.h"
using namespace std;

class Solution 
{
public:
	//为了保证链表在反转时不断裂，需要记录三个节点：当前节点，当前节点的前一节点与后一节点
	ListNode* ReverseList(ListNode* pHead) 
	{
		if (pHead == nullptr)
			return nullptr;

		ListNode* pPrevNode = nullptr;
		ListNode* pNode = pHead;
		ListNode* pPostNode = nullptr;

		while (pNode != nullptr)
		{
			pNode->m_pNext = pPostNode;
			pNode->m_pNext = pPrevNode;
		}
	}
};

int main_offer24()
{
	string a;
	string b;
	string c;
	while (cin >> a >> b >> c)
		cout << a << " " << b << " " << c << endl;

	return 0;
}