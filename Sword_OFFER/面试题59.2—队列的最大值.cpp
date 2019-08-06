// ������59.2�����е����ֵ
// ��Ŀ���붨��һ�����в�ʵ�ֺ���max�õ�����������ֵ��Ҫ����max��push_back��pop_front��ʱ�临�Ӷ�ΪO(1)

#include <map>
#include <deque>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
#include "BinaryTree.h"
using namespace std;

//ʵ�ֶ��е����ֵ����ʵ��һ����������Ϊ���޴������洢��Сֵ�����иû�������ͨ��deque���±�

//���ɣ��ɼ������е����ֵʵ����Ҫ����dequeЭ������stack�����ֵҲ��Ҫ����stackЭ��

//��ס��Ҫʵ������λ�õĵ�ǰ���ֵ���������ȼ����в���ȡ������ʵ�ֵ���queue������push��pop��top��
template<typename T> class QueueWithMax
{
public:
	QueueWithMax() :currentIndex(0) {}
	void push_back(T n)
	{
		//���ڴ������޴�������������׽ڵ�Ĺ��ڴ���ֻ����β�ڵ��pop����
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
		//����Ҫ��pop��indexΪ��ǰmaxNum��indexʱ���Ŷ�maxNum����pop�����ʾǰ��max���������
		//������ʵ��max�ĺ��ģ���indexС��maxNum��front��indexʱ���������maxNum����pop_front
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

// ====================���Դ���====================
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