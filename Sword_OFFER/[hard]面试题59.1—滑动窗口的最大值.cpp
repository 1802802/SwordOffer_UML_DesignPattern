// 面试题59.1：滑动窗口的最大值
// 题目：给定一个数组和滑动窗口的大小，找出所有滑动窗口里数值的最大值。
// 例如，如果输入数组{2,3,4,2,6,2,5,1}及滑动窗口的大小3，那么一共存在6个滑动窗口，
// 他们的最大值分别为{4,4,6,6,6,5}； 针对数组{2,3,4,2,6,2,5,1}的滑动窗口有以下6个：
// {[2,3,4],2,6,2,5,1}， {2,[3,4,2],6,2,5,1}， {2,3,[4,2,6],2,5,1}， {2,3,4,[2,6,2],5,1}， 
// {2,3,4,2,[6,2,5],1}， {2,3,4,2,6,[2,5,1]}。

#include <map>
#include <deque>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
#include "BinaryTree.h"
using namespace std;

class Solution 
{
public:
	//1.常规思想：暴力算法，遍历所有窗口，计算每个窗口的最大值，时间复杂度O(nk)，空间复杂度O(1)
	//运行时间：6ms，占用内存：472k
	vector<int> maxInWindows(const vector<int>& num, unsigned int size)
	{
		//1.1边界条件
		if (num.empty() || size <= 0 || size > num.size())
			return vector<int>();

		int head = 0;
		int end = size - 1;
		vector<int> save;
		while (end < num.size())
		{
			int maxNum = 0;
			for (int i = head; i <= end; i++)
				maxNum = max(maxNum, num[i]);
			save.push_back(maxNum);
			head++; end++;
		}
		return save;
	}

	//2.高级思想：使用双端队列deque实现操作，即使用deque来存储滑动窗口中的最大值与备选最大值
	vector<int> maxInWindows2(const vector<int>& num, unsigned int size)
	{
		//边界条件
		if (num.empty() || size <= 0 || size > num.size())
			return vector<int>();

		//vector存最大值，deque存当前滑动窗口（其头部往往为真窗口的最大值）的下标值
		//deque中的值往往首端为最大值，而后面的值为依次的备选最大值或上一位数字
		vector<int> maxnumSave;
		deque<int> indexSave;
		for (int i = 0; i < num.size(); i++)
		{
			//2.1 如果当前滑动窗口的末端值小于当前需要插入的值，则将末端值移出窗口
			while (indexSave.size() && num[indexSave.back()] <= num[i])
				indexSave.pop_back();
			//2.2 如果当前滑动窗口的首端小于窗口界限，则将首端值移出窗口（即为最大值）
			while (indexSave.size() && i - indexSave.front() + 1 > size)
				indexSave.pop_front();
			//2.3 将新需要加入的索引i插入indexSave队列中 （无论怎么样都要插，大小之后比较）
			indexSave.push_back(i);
			if (size && i + 1 >= size)//当滑动窗口首地址i大于等于size时才开始写入窗口最大值
				maxnumSave.push_back(num[indexSave.front()]);
		}
		return maxnumSave;
	}

	//3.使用优先级队列也可以实现（类似于方法1）
};

// ====================测试代码====================
static void Test(const char* testName, const vector<int>& num, unsigned int size, const vector<int>& expected)
{
	if (testName != nullptr)
		printf("%s begins: ", testName);

	Solution s;
	vector<int> result = s.maxInWindows2(num, size);

	vector<int>::const_iterator iterResult = result.begin();
	vector<int>::const_iterator iterExpected = expected.begin();
	while (iterResult < result.end() && iterExpected < expected.end())
	{
		if (*iterResult != *iterExpected)
			break;

		++iterResult;
		++iterExpected;
	}

	if (iterResult == result.end() && iterExpected == expected.end())
		printf("Passed.\n");
	else
		printf("FAILED.\n");
}

static void Test1()
{
	int num[] = { 2, 3, 4, 2, 6, 2, 5, 1 };
	vector<int> vecNumbers(num, num + sizeof(num) / sizeof(int));

	int expected[] = { 4, 4, 6, 6, 6, 5 };
	vector<int> vecExpected(expected, expected + sizeof(expected) / sizeof(int));

	unsigned int size = 3;

	Test("Test1", vecNumbers, size, vecExpected);
}

static void Test2()
{
	int num[] = { 1, 3, -1, -3, 5, 3, 6, 7 };
	vector<int> vecNumbers(num, num + sizeof(num) / sizeof(int));

	int expected[] = { 3, 3, 5, 5, 6, 7 };
	vector<int> vecExpected(expected, expected + sizeof(expected) / sizeof(int));

	unsigned int size = 3;

	Test("Test2", vecNumbers, size, vecExpected);
}

// 输入数组单调递增
static void Test3()
{
	int num[] = { 1, 3, 5, 7, 9, 11, 13, 15 };
	vector<int> vecNumbers(num, num + sizeof(num) / sizeof(int));

	int expected[] = { 7, 9, 11, 13, 15 };
	vector<int> vecExpected(expected, expected + sizeof(expected) / sizeof(int));

	unsigned int size = 4;

	Test("Test3", vecNumbers, size, vecExpected);
}

// 输入数组单调递减
static void Test4()
{
	int num[] = { 16, 14, 12, 10, 8, 6, 4 };
	vector<int> vecNumbers(num, num + sizeof(num) / sizeof(int));

	int expected[] = { 16, 14, 12 };
	vector<int> vecExpected(expected, expected + sizeof(expected) / sizeof(int));

	unsigned int size = 5;

	Test("Test4", vecNumbers, size, vecExpected);
}

// 滑动窗口的大小为1
static void Test5()
{
	int num[] = { 10, 14, 12, 11 };
	vector<int> vecNumbers(num, num + sizeof(num) / sizeof(int));

	int expected[] = { 10, 14, 12, 11 };
	vector<int> vecExpected(expected, expected + sizeof(expected) / sizeof(int));

	unsigned int size = 1;

	Test("Test5", vecNumbers, size, vecExpected);
}

// 滑动窗口的大小等于数组的长度
static void Test6()
{
	int num[] = { 10, 14, 12, 11 };
	vector<int> vecNumbers(num, num + sizeof(num) / sizeof(int));

	int expected[] = { 14 };
	vector<int> vecExpected(expected, expected + sizeof(expected) / sizeof(int));

	unsigned int size = 4;

	Test("Test6", vecNumbers, size, vecExpected);
}

// 滑动窗口的大小为0
static void Test7()
{
	int num[] = { 10, 14, 12, 11 };
	vector<int> vecNumbers(num, num + sizeof(num) / sizeof(int));

	vector<int> vecExpected;

	unsigned int size = 0;

	Test("Test7", vecNumbers, size, vecExpected);
}

// 滑动窗口的大小大于输入数组的长度
static void Test8()
{
	int num[] = { 10, 14, 12, 11 };
	vector<int> vecNumbers(num, num + sizeof(num) / sizeof(int));

	vector<int> vecExpected;

	unsigned int size = 5;

	Test("Test8", vecNumbers, size, vecExpected);
}

// 输入数组为空
static void Test9()
{
	vector<int> vecNumbers;
	vector<int> vecExpected;

	unsigned int size = 5;

	Test("Test9", vecNumbers, size, vecExpected);
}

int main_offer59_1(int argc, char* argv[])
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	Test6();
	Test7();
	Test8();
	Test9();

	return 0;
}