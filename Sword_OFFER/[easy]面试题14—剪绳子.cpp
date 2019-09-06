#ifndef offer14
#define offer14

#include <iostream>
using namespace std;

//剪绳子问题，采用动态规划分析：“从上往下的分析问题，从下往上的解决问题”
//分析：作为主问题时f(n) = max(f(i)*f(n-i))，作为子问题时：f(n) = max(f(i)*f(n-i),n)，解决：f(1) = 0,f(2) = 1, f(3) = 2
int maxProductAfterCutting_solution1(int length)
{
	//当成主问题时，n = 2时，其最大只能为1*1，而当n = 3时，其最大也只能为2*1
	//但是当他们被当成子问题时f(2)max = 2, f(3)max = 3

	//以下为length <= 3，当成主问题的最优解
	if (length < 2)
		return 0;
	if (length == 2)
		return 1;
	if (length == 3)
		return 2;
	
	//以下为length >= 4时，当成子问题的最优解
	int* bestSubProblem = new int[length + 1];
	bestSubProblem[0] = 0;
	bestSubProblem[1] = 1;
	bestSubProblem[2] = 2;
	bestSubProblem[3] = 3;

	int max = 0;
	for (int i = 4; i <= length; i++)
	{
		max = 0;
		for (int j = 1; j <= i >> 1; j++)
		{
			int submax = bestSubProblem[j] * bestSubProblem[i - j];
			if (submax > max)
			{
				max = submax;
				bestSubProblem[i] = max;
			}
		}
	}
	max = bestSubProblem[length];
	//cout << "max:" << max << endl;
	delete[] bestSubProblem;
	return max;
}

int maxProductAfterCutting_solution2(int length)
{
	//以下为length <= 3，当成主问题的最优解
	if (length < 2)
		return 0;
	if (length == 2)
		return 1;
	if (length == 3)
		return 2;
	if (length == 4)
		return 4;

	//f(3) = 3是最大的单子问题存在，f(4)是最小的单主问题存在
	//贪心思想：当n>=5时，尽可能地去剪去长度为3的绳子，当n=4时，剪成长度为2的绳子
	//1.尽可能地将绳子减为3（由于参与剪3的都是大于5的，所以至少会有1个3被剪出来）
	int cut_three = length / 3;
	//2.判断最后被剪到的长度是不是1，如果是则使其回到4
	if (length - cut_three * 3 == 1)
		cut_three--;
	//3.将剩余的部分剪2（可能的情况有剩2和剩4）
	int cut_two = (length - 3 * cut_three) / 2;
	//4.计算最终最佳数字
	return pow(3, cut_three)*pow(2, cut_two);
}

int maxProductAfterCutting_solution3(int length)
{
	//以下为length <= 3，当成主问题的最优解
	if (length < 2)
		return 0;
	if (length == 2)
		return 1;
	if (length == 3)
		return 2;
	if (length == 4)
		return 4;

	int cut_three = 0;
	int cut_two = 0;
	while (length)
	{
		if (length != 4 && length != 2)
		{
			length -= 3;
			cut_three++;
		}
		else
		{
			cut_two = length / 2;
			break;
		}
	}
	return pow(3, cut_three)*pow(2, cut_two);
}

int cutRope(int number)
{
	if (number < 2)
		return 0;
	if (number == 2)
		return 1;
	if (number == 3)
		return 2;
	if (number == 4)
		return 4;
	//尽可能地去剪成3，而剪成2的条数要么是1，要么是剪到1后回4变成2
	int three_times = number / 3;
	int two_times = 1;
	if (number - 3 * three_times == 1)
	{
		three_times--;
		two_times++;
	}
	return pow(2, two_times)*pow(3, three_times);
}

// ====================测试代码====================
static void test(const char* testName, int length, int expected)
{
	int result1 = maxProductAfterCutting_solution1(length);
	if (result1 == expected)
		std::cout << "Solution1 for " << testName << " passed." << std::endl;
	else
		std::cout << "Solution1 for " << testName << " FAILED." << std::endl;

	int result2 = maxProductAfterCutting_solution2(length);
	if (result2 == expected)
		std::cout << "Solution2 for " << testName << " passed." << std::endl;
	else
		std::cout << "Solution2 for " << testName << " FAILED." << std::endl;
}

static void test1()
{
	int length = 1;
	int expected = 0;
	test("test1", length, expected);
}

static void test2()
{
	int length = 2;
	int expected = 1;
	test("test2", length, expected);
}

static void test3()
{
	int length = 3;
	int expected = 2;
	test("test3", length, expected);
}

static void test4()
{
	int length = 4;
	int expected = 4;
	test("test4", length, expected);
}

static void test5()
{
	int length = 5;
	int expected = 6;
	test("test5", length, expected);
}

static void test6()
{
	int length = 6;
	int expected = 9;
	test("test6", length, expected);
}

static void test7()
{
	int length = 7;
	int expected = 12;
	test("test7", length, expected);
}

static void test8()
{
	int length = 8;
	int expected = 18;
	test("test8", length, expected);
}

static void test9()
{
	int length = 9;
	int expected = 27;
	test("test9", length, expected);
}

static void test10()
{
	int length = 10;
	int expected = 36;
	test("test10", length, expected);
}

static void test11()
{
	int length = 50;
	int expected = 86093442;
	test("test11", length, expected);
}

int main_offer14(int agrc, char* argv[])
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
	test11();

	return 0;
}

#endif