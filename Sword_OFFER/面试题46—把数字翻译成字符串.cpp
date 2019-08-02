// 面试题46—把数字翻译成字符串
// 题目：给定一个数字，我们按照如下规则把它翻译为字符串：0翻译成"a"，1翻
// 译成"b"，……，11翻译成"l"，……，25翻译成"z"。一个数字可能有多个翻译。例
// 如12258有5种不同的翻译，它们分别是"bccfi"、"bwfi"、"bczi"、"mcfi"和
// "mzi"。请编程实现一个函数用来计算一个数字有多少种不同的翻译方法。

#include <queue>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

//1.思路，使用动态规划实现：f(i) = f(i+1) + g(i,i+1)*f(i+2)，g(i,i+1)表示i与i+1组成的数字属于[10,25]
//在解题时需要注意dp数据的位置与save中数据的存储位置，save中为125之类的顺序，计算时需要反过来，而dp跟着从大到小进行计算
int GetTranslationCount1(int number)
{
	if (number < 0)
		return 0;
	if (number < 10)
		return 1;
	string save = to_string(number);
	vector<int> dp(save.size(), 0);
	dp[save.size() - 1] = 1;
	int sum = ((save[save.size() - 2] - '0') * 10 + (save[save.size() - 1] - '0'));
	if (sum <= 25 && sum >= 10)
		dp[save.size() - 2] = 2;
	else
		dp[save.size() - 2] = 1;
	for (int i = save.size() - 3; i >= 0; i--)
	{
		sum = ((save[i] - '0') * 10 + (save[i + 1] - '0'));
		if (sum <= 25 && sum >= 10)
			dp[i] = dp[i + 1] + dp[i + 2];
		else
			dp[i] = dp[i + 1];
	}
	return dp[0];
}

//优化改进后的版本，给dp多一位存储，减少代码量
int GetTranslationCount2(int number)
{
	if (number < 0)
		return 0;
	string save = to_string(number);
	vector<int> dp(save.size() + 1, 0);
	int size = save.size();
	dp[size] = 1;
	dp[size - 1] = 1;
	for (int i = size - 2; i >= 0; i--)
	{
		int sum = ((save[i] - '0') * 10 + (save[i + 1] - '0'));
		if (sum <= 25 && sum >= 10)
			dp[i] = dp[i + 1] + dp[i + 2];
		else
			dp[i] = dp[i + 1];
	}
	return dp[0];
}

// ====================测试代码====================
static void Test(const string& testName, int number, int expected)
{
	if (GetTranslationCount2(number) == expected)
		cout << testName << " passed." << endl;
	else
		cout << testName << " FAILED." << endl;
}

static void Test1()
{
	int number = 0;
	int expected = 1;
	Test("Test1", number, expected);
}

static void Test2()
{
	int number = 10;
	int expected = 2;
	Test("Test2", number, expected);
}

static void Test3()
{
	int number = 125;
	int expected = 3;
	Test("Test3", number, expected);
}

static void Test4()
{
	int number = 126;
	int expected = 2;
	Test("Test4", number, expected);
}

static void Test5()
{
	int number = 426;
	int expected = 1;
	Test("Test5", number, expected);
}

static void Test6()
{
	int number = 100;
	int expected = 2;
	Test("Test6", number, expected);
}

static void Test7()
{
	int number = 101;
	int expected = 2;
	Test("Test7", number, expected);
}

static void Test8()
{
	int number = 12258;
	int expected = 5;
	Test("Test8", number, expected);
}

static void Test9()
{
	int number = -100;
	int expected = 0;
	Test("Test9", number, expected);
}

int main_offer46(int argc, char* argv[])
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