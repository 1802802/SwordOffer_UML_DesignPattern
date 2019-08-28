/**
* Definition for singly-linked list.
* struct ListNode {
*     int val;
*     ListNode *next;
*     ListNode(int x) : val(x), next(NULL) {}
* };
*/
#include <iostream>
#include <list>
#include <algorithm>
#include <string>
#include <vector>    
using namespace std;

struct ListNode
{
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
	ListNode* removeNthFromEnd(ListNode* head, int n)
	{
		//1.找到倒数第k个节点
		ListNode* first = head;
		ListNode* second = head;
		for (int i = 0; i < n - 1; i++)
		{
			first = first->next;
		}
		while (first->next != nullptr)
		{
			first = first->next;
			second = second->next;
		}

		//2.删除链表中的某一节点
		if (second->next != nullptr)
		{
			ListNode* pNext = second->next;
			second->val = pNext->val;
			second->next = pNext->next;
			delete pNext;
			pNext = nullptr;
		}
		else if (head == second && n == 1)
		{
			delete head;
			head = nullptr;
		}
		else
		{
			ListNode* pNode = head;
			while (pNode->next != second)
				pNode = pNode->next;
			delete second;
			pNode->next = nullptr;
			second = nullptr;
		}
		return head;
	}
};

int main_leecode_unknown1()
{
	ListNode *node1 = new ListNode(1);
	ListNode *node2 = new ListNode(2);
	ListNode *node3 = new ListNode(3);
	node1->next = node2;
	node2->next = node3;
	Solution s;
	s.removeNthFromEnd(node1, 1);

	return 0;
}