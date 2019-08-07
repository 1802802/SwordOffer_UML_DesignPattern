// 面试题63：股票的最大利润
// 题目：假设把某股票的价格按照时间先后顺序存储在数组中，请问买卖交易该股
// 票可能获得的利润是多少？例如一只股票在某些时间节点的价格为{9, 11, 8, 5,
// 7, 12, 16, 14}。如果我们能在价格为5的时候买入并在价格为16时卖出，则能
// 收获最大的利润11。

#include <map>
#include <deque>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <list>
#include "BinaryTree.h"
using namespace std;

//股票最大利润问题有五种，需要都好好考虑一下他们的共性

//思路：动态规划，计算每个位置的卖出价最大值（如果将0作为最小值而不考虑负值时
//dp[i] = max( dp[i - 1] + n[i] - n[i - 1], dp[i - 1] )
//当考虑负值时，不好操作

int MaxDiff(const int* numbers, unsigned length)
{
	if (numbers == nullptr && length < 2)
		return 0;

	vector<int> maxArray(length, -99999);
	int maxValue = INT_MIN;
	int minValue = numbers[0];

	for (int i = 1; i < length; i++)
	{
		maxArray[i] = max({ maxArray[i - 1] + numbers[i] - numbers[i - 1], maxArray[i - 1], numbers[i] - minValue });
		maxValue = max(maxValue, maxArray[i]);
		if (numbers[i] < minValue)
			minValue = numbers[i];
	}

	//for (auto &s : maxArray)
	//	cout << s << " ";
	//cout << endl;
	return maxValue;
}

//思路2：记录前面的最小值，不断地计算最大效益（注意不要只考虑正收益的最大值，还要包括负收益的）
int MaxDiff2(const int* numbers, unsigned length)
{
	if (numbers == nullptr && length < 2)
		return 0;

	int minValue = INT_MAX;
	int maxDiff = INT_MIN;

	for (int i = 0; i < length; i++)
	{
		if (numbers[i] < minValue)
		{
			maxDiff = max(maxDiff, numbers[i] - minValue);
			minValue = numbers[i];
		}
		else
			maxDiff = max(maxDiff, numbers[i] - minValue);
	}
	
	return maxDiff;
}

// ==================== Test Code ====================
static void Test(const char* testName, const int* numbers, unsigned int length, int expected)
{
	if (testName != nullptr)
		printf("%s begins: ", testName);

	if (MaxDiff2(numbers, length) == expected)
		printf("Passed.\n");
	else
		printf("FAILED.\n");
}

static void Test1()
{
	int numbers[] = { 4, 1, 3, 2, 5 };
	Test("Test1", numbers, sizeof(numbers) / sizeof(int), 4);
}

// 价格递增
static void Test2()
{
	int numbers[] = { 1, 2, 4, 7, 11, 16 };
	Test("Test2", numbers, sizeof(numbers) / sizeof(int), 15);
}

// 价格递减
static void Test3()
{
	int numbers[] = { 16, 11, 7, 4, 2, 1 };
	Test("Test3", numbers, sizeof(numbers) / sizeof(int), -1);
}

// 价格全部相同
static void Test4()
{
	int numbers[] = { 16, 16, 16, 16, 16 };
	Test("Test4", numbers, sizeof(numbers) / sizeof(int), 0);
}

static void Test5()
{
	int numbers[] = { 9, 11, 5, 7, 16, 1, 4, 2 };
	Test("Test5", numbers, sizeof(numbers) / sizeof(int), 11);
}

static void Test6()
{
	int numbers[] = { 2, 4 };
	Test("Test6", numbers, sizeof(numbers) / sizeof(int), 2);
}

static void Test7()
{
	int numbers[] = { 4, 2 };
	Test("Test7", numbers, sizeof(numbers) / sizeof(int), -2);
}

static void Test8()
{
	Test("Test8", nullptr, 0, 0);
}

int main_offer63(int argc, char* argv[])
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	Test6();
	Test7();
	Test8();

	return 0;
}