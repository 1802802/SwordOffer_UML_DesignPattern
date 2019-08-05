// 面试题56.1：数组中只出现一次的两个数字
// 题目：一个整型数组里除了两个数字之外，其他的数字都出现了两次。请写程序
// 找出这两个只出现一次的数字。要求时间复杂度是O(n)，空间复杂度是O(1)。

#include <map>
#include <unordered_map>
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
	//基本思路：异或分组操作，当有多个不同数字时，则不断地在组中根据位数分组，直到所有组的异或值都为0
	//运行时间：4ms，占用内存：480k
	static void FindNumsAppearOnce(vector<int> data, int* num1, int *num2) 
	{
		int firstResult = 0;
		for (auto &s : data)
			firstResult ^= s;
		//异或出来的firstResult必然不为0，其为那两个单独数字的异或结果，对其进行分组：
		int n = 0;
		while (firstResult)
		{
			if (firstResult & 0x1 == 1)
				break;
			else
			{
				firstResult >>= 1;
				n++;
			}
		}
		//注意num1和num2的初始化
		*num1 = *num2 = 0;
		for (auto &s : data)
		{
			if (((s >> n) & (0x1)) == 1)
				(*num1) ^= s;
			else
				(*num2) ^= s;
		}
	}
};

// ====================测试代码====================
static void Test(const char* testName, vector<int> data, int length, int expected1, int expected2)
{
	if (testName != nullptr)
		printf("%s begins: ", testName);

	Solution s;
	int result1, result2;
	s.FindNumsAppearOnce(data, &result1, &result2);

	if ((expected1 == result1 && expected2 == result2) ||
		(expected2 == result1 && expected1 == result2))
		printf("Passed.\n\n");
	else
		printf("Failed.\n\n");
}

static void Test1()
{
	vector<int> data = { 2, 4, 3, 6, 3, 2, 5, 5 };
	Test("Test1", data, sizeof(data) / sizeof(int), 4, 6);
}

static void Test2()
{
	vector<int> data = { 4, 6 };
	Test("Test2", data, sizeof(data) / sizeof(int), 4, 6);
}

static void Test3()
{
	vector<int> data = { 4, 6, 1, 1, 1, 1 };
	Test("Test3", data, sizeof(data) / sizeof(int), 4, 6);
}

int main_offer56_1(int argc, char* argv[])
{
	Test1();
	Test2();
	Test3();

	return 0;
}