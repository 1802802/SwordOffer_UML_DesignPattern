// 面试题58.1：翻转单词顺序
// 题目：输入一个英文句子，翻转句子中单词的顺序，但单词内字符的顺序不变。
// 为简单起见，标点符号和普通字母一样处理。例如输入字符串"I am a student. "，
// 则输出"student. a am I"。

#include <map>
#include <unordered_map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
#include "BinaryTree.h"
using namespace std;

//思路：对于字符串的翻转，无非是两种方式：先整体翻转，再局部翻转；先局部翻转，再整体翻转
//运行时间：3ms，占用内存：476k
class Solution 
{
public:
	string ReverseSentence1(string &str)
	{
		for (int i = 0, j = 0; i < str.size();)
		{
			for (; j < str.size(); j++)
			{
				if (str[j] == ' ')
					break;
			}
			rotate(str, i, j - 1);
			i = ++j;
		}
		rotate(str, 0, str.size() - 1);
		return str;
	}

	void rotate(string &str, int lo, int hi)
	{
		while (lo < hi)
			swap(str[lo++], str[hi--]);
	}

	string ReverseSentence(string& str) 
	{
		if (str.size() <= 0)
			return str;
		//1.先整体翻转
		Reverse(str, 0, str.size());
		//2.再根据空格定位，进行每个单词的局部翻转
		for (int i = 0, j = 0; i < str.size();)
		{
			//2.1找到下个空格的位置，直到找到或者到头
			for (; j < str.size(); j++)
			{
				if (str[j] == ' ')
					break;
			}
			//2.2局部翻转
			Reverse(str, i, j);
			i = ++j;
		}
		return str;
	}

	//思路2：先局部翻转，再整体翻转，效果一样
	string ReverseSentence2(string& str)
	{
		if (str.size() <= 0)
			return str;
		//1.根据空格定位，进行每个单词的局部翻转
		for (int i = 0, j = 0; i < str.size();)
		{
			//2.1找到下个空格的位置，直到找到或者到头
			for (; j < str.size(); j++)
			{
				if (str[j] == ' ')
					break;
			}
			//2.2局部翻转
			Reverse(str, i, j);
			i = ++j;
		}
		//2.再整体翻转
		Reverse(str, 0, str.size());
		return str;
	}

	void Reverse(string& str, int i ,int j)
	{
		while (i < j)
		{
			swap(str[i], str[j - 1]);
			i++; j--;
		}
	}
};

// ====================测试代码====================
static void Test(const char* testName, string input, string expectedResult)
{
	if (testName != nullptr)
		printf("%s begins: \n", testName);

	Solution s;
	cout << s.ReverseSentence1(input) << endl;
	cout << expectedResult << endl;

	if ((input.empty() && expectedResult.empty())
		|| (!input.empty() && input == expectedResult))
		printf("Passed.\n\n");
	else
		printf("Failed.\n\n");
}

// 功能测试，句子中有多个单词
static void Test1()
{
	string input = "   I am  a student.";
	string expected = "student. a  am I   ";

	Test("Test1", input, expected);
}

// 功能测试，句子中只有一个单词
static void Test2()
{
	string input = "Wonderful";
	string expected = "Wonderful";

	Test("Test2", input, expected);
}

// 鲁棒性测试
static void Test3()
{
	Test("Test3", string(), string());
}

// 边界值测试，测试空字符串
static void Test4()
{
	Test("Test4", "", "");
}

// 边界值测试，字符串中只有空格
static void Test5()
{
	string input = "   ";
	string expected = "   ";
	Test("Test5", input, expected);
}

int main_offer58_1(int argc, char* argv[])
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();

	return 0;
}