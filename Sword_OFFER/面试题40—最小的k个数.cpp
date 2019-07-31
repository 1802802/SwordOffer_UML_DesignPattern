// 面试题40—最小的k个数
// 题目：输入n个整数，找出其中最小的K个数。例如输入4,5,1,6,2,7,3,8这8个数字，则最小的4个数字是1,2,3,4,。

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
using namespace std;


class Solution 
{
public:
	//1.排序后输出，O(nlogn)，运行时间：3ms，占用内存：480k
	vector<int> GetLeastNumbers_Solution(vector<int> input, int k) 
	{
		if (input.size() < 1)
			return vector<int>();
		sort(input.begin(), input.end());
		vector<int> tmp;
		if (k > input.size())
		{
			for (int i = 0; i < input.size(); i++)
				tmp.push_back(input[i]);
		}
		else
		{
			for (int i = 0; i < k; i++)
				tmp.push_back(input[i]);
		}
		return tmp;
	}

	//2.允许修改数据，轴点快速划分算法，时间O（n）
	vector<int> GetLeastNumbers_Solution2(vector<int> input, int k)
	{
		if (input.size() < 1)
			return vector<int>();
		int start = 0; int end = input.size() - 1;
		//找轴点
		int index = Partition(input, start, end);
		while (index != k - 1)
		{
			if (index > k - 1)
			{
				end = index - 1;
				index = 
			}
		}
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
};

// ====================测试代码====================
static void Test(char* testName, int* data, int n, int* expectedResult, int k)
{
	if (testName != nullptr)
		printf("%s begins: \n", testName);

	vector<int> vectorData;
	for (int i = 0; i < n; ++i)
		vectorData.push_back(data[i]);

	if (expectedResult == nullptr)
		printf("The input is invalid, we don't expect any result.\n");
	else
	{
		printf("Expected result: \n");
		for (int i = 0; i < k; ++i)
			printf("%d\t", expectedResult[i]);
		printf("\n");
	}

	printf("Result for solution1:\n");
	Solution s;
	vector<int> a = s.GetLeastNumbers_Solution(vectorData, k);
	if (expectedResult != nullptr)
	{
		for (int i = 0; i < k; ++i)
			printf("%d\t", a[i]);
		printf("\n");
	}
}

// k小于数组的长度
static void Test1()
{
	int data[] = { 4, 5, 1, 6, 2, 7, 3, 8 };
	int expected[] = { 1, 2, 3, 4 };
	Test("Test1", data, sizeof(data) / sizeof(int), expected, sizeof(expected) / sizeof(int));
}

// k等于数组的长度
static void Test2()
{
	int data[] = { 4, 5, 1, 6, 2, 7, 3, 8 };
	int expected[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
	Test("Test2", data, sizeof(data) / sizeof(int), expected, sizeof(expected) / sizeof(int));
}

// k大于数组的长度
static void Test3()
{
	int data[] = { 4, 5, 1, 6, 2, 7, 3, 8 };
	int* expected = nullptr;
	Test("Test3", data, sizeof(data) / sizeof(int), expected, 10);
}

// k等于1
static void Test4()
{
	int data[] = { 4, 5, 1, 6, 2, 7, 3, 8 };
	int expected[] = { 1 };
	Test("Test4", data, sizeof(data) / sizeof(int), expected, sizeof(expected) / sizeof(int));
}

// k等于0
static void Test5()
{
	int data[] = { 4, 5, 1, 6, 2, 7, 3, 8 };
	int* expected = nullptr;
	Test("Test5", data, sizeof(data) / sizeof(int), expected, 0);
}

// 数组中有相同的数字
static void Test6()
{
	int data[] = { 4, 5, 1, 6, 2, 7, 2, 8 };
	int expected[] = { 1, 2 };
	Test("Test6", data, sizeof(data) / sizeof(int), expected, sizeof(expected) / sizeof(int));
}

// 输入空指针
static void Test7()
{
	int* expected = nullptr;
	Test("Test7", nullptr, 0, expected, 0);
}

int main(int argc, char* argv[])
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	Test6();
	//Test7();

	return 0;
}