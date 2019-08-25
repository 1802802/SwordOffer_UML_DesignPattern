// ������18��������ɾ���������ظ��Ľ��
// ��Ŀ����һ������������У������ظ��Ľ�㣬��ɾ�����������ظ��Ľ�㣬�ظ��Ľ�㲻��������������ͷָ�롣 
// ���磬����1->2->3->3->4->4->5 �����Ϊ 1->2->5

#include <iostream>
using namespace std;

struct ListNode
{
	int val;
	struct ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

//��������������Ҫ����һλ��ͬ��ֵ���Լ�ȥ��������ͬ��ֵ
//��Ҫ˼·���ݹ�˼�룬pHead��pNext�����ڵ���ǰ�ƽ���Head�����ף�Next�����ƣ����ڱ���һλ����ȫȥ����
//�������ڣ��ڵݹ�ʱ���׽ڵ�ѡȡ���һλ��Head��������һ��ֵ��Next

class Solution 
{
public:
	//ɾ���ظ��Ľڵ㣬�ظ���ֻ����һλ��
	//EX:ԭ����1->2->3->3->4��ɾ����1->2->3->4
	ListNode* deleteDuplication1(ListNode* pHead)
	{
		//1.����ֵ�ж�
		if (pHead == nullptr || pHead->next == nullptr)
			return pHead;
		//2.˫ָ�������
		ListNode* pNext = pHead->next;
		//3.��ͷ�ڵ��費��Ҫ��ɾ������������ǰ��˼��
		if (pHead->val == pNext->val)
		{
			//3.1ֱ���ҵ���ͷ�ڵ�ֵ��ͬ���¸�ֵ
			while (pNext->next != nullptr && pNext->val == pNext->next->val)
				pNext = pNext->next;
			return deleteDuplication1(pNext);
		}
		else
		{
			//3.2���ǰ��ֵ��ͬ����ô��next�ڵ㿪ʼ�����������
			pHead->next = deleteDuplication1(pHead->next);
			return pHead;
		}
	}

	//�������������ɾ���������ظ��Ľڵ㣬����ʱ�䣺4ms��ռ���ڴ棺484k
	ListNode* deleteDuplication(ListNode* pHead)
	{
		//1.����ֵ�ж�
		if (pHead == nullptr || pHead->next == nullptr)
			return pHead;
		//2.˫ָ�������
		ListNode* pNext = pHead->next;
		//3.��ͷ�ڵ��費��Ҫ��ɾ������������ǰ��˼��
		if (pHead->val == pNext->val)
		{
			//3.1ֱ���ҵ���ͷ�ڵ�ֵ��ͬ���¸�ֵ��Ȼ���pNext���¸��ڵ㿪ʼ�㣨ɾ�������ظ�ֵ�ĵ㣩
			while (pNext->next != nullptr && pNext->val == pNext->next->val)
				pNext = pNext->next;
			return deleteDuplication(pNext->next);
		}
		else
		{
			//3.2���ǰ��ֵ��ͬ����ô��next�ڵ㿪ʼ�����������
			pHead->next = deleteDuplication(pHead->next);
			return pHead;
		}
	}

	//������ı���һλ
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

	//������Ĳ�����
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