// 面试题30—包含min函数的栈
// 题目：定义栈的数据结构，请在该类型中实现一个能够得到栈中所含最小元素的min函数（时间复杂度应为O（1））。
// 题目的意思是根据已有栈实现一个新栈，这个新栈有min函数，并且min、push和pop的时间复杂度都为O(1)

#include <iostream>
#include <vector>
#include <stack>
#include <assert.h>
using namespace std;

class Solution 
{
public:
	//思路：通过辅助栈来实现对所有最小值的存储（栈的数据结构可以用数组轻松实现，队列的则是链表）
	//运行时间：3ms，占用内存：472k。不知道主函数抽什么风，实现不了
	stack<int> m_data;
	stack<int> m_mindata;
	void push(int value) 
	{
		m_data.push(value);
		if (m_mindata.empty() || value < m_mindata.top())
			m_mindata.push(value);
		else
			m_mindata.push(m_mindata.top());
	}
	void pop() 
	{
		assert(m_data.size() > 0 && m_mindata.size() > 0);
		m_mindata.pop();
		m_data.pop();
	}
	int top() const
	{
		assert(m_data.size() > 0 && m_mindata.size() > 0);
		return m_data.top();
	}
	int min() const
	{
		assert(m_data.size() > 0 && m_mindata.size() > 0);
		return m_mindata.top();
	}
};

void Test(const char* testName, const Solution& stack, int expected)
{
	if (testName != nullptr)
		printf("%s begins: ", testName);

	if (stack.min() == expected)
		printf("Passed.\n");
	else
		printf("Failed.\n");
}

int main_offer30(int argc, char* argv[])
{
	Solution stack;

	stack.push(3);
	Test("Test1", stack, 3);

	stack.push(4);
	Test("Test2", stack, 3);

	stack.push(2);
	Test("Test3", stack, 2);

	stack.push(3);
	Test("Test4", stack, 2);

	stack.pop();
	Test("Test5", stack, 2);

	stack.pop();
	Test("Test6", stack, 3);

	stack.pop();
	Test("Test7", stack, 3);

	stack.push(0);
	Test("Test8", stack, 0);

	return 0;
}