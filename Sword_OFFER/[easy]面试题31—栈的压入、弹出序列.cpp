// ������30��ջ��ѹ�롢��������
// ��Ŀ�����������������У���һ�����б�ʾջ��ѹ��˳�����жϵڶ��������Ƿ����Ϊ��ջ�ĵ���˳�򡣼���ѹ��ջ���������־�����ȡ�
// ��������1,2,3,4,5��ĳջ��ѹ��˳������4,5,3,2,1�Ǹ�ѹջ���ж�Ӧ��һ���������У���4,3,5,1,2�Ͳ������Ǹ�ѹջ���еĵ������С�
// ��ע�⣺���������еĳ�������ȵģ�

#include <iostream>
#include <vector>
#include <stack>
#include <assert.h>
using namespace std;

class Solution 
{
public:
	//����ʱ�䣺4ms��ռ���ڴ棺476k
	bool IsPopOrder(vector<int> pushV, vector<int> popV) 
	{
		//1.��Ҫ��ȷ��û���������������ж�true��false
		if (pushV.size() == 0 || popV.size() == 0)
			return false;
		stack<int> help;
		int nPush = 0, nPop = 0;
		//2.�ж������ܼ򵥣�����ջ����popV���������ھ�push����push��ͷ�˻������ھ�false��
		//���ھͼ�pop������help��ջ��ֱ�����ջ���ˣ���������Ҳ�պö���ͷ�˳ɹ�������ʧ�ܣ���123��32��
		while (nPush < pushV.size() || nPop < popV.size())
		{
			if (help.empty() || help.top() != popV[nPop])
			{
				if (nPush < pushV.size())
					help.push(pushV[nPush++]);
				else
					return false;
			}
			else
			{
				help.pop();
				nPop++;
			}
		}
		if (help.empty())
			return true;
		else
			return false;
	}

	bool IsPopOrder2(vector<int> pushV, vector<int> popV)
	{
		if (pushV.empty() || popV.empty())
			return false;
		vector<int> stack;
		for (int i = 0, j = 0; i < pushV.size(); i++)
		{
			stack.push_back(pushV[i]);
			while (!stack.empty() && j < popV.size() && stack.back() == popV[j])
			{
				stack.pop_back();
				j++;
			}
		}
		return stack.empty();
	}
};

// ====================���Դ���====================
static void Test(const char* testName, vector<int> pushV, vector<int> popV, int nLength, bool expected)
{
	if (testName != nullptr)
		printf("%s begins: ", testName);

	Solution s;
	if (s.IsPopOrder(pushV, popV) == expected)
		printf("Passed.\n");
	else
		printf("failed.\n");
}

static void Test1()
{
	const int nLength = 5;
	vector<int> push = { 1, 2, 3, 4, 5 };
	vector<int> pop = { 4, 5, 3, 2, 1 };

	Test("Test1", push, pop, nLength, true);
}

static void Test2()
{
	const int nLength = 5;
	vector<int> push = { 1, 2, 3, 4, 5 };
	vector<int> pop = { 3, 5, 4, 2, 1 };

	Test("Test2", push, pop, nLength, true);
}

static void Test3()
{
	const int nLength = 5;
	vector<int> push = { 1, 2, 3, 4, 5 };
	vector<int> pop = { 4, 3, 5, 1, 2 };

	Test("Test3", push, pop, nLength, false);
}

static void Test4()
{
	const int nLength = 5;
	vector<int> push = { 1, 2, 3, 4, 5 };
	vector<int> pop = { 3, 5, 4, 1, 2 };

	Test("Test4", push, pop, nLength, false);
}

// push��pop����ֻ��һ������
static void Test5()
{
	const int nLength = 1;
	vector<int> push = { 1 };
	vector<int> pop = { 2 };

	Test("Test5", push, pop, nLength, false);
}

static void Test6()
{
	const int nLength = 1;
	vector<int> push = { 1 };
	vector<int> pop = { 1 };

	Test("Test6", push, pop, nLength, true);
}

static void Test7()
{
	Test("Test7", vector<int>(), vector<int>(), 0, false);
}				 

int main_offer31(int argc, char* argv[])
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	Test6();
	Test7();

	return 0;
}