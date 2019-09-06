#ifndef offer14
#define offer14

#include <iostream>
using namespace std;

//���������⣬���ö�̬�滮���������������µķ������⣬�������ϵĽ�����⡱
//��������Ϊ������ʱf(n) = max(f(i)*f(n-i))����Ϊ������ʱ��f(n) = max(f(i)*f(n-i),n)�������f(1) = 0,f(2) = 1, f(3) = 2
int maxProductAfterCutting_solution1(int length)
{
	//����������ʱ��n = 2ʱ�������ֻ��Ϊ1*1������n = 3ʱ�������Ҳֻ��Ϊ2*1
	//���ǵ����Ǳ�����������ʱf(2)max = 2, f(3)max = 3

	//����Ϊlength <= 3����������������Ž�
	if (length < 2)
		return 0;
	if (length == 2)
		return 1;
	if (length == 3)
		return 2;
	
	//����Ϊlength >= 4ʱ����������������Ž�
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
	//����Ϊlength <= 3����������������Ž�
	if (length < 2)
		return 0;
	if (length == 2)
		return 1;
	if (length == 3)
		return 2;
	if (length == 4)
		return 4;

	//f(3) = 3�����ĵ���������ڣ�f(4)����С�ĵ����������
	//̰��˼�룺��n>=5ʱ�������ܵ�ȥ��ȥ����Ϊ3�����ӣ���n=4ʱ�����ɳ���Ϊ2������
	//1.�����ܵؽ����Ӽ�Ϊ3�����ڲ����3�Ķ��Ǵ���5�ģ��������ٻ���1��3����������
	int cut_three = length / 3;
	//2.�ж���󱻼����ĳ����ǲ���1���������ʹ��ص�4
	if (length - cut_three * 3 == 1)
		cut_three--;
	//3.��ʣ��Ĳ��ּ�2�����ܵ������ʣ2��ʣ4��
	int cut_two = (length - 3 * cut_three) / 2;
	//4.���������������
	return pow(3, cut_three)*pow(2, cut_two);
}

int maxProductAfterCutting_solution3(int length)
{
	//����Ϊlength <= 3����������������Ž�
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
	//�����ܵ�ȥ����3��������2������Ҫô��1��Ҫô�Ǽ���1���4���2
	int three_times = number / 3;
	int two_times = 1;
	if (number - 3 * three_times == 1)
	{
		three_times--;
		two_times++;
	}
	return pow(2, two_times)*pow(3, three_times);
}

// ====================���Դ���====================
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