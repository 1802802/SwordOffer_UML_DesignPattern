// ������18��һ������O(1)ʱ��ɾ��������
// ��Ŀ���������������ͷָ���һ�����ָ�룬����һ��������O(1)ʱ��ɾ���ý�㡣

#include <iostream>
using namespace std;

struct ListNode 
{
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

//��������Ǳ����ҵ���Ӧ�Ľڵ㣬Ȼ�󽻻���ǰ��ָ�벢ɾ�����ɣ�
//����Ϊ��ʵ�ֱ���������O(1)ʱ�临�Ӷȣ���Ҫ�����ǽ���Ҫɾ���Ľڵ�ĺ���Ľڵ���ýڵ���н����������˱������ҵĹ���
void DeleteNode(ListNode** pListHead, ListNode* pToBeDeleted)
{
	//1.�����������Ҫɾ���Ľڵ�next�ڵ����,������һ����β�ڵ㣬�����ǵ�һ�ڵ�
	if (pToBeDeleted->next != nullptr)
	{
		ListNode* pNext = pToBeDeleted->next;
		pToBeDeleted->val = pNext->val;
		pToBeDeleted->next = pNext->next;
		delete pNext;
		pNext = nullptr;
	}
	//2.�����Ҫ��ɾ���Ľڵ����ͷ�ڵ㣬ͬʱ��next�ڵ�Ϊ��
	else if (pToBeDeleted == *pListHead)
	{
		delete pToBeDeleted;
		pToBeDeleted = nullptr;
		*pListHead = nullptr;
		pListHead = nullptr;
	}
	//3.��������������ʾҪɾ���Ľڵ�Ϊβ�ڵ㣬���nextΪ�գ����������ȥ��β�ڵ��ǰһ�ڵ���в���
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
