// 面试题59.2：队列的最大值
// 题目：请定义一个队列并实现函数max得到队列里的最大值，要求函数max、push_back和pop_front的时间复杂度为O(1)

#include <map>
#include <deque>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
#include "BinaryTree.h"
using namespace std;

//实现队列的最大值，即实现一个滑动窗口为无限大的情况存储最小值，其中该滑动窗口通过deque存下标

//归纳：可见，队列的最大值实现需要两个deque协作，而stack的最大值也需要两个stack协作

//记住是要实现所有位置的当前最大值，所以优先级队列不可取（这里实现的是queue操作，push和pop与top）
template<typename T> class QueueWithMax
{
public:
	QueueWithMax() :currentIndex(0) {}
	void push_back(T n)
	{
		//由于窗口无限大，所以无需进行首节点的过期处理，只进行尾节点的pop处理
		while (maxNum.size() && n >= maxNum.back().number)
			maxNum.pop_back();
		Data d = { n, currentIndex++ }; 
		data.push_back(d);
		maxNum.push_back(d);
	}
	void pop_front()
	{
		if (maxNum.empty() && data.empty())
			throw new exception("queue is empty");
		//当需要被pop的index为当前maxNum的index时，才对maxNum进行pop（这表示前面max都是这个）
		//这行是实现max的核心，当index小于maxNum的front的index时，将不会对maxNum进行pop_front
		if (maxNum.front().index == data.front().index)
			maxNum.pop_front();
		data.pop_front();
	}
	T max() const
	{
		if (maxNum.empty())
			throw new exception("queue is empty");
		return maxNum.front().number;
	}
private:
	struct Data
	{
		T number;
		int index;
	};
	deque<Data> maxNum;
	deque<Data> data;
	int currentIndex;
};

// ====================测试代码====================
static void Test(const char* testName, const QueueWithMax<int>& queue, int expected)
{
	if (testName != nullptr)
		printf("%s begins: ", testName);

	if (queue.max() == expected)
		printf("Passed.\n");
	else
		printf("FAILED.\n");
}

int main_offer59_2(int argc, char* argv[])
{
	QueueWithMax<int> queue;
	// {2}
	queue.push_back(2);
	Test("Test1", queue, 2);

	// {2, 3}
	queue.push_back(3);
	Test("Test2", queue, 3);

	// {2, 3, 4}
	queue.push_back(4);
	Test("Test3", queue, 4);

	// {2, 3, 4, 2}
	queue.push_back(2);
	Test("Test4", queue, 4);

	// {3, 4, 2}
	queue.pop_front();
	Test("Test5", queue, 4);

	// {4, 2}
	queue.pop_front();
	Test("Test6", queue, 4);

	// {2}
	queue.pop_front();
	Test("Test7", queue, 2);

	// {2, 6}
	queue.push_back(6);
	Test("Test8", queue, 6);

	// {2, 6, 2}
	queue.push_back(2);
	Test("Test9", queue, 6);

	// {2, 6, 2, 5}
	queue.push_back(5);
	Test("Test9", queue, 6);

	// {6, 2, 5}
	queue.pop_front();
	Test("Test10", queue, 6);

	// {2, 5}
	queue.pop_front();
	Test("Test11", queue, 5);

	// {5}
	queue.pop_front();
	Test("Test12", queue, 5);

	// {5, 1}
	queue.push_back(1);
	Test("Test13", queue, 5);

	return 0;
}