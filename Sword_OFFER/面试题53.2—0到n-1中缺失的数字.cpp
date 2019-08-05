// 面试题53.2—0到n-1中缺失的数字
// 题目：一个长度为n-1的递增排序数组中的所有数字都是唯一的，并且每个数字
// 都在范围0到n-1之内。在范围0到n-1的n个数字中有且只有一个数字不在该数组
// 中，请找出这个数字。

#include <map>
#include <unordered_map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
#include "List.h"
using namespace std;

//思路，下标和数字的对比，判断下标位置的数字和下标的大小比较，二分查找
int GetMissingNumber(const int* numbers, int length)
{
	if (numbers == nullptr || length <= 0)
		return -1;
	int lo = 0;
	int hi = length;
	while (lo < hi)
	{
		int mi = (lo + hi) >> 1;
		//说明缺失在mi的左边区间
		if (numbers[mi] > mi)
			hi = mi;
		//说明缺失在mi的右边区间
		else if (numbers[mi] == mi)
			lo = mi + 1;
	}
	//最后lo和hi会落入到所缺失的那个序号上
	if (lo == hi)
		return lo;
	else
		return -1;
}

// ====================测试代码====================
static void Test(const char* testName, int numbers[], int length, int expected)
{
	if (testName != nullptr)
		printf("%s begins: ", testName);

	int result = GetMissingNumber(numbers, length);
	if (result == expected)
		printf("Passed.\n");
	else
		printf("Failed.\n");
}

// 缺失的是第一个数字0
static void Test1()
{
	int numbers[] = { 1, 2, 3, 4, 5 };
	int expected = 0;
	Test("Test1", numbers, sizeof(numbers) / sizeof(int), expected);
}

// 缺失的是最后一个数字
static void Test2()
{
	int numbers[] = { 0, 1, 2, 3, 4 };
	int expected = 5;
	Test("Test2", numbers, sizeof(numbers) / sizeof(int), expected);
}

// 缺失的是中间某个数字0
static void Test3()
{
	int numbers[] = { 0, 1, 2, 4, 5 };
	int expected = 3;
	Test("Test3", numbers, sizeof(numbers) / sizeof(int), expected);
}

// 数组中只有一个数字，缺失的是第一个数字0
static void Test4()
{
	int numbers[] = { 1 };
	int expected = 0;
	Test("Test4", numbers, sizeof(numbers) / sizeof(int), expected);
}

// 数组中只有一个数字，缺失的是最后一个数字1
static void Test5()
{
	int numbers[] = { 0 };
	int expected = 1;
	Test("Test5", numbers, sizeof(numbers) / sizeof(int), expected);
}

// 空数组
static void Test6()
{
	int expected = -1;
	Test("Test6", nullptr, 0, expected);
}

int main_offer53_2(int argc, char* argv[])
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	Test6();

	return 0;
}