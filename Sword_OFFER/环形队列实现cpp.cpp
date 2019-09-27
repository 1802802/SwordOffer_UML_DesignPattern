/*
循环队列：队列有着先入先出的特性。但是对于队列如果删除队头以后剩下的空间将不会被释放，又由于队列只能由队尾插入这就导致被删除部分的空间被浪费。
解决这个问题就是循环队列。循环队列顾名思义就是将队列串起来形成一个类似与环的结构。
对于原来队列里的操作自然有不同的地方：
1.判断满：循环队列的满不再是rear=front 而是改成(rear-front+maxn)%maxn。
2.入队操作: data[rear] = x; rear = (rear+1)%maxn;

总体思想就是不让rear和front的值超过maxn的大小。于是就在rear和front自增时候模maxn。
注意！！：空队时rear等于front，满队时必须空一个位置。即size只能存size - 1
*/

#include <iostream>
using namespace std;

template<typename T> class circlequeue
{
private:
	unsigned int m_size;
	int m_front;
	int m_rear;
	T* m_data;
public:
	circlequeue(unsigned int size)
	{
		m_front = m_rear = 0;
		m_data = new T[m_size = size];
	}
	~circlequeue()
	{
		delete[] m_data;
	}
	bool isEmpty()
	{
		return m_front == m_rear;
	}
	bool isFull()
	{
		//m_front与m_rear均会移动，%size来判断，比如size = 10，m_rear = 9, m_front = 0的情况，需要考虑环形回环
		return m_front == (m_rear + 1) % m_size;
	}
	void push(T data)
	{
		if (isFull())
		{
			throw new exception("当前环形队列已满，不允许继续push");
		}
		m_data[m_rear] = data;
		m_rear = (m_rear + 1) % m_size;
	}
	void pop()
	{
		if (isEmpty())
		{
			throw new exception("当前环形队列为空，不允许继续pop");
		}
		m_front = (m_front + 1) % m_size;
	}
	void popall()
	{
		if (isEmpty())
		{
			throw new exception("当前环形队列为空，不允许继续pop");
		}
		//while (m_front != m_rear)
		//	m_front = (m_front + 1) % m_size;
		m_rear = m_front;
	}
	T top()
	{
		if (isEmpty())
		{
			throw new exception("当前环形队列为空，没有top对象");
		}
		return m_data[m_front];
	}
};

int main_circlequeue()
{
	circlequeue<int> q(5);
	q.push(1);
	q.push(2);
	q.push(3);
	q.push(4);
	for (int i = 0; i < 4; i++)
	{
		cout << q.top() << endl;
		q.pop();
	}
	q.push(5);
	q.push(5);
	q.push(5);
	cout << q.top() << endl;
	q.pop();
	cout << q.top() << endl;
	q.pop();
	cout << q.top() << endl;
	q.pop();
	q.push(5);
	q.push(5);
	q.push(5);
	q.popall();
	q.push(1);
	q.push(2);
	q.push(3);
	cout << q.top() << endl;
	q.pop();
	cout << q.top() << endl;
	q.pop();
	cout << q.top() << endl;
	q.pop();
	//cout << q.top() << endl;
	//q.pop();

	return 0;
}
