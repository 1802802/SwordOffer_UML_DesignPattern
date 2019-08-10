// ������66�������˻�����
// ��Ŀ������һ������A[0, 1, ��, n-1]���빹��һ������B[0, 1, ��, n-1]����
// ��B�е�Ԫ��B[i] =A[0]��A[1]���� ��A[i-1]��A[i+1]������A[n-1]������ʹ�ó�����

#include <map>
#include <deque>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <list>
#include "BinaryTree.h"
using namespace std; 

//˼·������Կ�ת����������ǹ���һ��ÿ��ΪA0��An-1�ľ���ͬʱ���þ���ĶԽ�����Ϊ1��
//��Bi��Ϊi����Ӧ����һ�е�����A�ĳ˻�������ÿ�е�1��λ�ã����Խ����з�ΪC��D�����֣�
class Solution 
{
public:
	//1.����ʵ�֣�ÿһ��Ԫ�ض���ͷ�����������ʱ�临�Ӷ�O(n2)
	//����ʱ�䣺3ms��ռ���ڴ棺488k
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

	//2.��һ��ѭ����ʵ�ֳ˻����飬ʱ�临�Ӷ�O(n)��˵���˾�������֮ǰ����������ݣ��������DP��
	//���Ǹ��ݾ����1��Ϊ���������飬Ȼ���Ƚ�1��ߵĳ��룬�ٽ�1�ұߵĳ���
	//����ʱ�䣺5ms��ռ���ڴ棺476k�����˹��ˣ�ʱ�仹�����ˣ�
	void multiply2(const vector<double>& A, vector<double> &B)
	{
		int length1 = A.size();
		int length2 = B.size();

		if (length1 == length2 && length2 > 1)
		{
			B[0] = 1;
			for (int i = 1; i < length1; i++)
				B[i] = B[i - 1] * A[i - 1];
			//ע������B[n-1]����Ҫ���㣬��Ϊ�����˵���1����B[n-2]��ʼ����
			double d = 1;  //�����dģ��D����
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
	// ����������û��0
	double input[] = { 1, 2, 3, 4, 5 };
	double output[] = { 0, 0, 0, 0, 0 };
	double expected[] = { 120, 60, 40, 30, 24 };

	test("Test1", vector<double>(input, input + sizeof(input) / sizeof(double)),
		vector<double>(output, output + sizeof(output) / sizeof(double)),
		vector<double>(expected, expected + sizeof(expected) / sizeof(double)));
}

static void test2()
{
	// ������������һ��0
	double input[] = { 1, 2, 0, 4, 5 };
	double output[] = { 0, 0, 0, 0, 0 };
	double expected[] = { 0, 0, 40, 0, 0 };

	test("Test2", vector<double>(input, input + sizeof(input) / sizeof(double)),
		vector<double>(output, output + sizeof(output) / sizeof(double)),
		vector<double>(expected, expected + sizeof(expected) / sizeof(double)));
}

static void test3()
{
	// ����������������0
	double input[] = { 1, 2, 0, 4, 0 };
	double output[] = { 0, 0, 0, 0, 0 };
	double expected[] = { 0, 0, 0, 0, 0 };

	test("Test3", vector<double>(input, input + sizeof(input) / sizeof(double)),
		vector<double>(output, output + sizeof(output) / sizeof(double)),
		vector<double>(expected, expected + sizeof(expected) / sizeof(double)));
}

static void test4()
{
	// ��������������������
	double input[] = { 1, -2, 3, -4, 5 };
	double output[] = { 0, 0, 0, 0, 0 };
	double expected[] = { 120, -60, 40, -30, 24 };

	test("Test4", vector<double>(input, input + sizeof(input) / sizeof(double)),
		vector<double>(output, output + sizeof(output) / sizeof(double)),
		vector<double>(expected, expected + sizeof(expected) / sizeof(double)));
}

static void test5()
{
	// ����������ֻ����������
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