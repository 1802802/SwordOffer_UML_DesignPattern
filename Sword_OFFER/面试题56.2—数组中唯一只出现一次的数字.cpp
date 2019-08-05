// ������56.2��������Ψһֻ����һ�ε�����
// ��Ŀ����һ�������г���һ������ֻ����һ��֮�⣬�������ֶ����������Ρ���
// �ҳ��Ǹ��Գ���һ�ε����֡�

#include <map>
#include <unordered_map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
#include "BinaryTree.h"
using namespace std;


//˼·��һ�����ֳ������Σ���ʾ������ֵ�ÿһλ�����������Ա�3������ͬ���Ķ��ڶ�����γ��ֵ�����Ҳһ��
//��������ԭ��ʹ��32λ���������洢ÿһλ�е�3��������ÿһλ��������Ϊ�Ǹ��������ֵ�λ���ϵ�����

//����ʱע�⣺��Ҫ���Ǹ���
int FindNumberAppearingOnce(int numbers[], int length)
{
	if (numbers == nullptr || length <= 0)
		throw new exception("Invalid input");

	int a[32] = { 0 };
	long long mask = 1;
	int num = 0;
	for (int i = 0; i < 32; i++)
	{
		for (int j = 0; j < length; j++)
		{
			//��Ҫע��һ��Ϊ������������������ﲻ��ֱ�Ӽӣ���Ҫ�����żӣ����Ҵ������Ϊ!=0��
			if ((numbers[j] & mask) != 0)
				a[i]++;
		}
		mask <<= 1;
		//����Ĳ����ܹؼ�������������������ԣ����������ݸ���i��λ��������õ�num��
		num |= (a[i] % 3) << i;
	}
	return num;
}

//�Ż���ļ�д�棬����Ҫʹ�ø��������븨�������������ȼ�������Ƶ�λ�ͣ�Ȼ���ٽ������λ��%3���뵽num����
int FindNumberAppearingOnce2(int numbers[], int length)
{
	if (numbers == nullptr || length <= 0)
		throw new exception("Invalid input");

	int num = 0;
	for (int i = 0; i < 32; i++)
	{
		int sum = 0;
		for (int j = 0; j < length; j++)
			//�����ʾ�����������е���������i�������ƣ�������1����&�������õ�������λ��iλ�Ľ��ƴ�С
			sum += (numbers[j] >> i) & 0x1;
		//�����ʾ�����е�����%3������iλ����|���������ڽ���ǰ�����iλǶ��num����
		num |= (sum % 3) << i;
	}
	return num;
}

// ====================���Դ���====================
static void Test(const char* testName, int numbers[], int length, int expected)
{
	int result = FindNumberAppearingOnce2(numbers, length);
	if (result == expected)
		printf("%s passed.\n", testName);
	else
		printf("%s FAILED.\n", testName);
}

// �������ֶ���������Ψһ����������С��
static void Test1()
{
	int numbers[] = { 1, 1, 2, 2, 2, 1, 3 };
	int expected = 3;
	Test("Test1", numbers, sizeof(numbers) / sizeof(int), expected);
}

// �������ֶ���������Ψһ�����ֵĴ�Сλ���м�
static void Test2()
{
	int numbers[] = { 4, 3, 3, 2, 2, 2, 3 };
	int expected = 4;
	Test("Test2", numbers, sizeof(numbers) / sizeof(int), expected);
}

// �������ֶ���������Ψһ������������
static void Test3()
{
	int numbers[] = { 4, 4, 1, 1, 1, 7, 4 };
	int expected = 7;
	Test("Test3", numbers, sizeof(numbers) / sizeof(int), expected);
}

// Ψһ�������Ǹ���
static void Test4()
{
	int numbers[] = { -10, 214, 214, 214 };
	int expected = -10;
	Test("Test4", numbers, sizeof(numbers) / sizeof(int), expected);
}

// ����Ψһ�����֣��������ֶ��Ǹ���
static void Test5()
{
	int numbers[] = { -209, 3467, -209, -209 };
	int expected = 3467;
	Test("Test5", numbers, sizeof(numbers) / sizeof(int), expected);
}

// �ظ�������������Ҳ�и���
static void Test6()
{
	int numbers[] = { 1024, -1025, 1024, -1025, 1024, -1025, 1023 };
	int expected = 1023;
	Test("Test6", numbers, sizeof(numbers) / sizeof(int), expected);
}

// �������ֶ��Ǹ���
static void Test7()
{
	int numbers[] = { -1024, -1024, -1024, -1023 };
	int expected = -1023;
	Test("Test7", numbers, sizeof(numbers) / sizeof(int), expected);
}

// Ψһ��������0
static void Test8()
{
	int numbers[] = { -23, 0, 214, -23, 214, -23, 214 };
	int expected = 0;
	Test("Test8", numbers, sizeof(numbers) / sizeof(int), expected);
}

// ����Ψһ�����֣��������ֶ���0
static void Test9()
{
	int numbers[] = { 0, 3467, 0, 0, 0, 0, 0, 0 };
	int expected = 3467;
	Test("Test9", numbers, sizeof(numbers) / sizeof(int), expected);
}

int main_offer56_2(int argc, char* argv[])
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