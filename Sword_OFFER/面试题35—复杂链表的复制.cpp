// ������35����������ĸ���
// ��Ŀ������һ����������
// ��ÿ���ڵ����нڵ�ֵ���Լ�����ָ�룬һ��ָ����һ���ڵ㣬��һ������ָ��ָ������һ���ڵ㣬
// ���ؽ��Ϊ���ƺ��������head����ע�⣬���������벻Ҫ���ز����еĽڵ����ã�������������ֱ�ӷ��ؿգ�

#include <iostream>
#include <vector>
#include <map>
#include "List.h"
using namespace std;

struct RandomListNode 
{
	int label;
	struct RandomListNode *next, *random;
	RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
};

struct ComplexListNode
{
	int                 m_nValue;
	ComplexListNode*    m_pNext;
	ComplexListNode*    m_pSibling;
};

ComplexListNode* CreateNode(int nValue)
{
	ComplexListNode* pNode = new ComplexListNode();

	pNode->m_nValue = nValue;
	pNode->m_pNext = nullptr;
	pNode->m_pSibling = nullptr;

	return pNode;
}

static void BuildNodes(ComplexListNode* pNode, ComplexListNode* pNext, ComplexListNode* pSibling)
{
	if (pNode != nullptr)
	{
		pNode->m_pNext = pNext;
		pNode->m_pSibling = pSibling;
	}
}

static void PrintList(ComplexListNode* pHead)
{
	ComplexListNode* pNode = pHead;
	while (pNode != nullptr)
	{
		printf("The value of this node is: %d.\n", pNode->m_nValue);

		if (pNode->m_pSibling != nullptr)
			printf("The value of its sibling is: %d.\n", pNode->m_pSibling->m_nValue);
		else
			printf("This node does not have a sibling.\n");

		printf("\n");

		pNode = pNode->m_pNext;
	}
}

class Solution 
{
public:
	//1.���ϵĸ߼���������Ϊ��������������㷨��˼����Ժú���⣬������˺�Ļ������Ѷ���Ľϴ�
	ComplexListNode* Clone(ComplexListNode* pHead)
	{
		CloneNodes(pHead);
		ConnectSiblingNodes(pHead);
		return ReconnectNodes(pHead);
	}
	//1.1��һ��������ʵ�ָ���ԭʼ���������ڵ�N�������½ڵ�N'���ٰ�N'���ӵ�N�ĺ���
	void CloneNodes(ComplexListNode* pHead)
	{
		ComplexListNode* pNode = pHead;
		while (pNode != nullptr)
		{
			ComplexListNode* pCloned = new ComplexListNode();
			pCloned->m_nValue = pNode->m_nValue;
			pCloned->m_pNext = pNode->m_pNext;
			pCloned->m_pSibling = nullptr;
		
			pNode->m_pNext = pCloned;
			pNode = pCloned->m_pNext;
		}
	}
	//1.2�����ڶ���������ʵ��ԭʼ������Nָ��S��Sibling����ΪN'ָ��S'��Sibling�����ϵغ��Ʊ仯��
	void ConnectSiblingNodes(ComplexListNode* pHead)
	{
		ComplexListNode* pNode = pHead;
		while (pNode != nullptr)
		{
			ComplexListNode* pClone = pNode->m_pNext;
			if (pNode->m_pSibling != nullptr)
				pClone->m_pSibling = pNode->m_pSibling->m_pNext;
			else
				pClone->m_pSibling = nullptr;
			pNode = pClone->m_pNext;
		}
	}
	//1.3 �������������������Ѿ���ɵĿ�¡������ڵ�˫��ṹ��ɾ����������0��ʼ�㣬ż��λ�õ�Ϊԭ������λ�õ�Ϊ��¡��
	ComplexListNode* ReconnectNodes(ComplexListNode* pHead)
	{
		ComplexListNode* pNode = pHead;
		ComplexListNode* pCloneHead = nullptr;
		ComplexListNode* pCloneNode = nullptr;

		//�����Ԫ�صļ�¼���������
		if (pNode != nullptr)
		{
			pCloneHead = pCloneNode = pNode->m_pNext;
			pNode->m_pNext = pCloneHead->m_pNext;
			pNode = pNode->m_pNext;
		}
		//whileѭ��ʵ��������루�����漰������Ԫ�ؽ�����nextָ�򽻻���Ҫ������˼����
		while (pNode != nullptr)
		{
			pCloneNode->m_pNext = pNode->m_pNext;
			pCloneNode = pCloneNode->m_pNext;
			pNode->m_pNext = pCloneNode->m_pNext;
			pNode = pNode->m_pNext;
		}
		return pCloneHead;
	}


