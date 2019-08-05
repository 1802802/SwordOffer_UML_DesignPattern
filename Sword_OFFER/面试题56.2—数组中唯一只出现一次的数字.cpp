// 面试题56.2：数组中唯一只出现一次的数字
// 题目：在一个数组中除了一个数字只出现一次之外，其他数字都出现了三次。请
// 找出那个吃出现一次的数字。

#include <map>
#include <unordered_map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
#include "BinaryTree.h"
using namespace std;


//思路：一个数字出现三次，表示这个数字的每一位加起来都可以被3整除，同样的对于多个三次出现的数字也一样
//根据这里原理，使用32位的数组来存储每一位中的3的余数，每一位的余数即为那个单独数字的位数上的数字

//测试时注意：需要考虑负数
int FindNumberAppearingOnce(int numbers[], int length)
{
	if (numbers == nullptr || length <= 0)
		throw new exception("Invalid input");

	int a[32] = { 0 };
	long long mask = 1;
	int num = 0;
	for (int i = 0; i < 32; i++)
	{
		for (int j = 0; j < length; j++)
		{
			//需要注意一下为负数的情况，所以这里不能直接加，需要处理着加（并且处理必须为!=0）
			if ((numbers[j] & mask) != 0)
				a[i]++;
		}
		mask <<= 1;
		//这里的操作很关键，针对正数负数都可以（将所得数据根据i按位或操作，得到num）
		num |= (a[i] % 3) << i;
	}
	return num;
}

//优化后的简写版，不需要使用辅助数组与辅助数，核心是先计算出进制的位和，然后再将计算的位和%3加入到num当中
int FindNumberAppearingOnce2(int numbers[], int length)
{
	if (numbers == nullptr || length <= 0)
		throw new exception("Invalid input");

	int num = 0;
	for (int i = 0; i < 32; i++)
	{
		int sum = 0;
		for (int j = 0; j < length; j++)
			//这里表示将数组中所有的数都根据i进行右移，将其与1进行&操作，得到该数字位于i位的进制大小
			sum += (numbers[j] >> i) & 0x1;
		//这里表示将所有的数据%3后左移i位进行|操作，用于将当前计算的i位嵌入num当中
		num |= (sum % 3) << i;
	}
	return num;
}

// ====================测试代码====================
static void Test(const char* testName, int numbers[], int length, int expected)
{
	int result = FindNumberAppearingOnce2(numbers, length);
	if (result == expected)
		printf("%s passed.\n", testName);
	else
		printf("%s FAILED.\n", testName);
}

// 所有数字都是正数，唯一的数字是最小的
static void Test1()
{
	int numbers[] = { 1, 1, 2, 2, 2, 1, 3 };
	int expected = 3;
	Test("Test1", numbers, sizeof(numbers) / sizeof(int), expected);
}

// 所有数字都是正数，唯一的数字的大小位于中间
static void Test2()
{
	int numbers[] = { 4, 3, 3, 2, 2, 2, 3 };
	int expected = 4;
	Test("Test2", numbers, sizeof(numbers) / sizeof(int), expected);
}

// 所有数字都是正数，唯一的数字是最大的
static void Test3()
{
	int numbers[] = { 4, 4, 1, 1, 1, 7, 4 };
	int expected = 7;
	Test("Test3", numbers, sizeof(numbers) / sizeof(int), expected);
}

// 唯一的数字是负数
static void Test4()
{
	int numbers[] = { -10, 214, 214, 214 };
	int expected = -10;
	Test("Test4", numbers, sizeof(numbers) / sizeof(int), expected);
}

// 除了唯一的数字，其他数字都是负数
static void Test5()
{
	int numbers[] = { -209, 3467, -209, -209 };
	int expected = 3467;
	Test("Test5", numbers, sizeof(numbers) / sizeof(int), expected);
}

// 重复的数字有正数也有负数
static void Test6()
{
	int numbers[] = { 1024, -1025, 1024, -1025, 1024, -1025, 1023 };
	int expected = 1023;
	Test("Test6", numbers, sizeof(numbers) / sizeof(int), expected);
}

// 所有数字都是负数
static void Test7()
{
	int numbers[] = { -1024, -1024, -1024, -1023 };
	int expected = -1023;
	Test("Test7", numbers, sizeof(numbers) / sizeof(int), expected);
}

// 唯一的数字是0
static void Test8()
{
	int numbers[] = { -23, 0, 214, -23, 214, -23, 214 };
	int expected = 0;
	Test("Test8", numbers, sizeof(numbers) / sizeof(int), expected);
}

// 除了唯一的数字，其他数字都是0
static void Test9()
{
	int numbers[] = { 0, 3467, 0, 0, 0, 0, 0, 0 };
	int expected = 3467;
	Test("Test9", numbers, sizeof(numbers) / sizeof(int), expected);
}

int main_offer56_2(int argc, char* argv[])
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