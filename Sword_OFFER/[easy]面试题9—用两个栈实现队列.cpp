#include <iostream>
#include <stack>
#include <queue>
using namespace std;

//����ջʵ�ֶ��У�һ��һɾ����Դ���룩ţ����3ms 488K
template<typename T> class Solution
{
public:
	//ջ1��push����
	void push(T node) 
	{
		stack1.push(node);
	}

	int pop() 
	{
		//1.���ж�ջ2�Ƿ�Ϊ�գ�������������
		if (stack2.size() <= 0)
		{
			while (stack1.size() > 0)
			{
				stack2.push(stack1.top());
				stack1.pop();
			}
			//��������ж�ջ2��û�����ݣ��쳣����Ϊ�˹�ţ�����ɸĳ�return 0��
			if (stack2.size() <= 0)
				throw new exception("queue is empty!");
		}
		//2.��ջ2��ɾ����
		T head = stack2.top();
		stack2.pop();

		return head;
	}

private:
	//ջ1�����ݣ�ջ2ɾ���ݣ�ջ2��������ջ1���㵹������Ϊ��ʱ��ջ1����
	stack<T> stack1;
	stack<T> stack2;
};

//��������ʵ��ջ��ѭ��ʹ�ã��������ݵģ��ڶ����л���ɾ��
class Solution2
{
public:
	void push(int node)
	{
		if (queue2.size() > 0)
			queue2.push(node);
		else
			queue1.push(node);
	}

	int pop()
	{
		//�������2�����ݣ���������1����ͬʱ�˿�����������
		if (queue2.size() > 0)
		{
			while (queue2.size() > 1)
			{
				queue1.push(queue2.front());
				queue2.pop();
			}
			int head = queue2.front();
			queue2.pop();
			return head;
		}
		else if (queue1.size() > 0)
		{
			while (queue1.size() > 1)
			{
				queue2.push(queue1.front());
				queue1.pop();
			}
			int head = queue1.front();
			queue1.pop();
			return head;
		}
		else
			throw new exception("queue is empty!");
	}

private:
	//ջ1�����ݣ�ջ2ɾ���ݣ�ջ2��������ջ1���㵹������Ϊ��ʱ��ջ1����
	queue<int> queue1;
	queue<int> queue2;
};

int Fibonacci(int n) 
{
	return [&n]() {int f = 1, s = 0; while (n--) { s = f + s; f = s - f; } return s; }();
}


int main_offer9()
{
	//Solution Cstack;
	Solution2 Cstack;
	Cstack.push(1);
	Cstack.push(2);
	Cstack.push(3);
	Cstack.push(4);
	Cstack.push(5);

	cout << Cstack.pop() << endl;
	cout << Cstack.pop() << endl;
	cout << Cstack.pop() << endl;
	cout << Cstack.pop() << endl;
	cout << Cstack.pop() << endl;
	
	return 0;
}