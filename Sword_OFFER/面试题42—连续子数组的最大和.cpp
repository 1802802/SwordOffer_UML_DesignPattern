// 面试题42—连续子数组的最大和
// 题目：HZ偶尔会拿些专业问题来忽悠那些非计算机专业的同学。
// 今天测试组开完会后,他又发话了:在古老的一维模式识别中,常常需要计算连续子向量的最大和,当向量全为正数的时候,问题很好解决。
// 但是,如果向量中包含负数,是否应该包含某个负数,并期望旁边的正数会弥补它呢？
// 例如:{6,-3,-2,7,-15,1,2,2},连续子向量的最大和为8(从第0个开始,到第3个为止)。
// 给一个数组，返回它的最大连续子序列的和，你会不会被他忽悠住？(子向量的长度至少是1)

// 题目描述：输入一个整型数组，数组里有正数也有负数。数组中一个或连续的多个整
// 数组成一个子数组。求所有子数组的和的最大值。要求时间复杂度为O(n)。

#include <queue>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

class Solution 
{
public:
	//1.动态规划思路，DP[i] = max(DP[i-1]+a[i],a[i])，save中存储了每步的最佳；运行时间：4ms，占用内存：468k
	int FindGreatestSumOfSubArray(vector<int> array) 
	{
		if (array.size() < 1)
			return 0;
		if (array.size() == 1)
			return array[0];
		vector<int> save;
		int maxSum = INT_MIN;
		save.push_back(array[0]);
		for (int i = 1; i < (int)array.size(); i++)
		{
			int sum = max(save[i - 1] + array[i], array[i]);
			save.push_back(sum);
			maxSum = max(sum, maxSum);
		}
		return maxSum;
	}
};

// ====================测试代码====================
static void Test(char* testName, vector<int> pData, int nLength, int expected, bool expectedFlag)
{
	if (testName != nullptr)
		printf("%s begins: \n", testName);
	Solution s;
	int result = s.FindGreatestSumOfSubArray(pData);
	if (result == expected)
		printf("Passed.\n");
	else
		printf("Failed.\n");
}

// 1, -2, 3, 10, -4, 7, 2, -5
static void Test1()
{
	vector<int> data = { 1, -2, 3, 10, -4, 7, 2, -5 };
	Test("Test1", data, sizeof(data) / sizeof(int), 18, false);
}

// 所有数字都是负数
// -2, -8, -1, -5, -9
static void Test2()
{
	vector<int> data = { -2, -8, -1, -5, -9 };
	Test("Test2", data, sizeof(data) / sizeof(int), -1, false);
}

// 所有数字都是正数
// 2, 8, 1, 5, 9
static void Test3()
{
	vector<int> data = { 2, 8, 1, 5, 9 };
	Test("Test3", data, sizeof(data) / sizeof(int), 25, false);
}

// 无效输入
static void Test4()
{
	Test("Test4", vector<int>(), 0, 0, true);
}

int main_offer42(int argc, char* argv[])
{
	Test1();
	Test2();
	Test3();
	Test4();

	return 0;
}