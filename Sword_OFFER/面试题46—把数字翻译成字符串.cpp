// ������46�������ַ�����ַ���
// ��Ŀ������һ�����֣����ǰ������¹����������Ϊ�ַ�����0�����"a"��1��
// ���"b"��������11�����"l"��������25�����"z"��һ�����ֿ����ж�����롣��
// ��12258��5�ֲ�ͬ�ķ��룬���Ƿֱ���"bccfi"��"bwfi"��"bczi"��"mcfi"��
// "mzi"������ʵ��һ��������������һ�������ж����ֲ�ͬ�ķ��뷽����

#include <queue>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

//1.˼·��ʹ�ö�̬�滮ʵ�֣�f(i) = f(i+1) + g(i,i+1)*f(i+2)��g(i,i+1)��ʾi��i+1��ɵ���������[10,25]
//�ڽ���ʱ��Ҫע��dp���ݵ�λ����save�����ݵĴ洢λ�ã�save��Ϊ125֮���˳�򣬼���ʱ��Ҫ����������dp���ŴӴ�С���м���
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

//�Ż��Ľ���İ汾����dp��һλ�洢�����ٴ�����
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

// ====================���Դ���====================
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