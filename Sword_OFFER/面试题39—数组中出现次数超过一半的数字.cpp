// 面试题39—数组中出现次数超过一半的数字
// 题目：数组中有一个数字出现的次数超过数组长度的一半，请找出这个数字。
// 例如输入一个长度为9的数组{1,2,3,2,2,2,5,4,2}。由于数字2在数组中出现了5次，超过数组长度的一半，因此输出2。如果不存在则输出0。

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
using namespace std;

class Solution 
{
public:
	//1.使用map存储，时间复杂度O(nlogn)，空间复杂度O(n)，运行时间：3ms，占用内存：468k
	int MoreThanHalfNum_Solution1(vector<int> numbers) 
	{
		map<int, int> save;
		for (auto &s : numbers)
		{
			if (!save.insert({ s,1 }).second)
				save[s]++;
		}
		for (auto &s : save)
			if (s.second > numbers.size() >> 1)
				return s.first;
		return 0;
	}
	//标准的中位数查找算法，运行时间：3ms，占用内存：472k，时间复杂度O(n)
	//2.基于partition函数的时间复杂度为O(n)的算法，从起点开始进行中位数划分，直到当前轴点到达了中位
	int MoreThanHalfNum_Solution2(vector<int> numbers)
	{
		if (!checkInvalid(numbers))
			return 0;
		int middle = numbers.size() >> 1;
		int start = 0; int end = numbers.size() - 1;
		//找轴点
		int index = Partition(numbers, start, end);
		//直到轴点和中位点位置相同，跳出（将轴点不断地逼近middle中位点）
		while (index != middle)
		{
			if (index > middle)
			{
				end = index - 1;
				index = Partition(numbers, start, end);
			}
			else
			{
				start = index + 1;
				index = Partition(numbers, start, end);
			}
		}
		int result = numbers[middle];
		if (!checkMoreThanHalf(numbers, result))
			result = 0;
		return result;
	}
	//函数1：检查合法性
	bool checkInvalid(vector<int>& numbers)
	{
		if (numbers.size() < 1)
			return false;
		return true;
	}
	//函数2：轴点快速划分算法
	int Partition(vector<int>& numbers, int start, int end)
	{
		int tmp = numbers[start];
		while (start < end)
		{
			while (start < end && numbers[end] >= tmp)
				end--;
			numbers[start] = numbers[end];
			while (start < end && numbers[start] <= tmp)
				start++;
			numbers[end] = numbers[start];
		}
		numbers[start] = tmp;
		return start;
	}
	//函数3，检查该数字是否为众数（前面所得到的result数据为数值正中间的中位数）
	bool checkMoreThanHalf(vector<int>& numbers, int result)
	{
		int num = 0;
		for (auto &s : numbers)
			if (s == result)
				num++;
		if (num * 2 > numbers.size())
			return true;
		else
			return false;
	}

	//3.众数选取算法标准版（计数方式），运行时间：3ms，占用内存：480k，时间复杂度O(n)
	int MoreThanHalfNum_Solution3(vector<int> numbers)
	{
		if (numbers.size() < 1)
			return 0;
		int result = numbers[0];
		int times = 1;
		//3.1候选点选取
		for (int i = 1; i < numbers.size(); i++)
		{
			if (numbers[i] == result)
				times++;
			else
				times--;
			if (times == 0)
			{
				result = numbers[i];
				times++;
			}
		}
		//3.2候选点判断是否当选
		times = 0;
		for (auto &s : numbers)
			if (s == result)
				times++;
		if (times * 2 > numbers.size())
			return result;
		return 0;
	}
};

// ====================测试代码====================
static void Test(char* testName, vector<int>& a, int length, int expectedValue, bool expectedFlag)
{
	if (testName != nullptr)
		printf("%s begins: \n", testName);

	Solution s;
	printf("Test for solution1: ");
	int result = s.MoreThanHalfNum_Solution3(a);
	if (result == expectedValue)
		printf("Passed.\n");
	else
		printf("Failed.\n");
}

// 存在出现次数超过数组长度一半的数字
static void Test1()
{
	vector<int> a = { 1, 2, 3, 2, 2, 2, 5, 4, 2 };
	Test("Test1", a, a.size(), 2, false);
}

// 不存在出现次数超过数组长度一半的数字
static void Test2()
{
	vector<int> a = { 1, 2, 3, 2, 4, 2, 5, 2, 3 };
	Test("Test2", a, a.size(), 0, true);
}

// 出现次数超过数组长度一半的数字都出现在数组的前半部分
static void Test3()
{
	vector<int> a = { 2, 2, 2, 2, 2, 1, 3, 4, 5 };
	Test("Test3", a, a.size(), 2, false);
}

// 出现次数超过数组长度一半的数字都出现在数组的后半部分
static void Test4()
{
	vector<int> a = { 1, 3, 4, 5, 2, 2, 2, 2, 2 };
	Test("Test4", a, a.size(), 2, false);
}

// 输入空指针
static void Test5()
{
	vector<int> a = { 1 };
	Test("Test5", a, a.size(), 1, false);
}

// 输入空指针
static void Test6()
{
	vector<int> a;
	Test("Test6", a, 0, 0, true);
}

int main_offer39(int argc, char* argv[])
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	Test6();

	return 0;
}