// ������24����ת����
// ��Ŀ������һ��������ת��������������ı�ͷ��

#include <iostream>
#include "List.h"
using namespace std;

class Solution 
{
public:
	//Ϊ�˱�֤�����ڷ�תʱ�����ѣ���Ҫ��¼�����ڵ㣺��ǰ�ڵ㣬��ǰ�ڵ��ǰһ�ڵ����һ�ڵ�
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