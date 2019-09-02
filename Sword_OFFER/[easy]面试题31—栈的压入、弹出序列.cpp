// 面试题30—栈的压入、弹出序列
// 题目：输入两个整数序列，第一个序列表示栈的压入顺序，请判断第二个序列是否可能为该栈的弹出顺序。假设压入栈的所有数字均不相等。
// 例如序列1,2,3,4,5是某栈的压入顺序，序列4,5,3,2,1是该压栈序列对应的一个弹出序列，但4,3,5,1,2就不可能是该压栈序列的弹出序列。
// （注意：这两个序列的长度是相等的）

#include <iostream>
#include <vector>
#include <stack>
#include <assert.h>
using namespace std;

class Solution 
{
public:
	//运行时间：4ms，占用内存：476k
	bool IsPopOrder(vector<int> pushV, vector<int> popV) 
	{
		//1.需要明确在没有数的情况下如何判定true和false
		if (pushV.size() == 0 || popV.size() == 0)
			return false;
		stack<int> help;
		int nPush = 0, nPop = 0;
		//2.判断条件很简单，就是栈顶与popV索引不等于就push，当push到头了还不等于就false；
		//等于就加pop索引并help出栈；直到最后栈空了，两个索引也刚好都到头了成功，否则失败（如123与32）
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

// ====================测试代码====================
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

// push和pop序列只有一个数字
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