// 面试题18（一）：在O(1)时间删除链表结点
// 题目：给定单向链表的头指针和一个结点指针，定义一个函数在O(1)时间删除该结点。

#include <iostream>
using namespace std;

struct ListNode 
{
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

//常规策略是遍历找到对应的节点，然后交换其前后指针并删除即可；
//但是为了实现本题所述的O(1)时间复杂度，需要做的是将需要删除的节点的后面的节点与该节点进行交换，避免了遍历查找的过程
void DeleteNode(ListNode** pListHead, ListNode* pToBeDeleted)
{
	//1.正常情况，需要删除的节点next节点存在,代表其一不是尾节点，而不是单一节点
	if (pToBeDeleted->next != nullptr)
	{
		ListNode* pNext = pToBeDeleted->next;
		pToBeDeleted->val = pNext->val;
		pToBeDeleted->next = pNext->next;
		delete pNext;
		pNext = nullptr;
	}
	//2.如果需要被删除的节点就是头节点，同时其next节点为空
	else if (pToBeDeleted == *pListHead)
	{
		delete pToBeDeleted;
		pToBeDeleted = nullptr;
		*pListHead = nullptr;
		pListHead = nullptr;
	}
	//3.在这种情况，则表示要删除的节点为尾节点，其后部next为空，必须遍历过去到尾节点的前一节点进行操作
	else
	{
		ListNode* pNode = *pListHead;
		while (pNode->next != pToBeDeleted)
			pNode = pNode->next;
		delete pToBeDeleted;
		pNode->next = nullptr;
		pToBeDeleted = nullptr;
	}
}
