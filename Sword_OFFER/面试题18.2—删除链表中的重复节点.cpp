// 面试题18（二）：删除链表中重复的结点
// 题目：在一个排序的链表中，存在重复的结点，请删除该链表中重复的结点，重复的结点不保留，返回链表头指针。 
// 例如，链表1->2->3->3->4->4->5 处理后为 1->2->5

#include <iostream>
using namespace std;

struct ListNode
{
	int val;
	struct ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

//针对两种情况：需要保留一位相同的值，以及去掉所有相同的值
//主要思路：递归思想，pHead和pNext两个节点向前推进，Head用于首，Next用于推，对于保留一位和完全去掉的
//区别在于，在递归时的首节点选取最后一位的Head，还是下一个值的Next

class Solution 
{
public:
	//删除重复的节点，重复的只保留一位：
	//EX:原链表1->2->3->3->4，删除后1->2->3->4
	ListNode* deleteDuplication1(ListNode* pHead)
	{
		//1.输入值判断
		if (pHead == nullptr || pHead->next == nullptr)
			return pHead;
		//2.双指针搞起来
		ListNode* pNext = pHead->next;
		//3.从头节点需不需要被删除来进行两种前进思想
		if (pHead->val == pNext->val)
		{
			//3.1直到找到和头节点值不同的下个值
			while (pNext->next != nullptr && pNext->val == pNext->next->val)
				pNext = pNext->next;
			return deleteDuplication1(pNext);
		}
		else
		{
			//3.2如果前后值不同，那么从next节点开始继续往后计算
			pHead->next = deleteDuplication1(pHead->next);
			return pHead;
		}
	}

	//针对题意的情况，删除所有有重复的节点，运行时间：4ms，占用内存：484k
	ListNode* deleteDuplication(ListNode* pHead)
	{
		//1.输入值判断
		if (pHead == nullptr || pHead->next == nullptr)
			return pHead;
		//2.双指针搞起来
		ListNode* pNext = pHead->next;
		//3.从头节点需不需要被删除来进行两种前进思想
		if (pHead->val == pNext->val)
		{
			//3.1直到找到和头节点值不同的下个值，然后从pNext的下个节点开始算（删除了有重复值的点）
			while (pNext->next != nullptr && pNext->val == pNext->next->val)
				pNext = pNext->next;
			return deleteDuplication(pNext->next);
		}
		else
		{
			//3.2如果前后值不同，那么从next节点开始继续往后计算
			pHead->next = deleteDuplication(pHead->next);
			return pHead;
		}
	}

	//迭代版的保留一位
	ListNode* deleteDuplication2(ListNode* pHead)
	{
		if (pHead == nullptr || pHead->next == nullptr)
			return pHead;
		ListNode* pPrev = pHead;
		ListNode* pNode = pHead->next;
		bool flag = false;
		while (pNode != nullptr && pPrev != nullptr)
		{
			if (pPrev->val != pNode->val)
			{
				if (flag)
					pPrev->next = pNode;
				pPrev = pNode;
				pNode = pNode->next;
				flag = false;
			}
			else
			{
				pNode = pNode->next;
				flag = true;
			}
		}
		pPrev->next = pNode;
		return pHead;
	}

	//迭代版的不保留
	//ListNode* deleteDuplication3(ListNode* pHead)
	//{
	//	if (pHead == nullptr || pHead->next == nullptr)
	//		return pHead;
	//	ListNode* pPrev = pHead;
	//	ListNode* pNode = pHead->next;
	//	while (pNode != nullptr && pPrev != nullptr)
	//	{
	//		while (pNode->next != nullptr && pNode->next->val == pNode->val)
	//			pNode = pNode->next;
	//		pPrev->next = pNode->next;
	//		pPrev = pNode->next;
	//	}
	//	pPrev->next = pNode;
	//	return pHead;
	//}
};

int main_offer18_2()
{
	ListNode* node1 = new ListNode(1);
	ListNode* node2 = new ListNode(2);
	ListNode* node3 = new ListNode(3);
	ListNode* node4 = new ListNode(3);
	ListNode* node5 = new ListNode(4);
	node1->next = node2;
	node2->next = node3;
	node3->next = node4;
	node4->next = node5;

	ListNode* node = node1;
	while (node != nullptr)
	{
		cout << node->val << " ";
		node = node->next;
	}
	cout << endl;

	Solution s;
	node = s.deleteDuplication(node1);
	while (node != nullptr)
	{
		cout << node->val << " ";
		node = node->next;
	}
	cout << endl;

	return 0;
}