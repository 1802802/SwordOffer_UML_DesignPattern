// 面试题58.2：左旋转字符串
// 题目：字符串的左旋转操作是把字符串前面的若干个字符转移到字符串的尾部。
// 请定义一个函数实现字符串左旋转操作的功能。比如输入字符串"abcdefg"和数
// 字2，该函数将返回左旋转2位得到的结果"cdefgab"。

#include <map>
#include <unordered_map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
#include "BinaryTree.h"
using namespace std;

//左旋的特点在于，先旋转局部（前n位后后n-1位），再整体旋转
//运行时间：3ms，占用内存：476k
class Solution 
{
public:
	string LeftRotateString(string& str, int n) 
	{
		//边界条件的施加
		if (str.size() <= 0 || str.size() < n)
			return string();

		Reverse(str, 0, n - 1);
		Reverse(str, n, str.size() - 1);
		Reverse(str, 0, str.size() - 1);
		return str;
	}

	static void Reverse(string& str, int i, int j)
	{
		while (i < j)
		{
			swap(str[i], str[j]);
			i++; j--;
		}
	}
};

// ====================测试代码====================
static void Test(const char* testName, string input, int num ,string expectedResult)
{
	if (testName != nullptr)
		printf("%s begins: ", testName);

	Solution s;
	cout << s.LeftRotateString(input, num) << endl;

	if ((input.empty() && expectedResult.empty())
		|| (!input.empty() && input == expectedResult))
		printf("Passed.\n\n");
	else
		printf("Failed.\n\n");
}

// 功能测试
static void Test1()
{
	string input = "abcdefg";
	string expected = "cdefgab";

	Test("Test1", input, 2, expected);
}

// 边界值测试
static void Test2()
{
	string input = "abcdefg";
	string expected = "bcdefga";

	Test("Test2", input, 1, expected);
}

// 边界值测试
static void Test3()
{
	string input = "abcdefg";
	string expected = "gabcdef";

	Test("Test3", input, 6, expected);
}

// 鲁棒性测试
static void Test4()
{
	Test("Test4", string(), 6, string());
}

// 鲁棒性测试
static void Test5()
{
	string input = "abcdefg";
	string expected = "abcdefg";

	Test("Test5", input, 0, expected);
}

// 鲁棒性测试
static void Test6()
{
	string input = "abcdefg";
	string expected = "abcdefg";

	Test("Test6", input, 7, expected);
}

int main_offer58_2(int argc, char* argv[])
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	Test6();

	return 0;
}