#include <vector>
#include <iostream>
#include <sstream>
#include <queue>
using namespace std;

struct RandomListNode 
{
	int label;
	struct RandomListNode *next, *random;
	RandomListNode(int x) :  label(x), next(NULL), random(NULL) {}
};

class Solution
{
public:
	//运行时间：4ms，占用内存：480k
	RandomListNode* Clone(RandomListNode* pHead)
	{
		if (pHead == nullptr)
			return nullptr;
		CloneAllNode(pHead);
		CloneAllConnect(pHead);
		return SeparateAllCloneNode(pHead);
	}

	void CloneAllNode(RandomListNode* pHead)
	{
		if (pHead == nullptr)
			return;
		RandomListNode* pNode = new RandomListNode(pHead->label);
		pNode->next = pHead->next;
		pHead->next = pNode;
		CloneAllNode(pNode->next);
	}

	void CloneAllConnect(RandomListNode* pHead)
	{
		if (pHead == nullptr)
			return;
		RandomListNode* pNode = pHead->next;
		if (pHead->random != nullptr)
			pNode->random = pHead->random->next;
		else
			pNode->random = nullptr;
		CloneAllConnect(pNode->next);
	}

	RandomListNode* SeparateAllCloneNode(RandomListNode* pHead)
	{
		if (pHead == nullptr)
			return nullptr;
		RandomListNode* pNode = pHead->next;
		pHead->next = pNode->next;			//这句是为了将原链表的指向复原
		pNode->next = SeparateAllCloneNode(pNode->next);
		return pNode;
	}
};

int main_offer35_plus()
{
	Solution s;
	RandomListNode* p1 = new RandomListNode(1);
	RandomListNode* p2 = new RandomListNode(2);
	RandomListNode* p3 = new RandomListNode(3);
	RandomListNode* p4 = new RandomListNode(4);
	p1->next = p2;
	p2->next = p3;
	p3->next = p4;
	p1->random = p3;
	p2->random = p1;
	int n = 5;
	while (n--)
	{
		RandomListNode* p5 = s.Clone(p1);
		while (p5 != nullptr)
		{
			cout << p5->label << " ";
			if (p5->random == nullptr)
				cout << "#" << " ";
			else
				cout << p5->random->label << " ";
			p5 = p5->next;
		}
		cout << endl;
	}

	return 0;
}