// 面试题53.3—数组中数值和下标相等的元素
// 题目：假设一个单调递增的数组里的每个元素都是整数并且是唯一的。请编程实
// 现一个函数找出数组中任意一个数值等于其下标的元素。
// 例如，在数组{-3, -1, 1, 3, 5}中，数字3和它的下标相等。

#include <map>
#include <unordered_map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
#include "List.h"
using namespace std;

//思路：设j为下标，i为下标j对应的值，i+j>j+j时，相等位置位于mi的左区间，i+j<j+j时，相等位置位于mi的右区间

int GetNumberSameAsIndex(const int* numbers, int length)
{
	if (numbers == nullptr || length <= 0)
		return -1;
	int lo = 0;
	int hi = length;
	while (lo < hi)
	{
		int mi = (lo + hi) >> 1;
		//i+j > j+j，相等位置位于mi的左区间
		if (numbers[mi] + mi > mi + mi)
			hi = mi;
		//i+j < j+j，相等位置位于mi的右区间
		else if (numbers[mi] + mi < mi + mi)
			lo = mi + 1;
		//相等则命中（如果要找第一个相等位置，则这里将数据存入，并进入mi的左区间继续找）
		else if (numbers[mi] + mi == mi + mi)
			return mi;
	}
	return -1;
}

// ====================测试代码====================
static void Test(const char* testName, int numbers[], int length, int expected)
{
	if (GetNumberSameAsIndex(numbers, length) == expected)
		printf("%s passed.\n", testName);
	else
		printf("%s FAILED.\n", testName);
}

static void Test1()
{
	int numbers[] = { -3, -1, 1, 3, 5 };
	int expected = 3;
	Test("Test1", numbers, sizeof(numbers) / sizeof(int), expected);
}

static void Test2()
{
	int numbers[] = { 0, 1, 3, 5, 6 };
	int expected = 1;
	Test("Test2", numbers, sizeof(numbers) / sizeof(int), expected);
}

static void Test3()
{
	int numbers[] = { -1, 0, 1, 2, 4 };
	int expected = 4;
	Test("Test3", numbers, sizeof(numbers) / sizeof(int), expected);
}

static void Test4()
{
	int numbers[] = { -1, 0, 1, 2, 5 };
	int expected = -1;
	Test("Test4", numbers, sizeof(numbers) / sizeof(int), expected);
}

static void Test5()
{
	int numbers[] = { 0 };
	int expected = 0;
	Test("Test5", numbers, sizeof(numbers) / sizeof(int), expected);
}

static void Test6()
{
	int numbers[] = { 10 };
	int expected = -1;
	Test("Test6", numbers, sizeof(numbers) / sizeof(int), expected);
}

static void Test7()
{
	Test("Test7", nullptr, 0, -1);
}

int main_offer53_3(int argc, char* argv[])
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	Test6();
	Test7();

	return 0;
}