	//2.����map��clone��ԭnode�Ķ�Ӧ��ϵ��ʵ��O(n)ʱ��O(n)�ռ��ʵ�ַ�ʽ��д�ĺ����ң�˵ʵ�����ÿ�����
	//����ʱ�䣺4ms��ռ���ڴ棺608k
	ComplexListNode* Clone2(ComplexListNode* pHead)
	{
		//1.1�߽�����
		if (pHead == nullptr)
			return nullptr;
		//1.2�����¡����
		map<ComplexListNode*, ComplexListNode*> node2node;
		ComplexListNode* pClone = new ComplexListNode();     pClone->m_nValue = pHead->m_nValue;
		ComplexListNode* pCloneHead = pClone;
		ComplexListNode* pBackHead = pHead;
		node2node.insert({ pBackHead ,pCloneHead });
		pHead = pHead->m_pNext;
		while (pHead != nullptr)
		{
			ComplexListNode* pNode = new ComplexListNode();  pNode->m_nValue = pHead->m_nValue;
			node2node.insert({ pHead ,pNode });
			pHead = pHead->m_pNext;
			pClone->m_pNext = pNode;
			pClone = pNode;		
		}
		//1.3ͨ��mapʵ�������sibl����
		for (auto &s : node2node)
		{
			if (s.first->m_pSibling != nullptr)
				s.second->m_pSibling = node2node[s.first->m_pSibling];
			else
				s.second->m_pSibling = nullptr;
		}
		return pCloneHead;
	}


	//3���Ի����ⷨ����O(n2)ʱ�临�Ӷȣ�O(1)�ռ临�ӶȵĲ�����ʱ�����̫���ˣ�ѡ��ʵ�֣�
	ComplexListNode* Clone3(ComplexListNode* pHead)
	{
		//1.1�߽�����
		if (pHead == nullptr)
			return nullptr;
		//1.2�����¡����
		ComplexListNode* pClone = new ComplexListNode();
		pClone->m_nValue = pHead->m_nValue;
		ComplexListNode* pCloneHead = pClone;
		ComplexListNode* pBackHead = pHead;
		pHead = pHead->m_pNext;
		while (pHead != nullptr)
		{
			ComplexListNode* pNode = new ComplexListNode();
			pNode->m_nValue = pHead->m_nValue;
			pHead = pHead->m_pNext;
			pClone->m_pNext = pNode;
			pClone = pNode;
		}
		//1.3ʵ��m_pSibling
		pClone = pCloneHead;
		pHead = pBackHead;
		while (pHead != nullptr)
		{
			ComplexListNode* pNode = pHead->m_pSibling;
			if (pNode != nullptr)
			{
				int n = 0;
				pHead = pHead->m_pNext;
				while (pHead != nullptr)
				{
					if (pNode == pHead->m_pSibling)
						break;
					pHead = pHead->m_pNext;
					n++;
				}
			}
		}
	}
};


// ====================���Դ���====================
static void Test(const char* testName, ComplexListNode* pHead)
{
	if (testName != nullptr)
		printf("%s begins:\n", testName);

	printf("The original list is:\n");
	PrintList(pHead);

	Solution s;
	ComplexListNode* pClonedHead = s.Clone(pHead);

	printf("The cloned list is:\n");
	PrintList(pClonedHead);
}

