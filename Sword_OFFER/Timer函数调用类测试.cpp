#include <iostream>
#include <queue>
#include <deque>
#include <thread>
#include <time.h>
#include <vector>
using namespace std;

//���Գ�����ģ�����m_ptr����������һ��

class Data
{
public:
	//ע��ʱ����õ��ķ�ʽ��time(NULL)���ɣ���ʾ��1970��1��1��������������ǳ�����
	time_t m_time = time(NULL);
	//����ע�⣬����һ��ָ��nullptr�ĺ���ָ�룬Ȼ�󲻶ϵظ�ֵ
	//Ŀǰ����һ�����⣬����ֻ�ܸ��������ptr��ȷ��ʹ�����ֺ�����ָ�루��void�͵ģ������ǲ���ʵ�ֺ����Ĳ�����������ƥ��
	void (*m_ptr)() = nullptr;
};

class compare
{
public:
	bool operator()(Data &a, Data &b) { return(a.m_time > b.m_time); };
};

class Timer
{
public:
	priority_queue<Data, deque<Data>, compare> m_pQueue;
	//�ڲ����һ����ʱ����ÿX���ӣ�X�����������ã�����һ�δ˺�������
	void checkSelf()
	{
		time_t cur_time = time(NULL);
		while (!m_pQueue.empty())
		{
			Data temp = m_pQueue.top();
			if (temp.m_time <= cur_time)
			{
				temp.m_ptr();
				m_pQueue.pop();
			}
			else
				break;
		}
	}
};

void fun1() { cout << "fun1" << endl; }
void fun2() { cout << "fun2" << endl; }
void fun3() { cout << "fun3" << endl; }

int main_timertest()
{
	Timer t;

	Data d1;
	int d1_time = 1;
	void(*p1)() = fun1;
	d1.m_ptr = p1;
	d1.m_time = time(NULL) + d1_time;
	t.m_pQueue.push(d1);

	Data d2;
	int d2_time = 2;
	void(*p2)() = fun2;
	d2.m_ptr = p2;
	d2.m_time = time(NULL) + d2_time;
	t.m_pQueue.push(d2);

	Data d3;
	int d3_time = 3;
	void(*p3)() = fun3;
	d3.m_ptr = p3;
	d3.m_time = time(NULL) + d3_time;
	t.m_pQueue.push(d3);

	t.checkSelf();

	return 0;
}