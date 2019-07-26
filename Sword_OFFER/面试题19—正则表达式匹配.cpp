// ������19��������ʽƥ��
// ��Ŀ����ʵ��һ����������ƥ�����'.'��'*'��������ʽ��ģʽ�е��ַ�'.'��ʾ����һ���ַ���
// ��'*'��ʾ��ǰ����ַ����Գ�������Σ�����0�Σ��� �ڱ����У�ƥ����ָ�ַ����������ַ�ƥ������ģʽ��
// ���磬�ַ���"aaa"��ģʽ"a.a"��"ab*ac*a"ƥ�䣬������"aa.a"��"ab*a"����ƥ��

#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
	//forѭ���ĵݹ�ʵ�ַ�ʽ����ͨ����δ�������ʵ�ֶ�����ڵ���������ţ�����������õķ�ʽ��ֻ��һ�����ڵ���������

	//�����˼·��Ҫ����Դ����״̬�����ֵģ������˵��5��״̬����ϸ�µ���˵��8��״̬����1.1ϸ�ֵĻ���
	//�Ժ���ص����ⶼ���Ա�����ƵĶ�·�ݹ����⣬���ݹ���������ͨ����������������̡�����ʱ�䣺3ms��ռ���ڴ棺472k
	
	/*��������һ��˼·�����öԲ�ͬƥ��״̬�Ļ�����ʵ�֣�ͨ�����ƶ�������ɣ����õݹ��С�ȶԴ��ķ�����
	1.�жϵ�ǰλ�õ���һλ�Ƿ�Ϊ'*�����������״̬1��
		����״̬1�󣬵�ǰλ�������Ƿ�ƥ�䣬�������״̬1.1������ͽ���״̬1.2��
	1.1״̬1.1����ӵ�״̬����ʱ��һλΪ'*'������ƥ�䣬�����������(ab*c,abc),(ab*c,abbbc),(ab*bc,abc)
		����״̬1.1��Ӧ�����ƶ�����ָ��ķ�ʽ��matchCore(str + 1, pattern + 2) || matchCore(str + 1, pattern) || matchCore(str, pattern + 2);
	1.2״̬1.2����ʱ��ǰλ�õ���һλ�Ƿ�Ϊ'*������������ƥ�䣬���Ҷ�Ӧ�����(af*c,abc/ac)�����������ΪmatchCore(str, pattern + 2)��
	2.��ǰλ�õ���һλ��Ϊ'*'���жϵ�ǰλ�������Ƿ�ƥ�䣬�������״̬2��
		״̬2�Ĳ����ܼ򵥣����������ɹ�ƥ������λ��Ϊ'*'��char��pat��ǰ��һλ����
	3.��ǰλ�õ���һλ��Ϊ'*����ͬʱ��ǰλ��������ƥ�䣬�����״̬3��ֱ�ӷ���false����
	*/

	bool match(char* str, char* pattern)
	{
		if (str == nullptr || pattern == nullptr)
			return false;
		return matchCore(str, pattern);
	}

	bool matchCore(char* str, char* pattern)
	{
		//�ݹ����������ַ���ͬʱ��ͷ�����true�����û��ͬʱ��ͷ�����false
		if (*str == '\0' && *pattern == '\0')
			return true;
		if (*str != '\0' && *pattern == '\0')
			return false;
		//�ж�״̬1
		if (*(pattern + 1) == '*')
		{
			//�ж�״̬1.1������1.1��Ҫ����������������õݹ��С�ȶԴ��ķ�����
			if (*pattern == *str || (*pattern == '.' && *str != '\0'))
				return matchCore(str + 1, pattern + 2) || matchCore(str + 1, pattern) || matchCore(str, pattern + 2);
			//����״̬1.2
			else
				return matchCore(str, pattern + 2);
		}
		//�ж�״̬2
		if (*str == *pattern || (*pattern == '.' && *str != '\0'))
			return matchCore(str + 1, pattern + 1);
		//����״̬3
		return false;
	}

	//2.һ�ָ߼���������̬�滮˼�룬��ϧ�ҿ�������������ȷ��Ҳ���ߣ�
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

// ====================���Դ���====================
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