#include <iostream>
#include <queue>
#include <deque>
#include <thread>
#include <time.h>
#include <vector>
using namespace std;

//可以尝试用模板代替m_ptr的类型来试一下

class Data
{
public:
	//注意时间戳得到的方式：time(NULL)即可，表示从1970年1月1日至今的秒数，非常好用
	time_t m_time = time(NULL);
	//核心注意，定义一个指向nullptr的函数指针，然后不断地赋值
	//目前还有一个问题，就是只能根据这里的ptr来确定使用哪种函数的指针（如void型的），还是不能实现函数的参数配置与自匹配
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
	//内部设计一个定时器，每X秒钟（X秒钟随意设置）调用一次此函数即可
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