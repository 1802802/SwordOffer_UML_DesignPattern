/*
ѭ�����У��������������ȳ������ԡ����Ƕ��ڶ������ɾ����ͷ�Ժ�ʣ�µĿռ佫���ᱻ�ͷţ������ڶ���ֻ���ɶ�β������͵��±�ɾ�����ֵĿռ䱻�˷ѡ�
�������������ѭ�����С�ѭ�����й���˼����ǽ����д������γ�һ�������뻷�Ľṹ��
����ԭ��������Ĳ�����Ȼ�в�ͬ�ĵط���
1.�ж�����ѭ�����е���������rear=front ���Ǹĳ�(rear-front+maxn)%maxn��
2.��Ӳ���: data[rear] = x; rear = (rear+1)%maxn;

����˼����ǲ���rear��front��ֵ����maxn�Ĵ�С�����Ǿ���rear��front����ʱ��ģmaxn��
ע�⣡�����ն�ʱrear����front������ʱ�����һ��λ�á���sizeֻ�ܴ�size - 1
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
		//m_front��m_rear�����ƶ���%size���жϣ�����size = 10��m_rear = 9, m_front = 0���������Ҫ���ǻ��λػ�
		return m_front == (m_rear + 1) % m_size;
	}
	void push(T data)
	{
		if (isFull())
		{
			throw new exception("��ǰ���ζ������������������push");
		}
		m_data[m_rear] = data;
		m_rear = (m_rear + 1) % m_size;
	}
	void pop()
	{
		if (isEmpty())
		{
			throw new exception("��ǰ���ζ���Ϊ�գ����������pop");
		}
		m_front = (m_front + 1) % m_size;
	}
	void popall()
	{
		if (isEmpty())
		{
			throw new exception("��ǰ���ζ���Ϊ�գ����������pop");
		}
		//while (m_front != m_rear)
		//	m_front = (m_front + 1) % m_size;
		m_rear = m_front;
	}
	T top()
	{
		if (isEmpty())
		{
			throw new exception("��ǰ���ζ���Ϊ�գ�û��top����");
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