//          -----------------
//         \|/              |
//  1-------2-------3-------4-------5
//  |       |      /|\             /|\
//  --------+--------               |
//          -------------------------
static void Test1()
{
	ComplexListNode* pNode1 = CreateNode(1);
	ComplexListNode* pNode2 = CreateNode(2);
	ComplexListNode* pNode3 = CreateNode(3);
	ComplexListNode* pNode4 = CreateNode(4);
	ComplexListNode* pNode5 = CreateNode(5);

	BuildNodes(pNode1, pNode2, pNode3);
	BuildNodes(pNode2, pNode3, pNode5);
	BuildNodes(pNode3, pNode4, nullptr);
	BuildNodes(pNode4, pNode5, pNode2);

	Test("Test1", pNode1);
}

// m_pSiblingָ��������
//          -----------------
//         \|/              |
//  1-------2-------3-------4-------5
//         |       | /|\           /|\
//         |       | --             |
//         |------------------------|
static void Test2()
{
	ComplexListNode* pNode1 = CreateNode(1);
	ComplexListNode* pNode2 = CreateNode(2);
	ComplexListNode* pNode3 = CreateNode(3);
	ComplexListNode* pNode4 = CreateNode(4);
	ComplexListNode* pNode5 = CreateNode(5);

	BuildNodes(pNode1, pNode2, nullptr);
	BuildNodes(pNode2, pNode3, pNode5);
	BuildNodes(pNode3, pNode4, pNode3);
	BuildNodes(pNode4, pNode5, pNode2);

	Test("Test2", pNode1);
}

// m_pSibling�γɻ�
//          -----------------
//         \|/              |
//  1-------2-------3-------4-------5
//          |              /|\
//          |               |
//          |---------------|
static void Test3()
{
	ComplexListNode* pNode1 = CreateNode(1);
	ComplexListNode* pNode2 = CreateNode(2);
	ComplexListNode* pNode3 = CreateNode(3);
	ComplexListNode* pNode4 = CreateNode(4);
	ComplexListNode* pNode5 = CreateNode(5);

	BuildNodes(pNode1, pNode2, nullptr);
	BuildNodes(pNode2, pNode3, pNode4);
	BuildNodes(pNode3, pNode4, nullptr);
	BuildNodes(pNode4, pNode5, pNode2);

	Test("Test3", pNode1);
}

// ֻ��һ�����
static void Test4()
{
	ComplexListNode* pNode1 = CreateNode(1);
	BuildNodes(pNode1, nullptr, pNode1);

	Test("Test4", pNode1);
}

// ³���Բ���
static void Test5()
{
	Test("Test5", nullptr);
}

int main_offer35(int argc, char* argv[])
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();

	return 0;
}

//int main()
//{
//	ComplexListNode* n1 = new ComplexListNode();
//	ComplexListNode* n2 = new ComplexListNode();
//	ComplexListNode* n3 = new ComplexListNode();
//	ComplexListNode* n4 = new ComplexListNode();
//
//	n1->m_nValue = 1;
//	n2->m_nValue = 2;
//	n3->m_nValue = 3;
//	n4->m_nValue = 4;
//
//	n1->m_pNext = n2;
//	n2->m_pNext = n3;
//	n3->m_pNext = n4;
//
//	Solution s;
//	s.Clone(n1);
//}



//if (pHead == nullptr)
//return nullptr;
//ComplexListNode* pClone = new ComplexListNode();
//pClone->m_nValue = pHead->m_nValue;
//pHead = pHead->m_pNext;
//while (pHead != nullptr)
//{
//	ComplexListNode* pNode = new ComplexListNode();
//	pNode->m_nValue = pHead->m_nValue;
//	pClone->m_pNext = pNode;
//	pClone = pNode;
//}