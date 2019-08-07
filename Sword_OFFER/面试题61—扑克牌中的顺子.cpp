// 面试题61：扑克牌的顺子
// 题目：从扑克牌中随机抽5张牌，判断是不是一个顺子，即这5张牌是不是连续的。
// 2～10为数字本身，A为1，J为11，Q为12，K为13，而大、小王可以看成任意数字。
// （五张牌，其中大小鬼为癞子，牌面为 0。判断这五张牌是否能组成顺子）

#include <map>
#include <deque>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <list>
#include "BinaryTree.h"
using namespace std;

//思路：首先确定癞子数量，然后确定癞子能否补齐空缺（排序后计算前后差值即可）
//思路2：排序的方式除了sort函数，还可以使用哈希表来实现
class Solution 
{
public:
	//运行时间：3ms，占用内存：468k
	bool IsContinuous(vector<int> numbers) 
	{
		//1.边界条件
		if (numbers.size() < 5)
			return false;
		//2.计算癞子数量
		int zeroNum = 0;
		int gapNum = 0;
		for (auto &s : numbers)
			if (s == 0)
				zeroNum++;
		//3.排序数组，然后计算前后空缺总和
		sort(numbers.begin(), numbers.end());
		//注意small和big的初值从第一个非0数字位开始
		int small = zeroNum;
		int big = small + 1;
		while (small < numbers.size() && big < numbers.size())
		{
			if (numbers[small] == numbers[big])
				return false;
			//因为已经排过序了，直接减过去就行
			gapNum += numbers[big++] - numbers[small++] - 1;
			//（使用hash表排序的话，需要进行前后指针的big赋值，与small = big操作）
		}
		return (gapNum <= zeroNum) ? true : false;
	}

	//运行时间：5ms，占用内存：480k
	bool IsContinuous2(vector<int> numbers)
	{
		//1.边界条件
		if (numbers.size() < 5)
			return false;
		//2.计算癞子数量
		int totalNum[14] = { 0 };
		for (auto &s : numbers)
			totalNum[s]++;
		int zeroNum = totalNum[0];
		int gapNum = 0;
		int small = 1;
		int big = 1;
		while (small < 14 && big < 14)
		{
			for (int i = big; i < 14; i++)
			{
				if (totalNum[i] == 1)
				{
					//hash表的计算，big和small前后移动双指针
					if (small == i)
						continue;
					big = i;
					break;
				}
				else if (totalNum[i] > 1)
					return false;
			}
			gapNum += big - small - 1;
			small = big;
			big++;
			//（使用hash表排序的话，需要进行前后指针的big赋值，与small = big操作）
		}
		return (gapNum <= zeroNum) ? true : false;
	}
};

// ====================测试代码====================
static void Test(const char* testName, vector<int> numbers, int length, bool expected)
{
	if (testName != nullptr)
		printf("%s begins: ", testName);

	Solution s;
	if (s.IsContinuous2(numbers) == expected)
		printf("Passed.\n");
	else
		printf("Failed.\n");
}

static void Test1()
{
	vector<int> numbers = { 1, 3, 2, 5, 4 };
	Test("Test1", numbers, sizeof(numbers) / sizeof(int), true);
}

static void Test2()
{
	vector<int> numbers = { 1, 3, 2, 6, 4 };
	Test("Test2", numbers, sizeof(numbers) / sizeof(int), false);
}

static void Test3()
{
	vector<int> numbers = { 0, 3, 2, 6, 4 };
	Test("Test3", numbers, sizeof(numbers) / sizeof(int), true);
}

static void Test4()
{
	vector<int> numbers = { 0, 3, 1, 6, 4 };
	Test("Test4", numbers, sizeof(numbers) / sizeof(int), false);
}

static void Test5()
{
	vector<int> numbers = { 1, 3, 0, 5, 0 };
	Test("Test5", numbers, sizeof(numbers) / sizeof(int), true);
}

static void Test6()
{
	vector<int> numbers = { 1, 3, 0, 7, 0 };
	Test("Test6", numbers, sizeof(numbers) / sizeof(int), false);
}

static void Test7()
{
	vector<int> numbers = { 1, 0, 0, 5, 0 };
	Test("Test7", numbers, sizeof(numbers) / sizeof(int), true);
}

static void Test8()
{
	vector<int> numbers = { 1, 0, 0, 7, 0 };
	Test("Test8", numbers, sizeof(numbers) / sizeof(int), false);
}

static void Test9()
{
	vector<int> numbers = { 3, 0, 0, 0, 0 };
	Test("Test9", numbers, sizeof(numbers) / sizeof(int), true);
}

static void Test10()
{
	vector<int> numbers = { 0, 0, 0, 0, 0 };
	Test("Test10", numbers, sizeof(numbers) / sizeof(int), true);
}

// 有对子
static void Test11()
{
	vector<int> numbers = { 1, 0, 0, 1, 0 };
	Test("Test11", numbers, sizeof(numbers) / sizeof(int), false);
}

// 鲁棒性测试
static void Test12()
{
	Test("Test12", vector<int>(), 0, false);
}

int main_offer61(int argc, char* argv[])
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
	Test12();

	return 0;
}
