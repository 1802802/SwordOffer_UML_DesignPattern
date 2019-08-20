#include <iostream>
#include <stack>
#include <queue>
using namespace std;

//两个栈实现队列（一存一删，资源申请）牛客网3ms 488K
template<typename T> class Solution
{
public:
	//栈1中push数据
	void push(T node) 
	{
		stack1.push(node);
	}

	int pop() 
	{
		//1.先判断栈2是否为空，空则申请数据
		if (stack2.size() <= 0)
		{
			while (stack1.size() > 0)
			{
				stack2.push(stack1.top());
				stack1.pop();
			}
			//申请完后判断栈2有没有数据（异常处理为了过牛客网可改成return 0）
			if (stack2.size() <= 0)
				throw new exception("queue is empty!");
		}
		//2.在栈2中删数据
		T head = stack2.top();
		stack2.pop();

		return head;
	}

private:
	//栈1存数据，栈2删数据，栈2数据来自栈1的倾倒，当其为空时向栈1申请
	stack<T> stack1;
	stack<T> stack2;
};

//两个队列实现栈（循环使用，插有数据的，在队伍切换中删）
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
		//如果队列2有数据，则往队列1倒，同时克扣下最后的数据
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
	//栈1存数据，栈2删数据，栈2数据来自栈1的倾倒，当其为空时向栈1申请
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