// ������30������min������ջ
// ��Ŀ������ջ�����ݽṹ�����ڸ�������ʵ��һ���ܹ��õ�ջ��������СԪ�ص�min������ʱ�临�Ӷ�ӦΪO��1������
// ��Ŀ����˼�Ǹ�������ջʵ��һ����ջ�������ջ��min����������min��push��pop��ʱ�临�Ӷȶ�ΪO(1)

#include <iostream>
#include <vector>
#include <stack>
#include <assert.h>
using namespace std;

class Solution 
{
public:
	//˼·��ͨ������ջ��ʵ�ֶ�������Сֵ�Ĵ洢��ջ�����ݽṹ��������������ʵ�֣����е���������
	//����ʱ�䣺3ms��ռ���ڴ棺472k����֪����������ʲô�磬ʵ�ֲ���
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