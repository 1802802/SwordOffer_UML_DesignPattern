// 面试题19—正则表达式匹配
// 题目：请实现一个函数用来匹配包括'.'和'*'的正则表达式。模式中的字符'.'表示任意一个字符，
// 而'*'表示它前面的字符可以出现任意次（包含0次）。 在本题中，匹配是指字符串的所有字符匹配整个模式。
// 例如，字符串"aaa"与模式"a.a"和"ab*ac*a"匹配，但是与"aa.a"和"ab*a"均不匹配

#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
	//for循环的递归实现方式，是通过多次传入数据实现多个根节点的类似扩张；不断自身调用的方式是只有一个根节点往下扩张

	//本题的思路主要是针对此题的状态来划分的，大概来说是5种状态，更细致地来说是8种状态（将1.1细分的话）
	//以后相关的问题都可以变成类似的多路递归问题，而递归问题往往通过多叉树来分析过程。运行时间：3ms，占用内存：472k
	
	/*重新整理一下思路，采用对不同匹配状态的划分来实现（通过绘制多叉树即可，采用递归减小比对串的方法）
	1.判断当前位置的下一位是否为'*’，是则进入状态1；
		进入状态1后，当前位置两两是否匹配，是则进入状态1.1，否则就进入状态1.2；
	1.1状态1.1：最复杂的状态，此时下一位为'*'且两两匹配，有三种情况：(ab*c,abc),(ab*c,abbbc),(ab*bc,abc)
		所以状态1.1对应三种移动数据指针的方式：matchCore(str + 1, pattern + 2) || matchCore(str + 1, pattern) || matchCore(str, pattern + 2);
	1.2状态1.2：此时当前位置的下一位是否为'*’，且两两不匹配，有且对应情况：(af*c,abc/ac)，所以其操作为matchCore(str, pattern + 2)；
	2.当前位置的下一位不为'*'，判断当前位置两两是否匹配，是则进入状态2；
		状态2的操作很简单，就是两两成功匹配且下位不为'*'，char和pat都前移一位即可
	3.当前位置的下一位不为'*’，同时当前位置两两不匹配，则进入状态3（直接返回false）。
	*/

	bool match(char* str, char* pattern)
	{
		if (str == nullptr || pattern == nullptr)
			return false;
		return matchCore(str, pattern);
	}

	bool matchCore(char* str, char* pattern)
	{
		//递归基，如果两字符串同时到头则完成true，如果没有同时到头则完成false
		if (*str == '\0' && *pattern == '\0')
			return true;
		if (*str != '\0' && *pattern == '\0')
			return false;
		//判断状态1
		if (*(pattern + 1) == '*')
		{
			//判断状态1.1，其中1.1需要考虑三种情况（采用递归减小比对串的方法）
			if (*pattern == *str || (*pattern == '.' && *str != '\0'))
				return matchCore(str + 1, pattern + 2) || matchCore(str + 1, pattern) || matchCore(str, pattern + 2);
			//进入状态1.2
			else
				return matchCore(str, pattern + 2);
		}
		//判断状态2
		if (*str == *pattern || (*pattern == '.' && *str != '\0'))
			return matchCore(str + 1, pattern + 1);
		//进入状态3
		return false;
	}

	//2.一种高级做法，动态规划思想，可惜我看不懂（而且正确率也不高）
	bool match1(char* str, char* pattern)
	{
		if (str == nullptr || pattern == nullptr)
			return false;
		int m = strlen(str); int n = strlen(pattern);
		bool** dp = new bool*[m + 1];
		for (int i = 0; i < m + 1; i++)
			dp[i] = new bool[n + 1];

		dp[0][0] = true;
		for (int i = 1; i <= n; i++)
			if (pattern[i - 1] == '*')
				dp[0][i] = dp[0][i - 2];

		for (int i = 1; i <= m; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				if (str[i - 1] == pattern[j - 1] || pattern[j - 1] == '.')
				{
					dp[i][j] = dp[i - 1][j - 1];
				}
				else if (pattern[j - 1] == '*')
				{
					if (pattern[j - 2] == str[i - 1] || pattern[j - 2] == '.')
					{
						dp[i][j] |= dp[i][j - 1]; // a* counts as single a
						dp[i][j] |= dp[i - 1][j]; // a* counts as multiple a
						dp[i][j] |= dp[i][j - 2]; // a* counts as empty
					}
					else
					{
						dp[i][j] = dp[i][j - 2]; // a* only counts as emptyreturn dp[m][n];
					}
				}
			}
		}
		return dp[m][n];
	}
};

// ====================测试代码====================
void Test(const char* testName, char* string, char* pattern, bool expected)
{
	if (testName != nullptr)
		printf("%s begins: ", testName);
	Solution s;
	if (s.match(string, pattern) == expected)
		printf("Passed.\n");
	else
		printf("FAILED.\n");
}

int main_offer19(int argc, char* argv[])
{
	Test("Test01", "", "", true);
	Test("Test02", "", ".*", true);
	Test("Test03", "", ".", false);
	Test("Test04", "", "c*", true);
	Test("Test05", "a", ".*", true);
	Test("Test06", "a", "a.", false);
	Test("Test07", "a", "", false);
	Test("Test08", "a", ".", true);
	Test("Test09", "a", "ab*", true);
	Test("Test10", "a", "ab*a", false);
	Test("Test11", "aa", "aa", true);
	Test("Test12", "aa", "a*", true);
	Test("Test13", "aa", ".*", true);
	Test("Test14", "aa", ".", false);
	Test("Test15", "ab", ".*", true);
	Test("Test16", "ab", ".*", true);
	Test("Test17", "aaa", "aa*", true);
	Test("Test18", "aaa", "aa.a", false);
	Test("Test19", "aaa", "a.a", true);
	Test("Test20", "aaa", ".a", false);
	Test("Test21", "aaa", "a*a", true);
	Test("Test22", "aaa", "ab*a", false);
	Test("Test23", "aaa", "ab*ac*a", true);
	Test("Test24", "aaa", "ab*a*c*a", true);
	Test("Test25", "aaa", ".*", true);
	Test("Test26", "aab", "c*a*b", true);
	Test("Test27", "aaca", "ab*a*c*a", true);
	Test("Test28", "aaba", "ab*a*c*a", false);
	Test("Test29", "bbbba", ".*a*a", true);
	Test("Test30", "bcbbabab", ".*a*a", false);

	return 0;
}