// 面试题48—最长不含重复字符的子字符串
// 题目：请从字符串中找出一个最长的不包含重复字符的子字符串，计算该最长子
// 字符串的长度。假设字符串中只包含从'a'到'z'的字符。

#include <queue>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

//1.暴力贪心算法，计算每个字符位置的最佳长度，并存储当前的最大长度直到结束
//有问题，因为有时候最长的长度的起始位置是在初始位置是在两个相同的数中间的数
//解决上述的问题，需要采用截断的方式（即当出现相同时判断相同的位置距离，如果大于当前串长度则无视，小于当前串长度则截断）
int longestSubstringWithoutDuplication_1(const string& str)
{
	int Length = 0;
	int maxLength = 0;
	string save;
	for (int i = 0; i < str.size(); i++)
	{
		if (save.find(str[i]) == -1)
		{
			save.push_back(str[i]);
			Length++;
		}
		else
		{
			save.clear();
			save.push_back(str[i]);
			maxLength = max(maxLength, Length);
			Length = 1;
		}
	}
	maxLength = max(maxLength, Length);
	return maxLength;
}

//2.使用动态规划，其中加入截断的判断操作，并用一个26位的数组来存放当前字符的位置（默认均为-1）
//公式如下：
//若当前字符未出现，则f(i)=f(i-1)+1；若当前字符出现，且相距d<=f(i-1)，f(i)=d；若d>=f(i-1)，f(i)=f(i-1)+1
int longestSubstringWithoutDuplication_2(const string& str)
{
	int longestPath = 0;
	//charPlace用于存储对应的字符的出现位置，bestSave存储每个位置的字符的最佳子字符串长度
	vector<int> charPlace(26, -1);
	vector<int> bestSave(str.size() + 1, 0);
	for (int i = 0; i < str.size(); i++)
	{
		int currentChar = str[i] - 'a';
		if (charPlace[currentChar] == -1)
		{
			charPlace[currentChar] = i;
			if (i != 0)
				bestSave[i] = bestSave[i - 1] + 1;
			else
				bestSave[i] = 1;
		}
		else
		{
			int lastPlace = charPlace[currentChar];
			charPlace[currentChar] = i;
			int distance = i - lastPlace; 
			//计算两次重复的间隔，如果间隔在上一位之间（包括开头），截断它，将当前f(i)至为distance
			//如果不是，则将当前f(i)继续递增
			if (distance <= bestSave[i - 1])
				bestSave[i] = distance;
			else
				bestSave[i] = bestSave[i - 1] + 1;
		}
		//每次计算完当前最长子字符串后，记录最大的
		longestPath = max(longestPath, bestSave[i]);
	}
	return longestPath;
}

// ====================测试代码====================
static void testSolution1(const std::string& input, int expected)
{
	int output = longestSubstringWithoutDuplication_1(input);
	if (output == expected)
		std::cout << "Solution 1 passed, with input: " << input << std::endl;
	else
		std::cout << "Solution 1 FAILED, with input: " << input << std::endl;
}

static void testSolution2(const std::string& input, int expected)
{
	int output = longestSubstringWithoutDuplication_2(input);
	if (output == expected)
		std::cout << "Solution 2 passed, with input: " << input << std::endl;
	else
		std::cout << "Solution 2 FAILED, with input: " << input << std::endl;
}

static void test(const std::string& input, int expected)
{
	testSolution1(input, expected);
	testSolution2(input, expected);
}

static void test1()
{
	const std::string input = "abcacfrar";
	int expected = 4;
	test(input, expected);
}

static void test2()
{
	const std::string input = "acfrarabc";
	int expected = 4;
	test(input, expected);
}

static void test3()
{
	const std::string input = "arabcacfr";
	int expected = 4;
	test(input, expected);
}

static void test4()
{
	const std::string input = "aaaa";
	int expected = 1;
	test(input, expected);
}

static void test5()
{
	const std::string input = "abcdefg";
	int expected = 7;
	test(input, expected);
}

static void test6()
{
	const std::string input = "aaabbbccc";
	int expected = 2;
	test(input, expected);
}

static void test7()
{
	const std::string input = "abcdcba";
	int expected = 4;
	test(input, expected);
}

static void test8()
{
	const std::string input = "abcdaef";
	int expected = 6;
	test(input, expected);
}

static void test9()
{
	const std::string input = "a";
	int expected = 1;
	test(input, expected);
}

static void test10()
{
	const std::string input = "";
	int expected = 0;
	test(input, expected);
}

int main_offer48(int argc, char* argv[])
{
	test1();
	test2();
	test3();
	test4();
	test5();
	test6();
	test7();
	test8();
	test9();
	test10();

	return 0;
}