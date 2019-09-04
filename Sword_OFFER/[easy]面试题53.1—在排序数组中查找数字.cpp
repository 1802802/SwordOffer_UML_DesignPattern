// 面试题53.1—在排序数组中查找数字
// 题目：统计一个数字在排序数组中出现的次数。

#include <map>
#include <unordered_map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
#include "List.h"
using namespace std;

class Solution 
{
public:
	//方法真的很多种，无论是顺序查找，map存之类的都行，但是如果要实现时间复杂度为O(logn)
	//思路需要定位为使用二分查找找到对应数字的第一个数和最后一个数（或者下一个数的第一个数），然后相减这样子的
	//运行时间：3ms，占用内存：604k
	int GetNumberOfK(vector<int> data, int k) 
	{
		if (data.size() < 1)
			return 0;
		//这是一种很骚的做法，用k+1搜第一个数减去用k搜第一个数，但是BinarySearchFirst需要返回lo而不是-1
		//原因在于返回lo会返回最后失败的位置
		//int i1 = BinarySearchFirst(data, k);
		//int i2 = BinarySearchFirst(data, k + 1);
		//return i2 - i1;

		//下面为正统做法，搜一个数的首和尾
		int i1 = BinarySearchFirst(data, k);
		int i2 = BinarySearchLast(data, k);
		cout << "i2:" << i2 << endl;
		cout << "i1:" << i1 << endl;
		if (i2 == -1 && i1 == -1)
			return 0;
		return i2 - i1 + 1;
		
	}

	int BinarySearchFirst(vector<int>& data, int k)
	{
		int lo = 0; int hi = data.size();
		while (lo < hi)
		{
			int mi = (lo + hi) >> 1;
			if (data[mi] > k)
				hi = mi;
			else if (data[mi] < k)
				lo = mi + 1;
			else
			{
				//此处判断当前k是否为排序序列的第一个k（包括其位置为0的情况），是则返回位置mi，不是则区间左移
				//成功则返回k的第一个数字index，失败则返回k在数组中下一位值的第一个数字index，当当前数字为最后一位时
				//则返回的是hi的最大值，即data的size()位，可理解为迭代器的.end()位置
				if ((mi > 0 && data[mi - 1] != k) || mi == 0)
					return mi;
				else
					hi = mi;
			}
		}
		return -1;
	}

	int BinarySearchLast(vector<int>& data, int k)
	{
		int lo = 0; int hi = data.size();
		while (lo < hi)
		{
			int mi = (lo + hi) >> 1;
			if (data[mi] > k)
				hi = mi;
			else if (data[mi] < k)
				lo = mi + 1;
			else
			{
				//此处判断当前k是否为排序序列的最后一个k（包括其位置为hi - 1的情况），是则返回位置mi，不是则区间右移
				if ((mi < hi - 1 && data[mi + 1] != k) || mi == hi - 1)
					return mi;
				else
					lo = mi + 1;
			}
		}
		return -1;
	}
};

// ====================测试代码====================
static void Test(const char* testName, vector<int> data, int length, int k, int expected)
{
	if (testName != nullptr)
		printf("%s begins: ", testName);
	Solution s;
	int result = s.GetNumberOfK(data, k);
	if (result == expected)
		printf("Passed.\n");
	else
		printf("Failed.\n");
}

// 查找的数字出现在数组的中间
static void Test1()
{
	vector<int> data = { 1, 2, 3, 3, 3, 3, 4, 5 };
	Test("Test1", data, sizeof(data) / sizeof(int), 3, 4);
}

// 查找的数组出现在数组的开头
static void Test2()
{
	vector<int> data = { 3, 3, 3, 3, 4, 5 };
	Test("Test2", data, sizeof(data) / sizeof(int), 3, 4);
}

// 查找的数组出现在数组的结尾
static void Test3()
{
	vector<int> data = { 1, 2, 3, 3, 3, 3 };
	Test("Test3", data, sizeof(data) / sizeof(int), 3, 4);
}

// 查找的数字不存在
static void Test4()
{
	vector<int> data = { 1, 3, 3, 3, 3, 4, 5 };
	Test("Test4", data, sizeof(data) / sizeof(int), 2, 0);
}

// 查找的数字比第一个数字还小，不存在
static void Test5()
{
	vector<int> data = { 1, 3, 3, 3, 3, 4, 5 };
	Test("Test5", data, sizeof(data) / sizeof(int), 0, 0);
}

// 查找的数字比最后一个数字还大，不存在
static void Test6()
{
	vector<int> data = { 1, 3, 3, 3, 3, 4, 5 };
	Test("Test6", data, sizeof(data) / sizeof(int), 6, 0);
}

// 数组中的数字从头到尾都是查找的数字
static void Test7()
{
	vector<int> data = { 3, 3, 3, 3 };
	Test("Test7", data, sizeof(data) / sizeof(int), 3, 4);
}

// 数组中的数字从头到尾只有一个重复的数字，不是查找的数字
static void Test8()
{
	vector<int> data = { 3, 3, 3, 3 };
	Test("Test8", data, sizeof(data) / sizeof(int), 4, 0);
}

// 数组中只有一个数字，是查找的数字
static void Test9()
{
	vector<int> data = { 3 };
	Test("Test9", data, sizeof(data) / sizeof(int), 3, 1);
}

// 数组中只有一个数字，不是查找的数字
static void Test10()
{
	vector<int> data = { 3 };
	Test("Test10", data, sizeof(data) / sizeof(int), 4, 0);
}

// 鲁棒性测试，数组空指针
static void Test11()
{
	Test("Test11", vector<int>(), 0, 0, 0);
}

int main_offer53(int argc, char* argv[])
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
	Test10();
	Test11();

	return 0;
}