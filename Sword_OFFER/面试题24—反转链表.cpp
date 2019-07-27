// ������24����ת����
// ��Ŀ������һ��������ת��������������ı�ͷ��

#include <iostream>
#include <string>
#include "List.h"
using namespace std;

class Solution 
{
public:
	//Ϊ�˱�֤�����ڷ�תʱ�����ѣ���Ҫ��¼�����ڵ㣺��ǰ�ڵ㣬��ǰ�ڵ��ǰһ�ڵ����һ�ڵ�
	//����ʱ�䣺3ms��ռ���ڴ棺456k
	ListNode* ReverseList(ListNode* pHead) 
	{
		if (pHead == nullptr)
			return nullptr;

		ListNode* pPrevNode = nullptr;
		ListNode* pNode = pHead;
		ListNode* pPostNode = nullptr;

		while (pNode != nullptr)
		{
			pPostNode = pNode->m_pNext;
			pNode->m_pNext = pPrevNode;
			pPrevNode = pNode;
			pNode = pPostNode;
		}
		//�������ɵã����ﵽpNodeΪnullptrʱ����ǰ�ڵ�Ϊ����ͷ�ڵ�
		return pPrevNode;
	}
};

// ====================���Դ���====================
ListNode* Test(ListNode* pHead)
{
	printf("The original list is: \n");
	PrintList(pHead);
	Solution s;
	ListNode* pReversedHead = s.ReverseList(pHead);

	printf("The reversed list is: \n");
	PrintList(pReversedHead);

	return pReversedHead;
}

// ����������ж�����
static void Test1()
{
	ListNode* pNode1 = CreateListNode(1);
	ListNode* pNode2 = CreateListNode(2);
	ListNode* pNode3 = CreateListNode(3);
	ListNode* pNode4 = CreateListNode(4);
	ListNode* pNode5 = CreateListNode(5);

	ConnectListNodes(pNode1, pNode2);
	ConnectListNodes(pNode2, pNode3);
	ConnectListNodes(pNode3, pNode4);
	ConnectListNodes(pNode4, pNode5);

	ListNode* pReversedHead = Test(pNode1);

	DestroyList(pReversedHead);
}

// ���������ֻ��һ�����
static void Test2()
{
	ListNode* pNode1 = CreateListNode(1);

	ListNode* pReversedHead = Test(pNode1);

	DestroyList(pReversedHead);
}

// ���������
static void Test3()
{
	Test(nullptr);
}

int main_offer24(int argc, char* argv[])
{
	Test1();
	Test2();
	Test3();

	return 0;
}