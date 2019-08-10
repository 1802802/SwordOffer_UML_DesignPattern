// 面试题66：构建乘积数组
// 题目：给定一个数组A[0, 1, …, n-1]，请构建一个数组B[0, 1, …, n-1]，其
// 中B中的元素B[i] =A[0]×A[1]×… ×A[i-1]×A[i+1]×…×A[n-1]。不能使用除法。

#include <map>
#include <deque>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <list>
#include "BinaryTree.h"
using namespace std; 

//思路：万物皆可转矩阵，这里就是构建一个每行为A0到An-1的矩阵，同时将该矩阵的对角线设为1，
//而Bi即为i所对应的那一行的所有A的乘积（根据每行的1的位置，可以将该行分为C与D两部分）
class Solution 
{
public:
	//1.常规实现，每一个元素都从头算起乘起来，时间复杂度O(n2)
	//运行时间：3ms，占用内存：488k
	void multiply(const vector<double>& A, vector<double> &B)
	{
		vector<double> save(A.size(), 1);
		for (int i = 0; i < A.size(); i++)
		{
			for (int j = 0; j < B.size(); j++)
			{
				if (j != i)
					save[i] *= A[j];
			}
		}
		B = save;
	}

	//2.在一次循环中实现乘积数组，时间复杂度O(n)（说穿了就是利用之前的算过的数据，可以类比DP）
	//就是根据矩阵的1分为左右两数组，然后先将1左边的乘入，再将1右边的乘入
	//运行时间：5ms，占用内存：476k（奇了怪了，时间还增加了）
	void multiply2(const vector<double>& A, vector<double> &B)
	{
		int length1 = A.size();
		int length2 = B.size();

		if (length1 == length2 && length2 > 1)
		{
			B[0] = 1;
			for (int i = 1; i < length1; i++)
				B[i] = B[i - 1] * A[i - 1];
			//注意这里B[n-1]不需要计算，因为其最后乘的是1，从B[n-2]开始计算
			double d = 1;  //这里的d模拟D数组
			for (int i = length2 - 2; i >= 0; i--)
			{
				d *= A[i + 1];
				B[i] *= d;
				//B[n-2] *= A[n-1]
			}
		}
		else
		{
			throw new exception("length is error");
		}
	}
};

//================= Test Code =================
static bool EqualArrays(const vector<double>& input, const vector<double>& output)
{
	int length1 = input.size();
	int length2 = output.size();

	if (length1 != length2)
		return false;

	for (int i = 0; i < length1; ++i)
	{
		if (abs(input[i] - output[i]) > 0.0000001)
			return false;
	}

	return true;
}

static void test(char* testName, const vector<double>& input, vector<double>& output, const vector<double>& expected)
{
	printf("%s Begins: ", testName);

	Solution s;
	s.multiply2(input, output);
	if (EqualArrays(output, expected))
		printf("Passed.\n");
	else
		printf("FAILED.\n");
}

static void test1()
{
	// 输入数组中没有0
	double input[] = { 1, 2, 3, 4, 5 };
	double output[] = { 0, 0, 0, 0, 0 };
	double expected[] = { 120, 60, 40, 30, 24 };

	test("Test1", vector<double>(input, input + sizeof(input) / sizeof(double)),
		vector<double>(output, output + sizeof(output) / sizeof(double)),
		vector<double>(expected, expected + sizeof(expected) / sizeof(double)));
}

static void test2()
{
	// 输入数组中有一个0
	double input[] = { 1, 2, 0, 4, 5 };
	double output[] = { 0, 0, 0, 0, 0 };
	double expected[] = { 0, 0, 40, 0, 0 };

	test("Test2", vector<double>(input, input + sizeof(input) / sizeof(double)),
		vector<double>(output, output + sizeof(output) / sizeof(double)),
		vector<double>(expected, expected + sizeof(expected) / sizeof(double)));
}

static void test3()
{
	// 输入数组中有两个0
	double input[] = { 1, 2, 0, 4, 0 };
	double output[] = { 0, 0, 0, 0, 0 };
	double expected[] = { 0, 0, 0, 0, 0 };

	test("Test3", vector<double>(input, input + sizeof(input) / sizeof(double)),
		vector<double>(output, output + sizeof(output) / sizeof(double)),
		vector<double>(expected, expected + sizeof(expected) / sizeof(double)));
}

static void test4()
{
	// 输入数组中有正、负数
	double input[] = { 1, -2, 3, -4, 5 };
	double output[] = { 0, 0, 0, 0, 0 };
	double expected[] = { 120, -60, 40, -30, 24 };

	test("Test4", vector<double>(input, input + sizeof(input) / sizeof(double)),
		vector<double>(output, output + sizeof(output) / sizeof(double)),
		vector<double>(expected, expected + sizeof(expected) / sizeof(double)));
}

static void test5()
{
	// 输入输入中只有两个数字
	double input[] = { 1, -2 };
	double output[] = { 0, 0 };
	double expected[] = { -2, 1 };

	test("Test5", vector<double>(input, input + sizeof(input) / sizeof(double)),
		vector<double>(output, output + sizeof(output) / sizeof(double)),
		vector<double>(expected, expected + sizeof(expected) / sizeof(double)));
}

int main_offer66(int argc, char* argv[])
{
	test1();
	test2();
	test3();
	test4();
	test5();

	return 0;
}