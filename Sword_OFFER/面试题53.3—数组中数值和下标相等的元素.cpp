// ������53.3����������ֵ���±���ȵ�Ԫ��
// ��Ŀ������һ�������������������ÿ��Ԫ�ض�������������Ψһ�ġ�����ʵ
// ��һ�������ҳ�����������һ����ֵ�������±��Ԫ�ء�
// ���磬������{-3, -1, 1, 3, 5}�У�����3�������±���ȡ�

#include <map>
#include <unordered_map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
#include "List.h"
using namespace std;

//˼·����jΪ�±꣬iΪ�±�j��Ӧ��ֵ��i+j>j+jʱ�����λ��λ��mi�������䣬i+j<j+jʱ�����λ��λ��mi��������

int GetNumberSameAsIndex(const int* numbers, int length)
{
	if (numbers == nullptr || length <= 0)
		return -1;
	int lo = 0;
	int hi = length;
	while (lo < hi)
	{
		int mi = (lo + hi) >> 1;
		//i+j > j+j�����λ��λ��mi��������
		if (numbers[mi] + mi > mi + mi)
			hi = mi;
		//i+j < j+j�����λ��λ��mi��������
		else if (numbers[mi] + mi < mi + mi)
			lo = mi + 1;
		//��������У����Ҫ�ҵ�һ�����λ�ã������ｫ���ݴ��룬������mi������������ң�
		else if (numbers[mi] + mi == mi + mi)
			return mi;
	}
	return -1;
}

// ====================���Դ���====================
static void Test(const char* testName, int numbers[], int length, int expected)
{
	if (GetNumberSameAsIndex(numbers, length) == expected)
		printf("%s passed.\n", testName);
	else
		printf("%s FAILED.\n", testName);
}

static void Test1()
{
	int numbers[] = { -3, -1, 1, 3, 5 };
	int expected = 3;
	Test("Test1", numbers, sizeof(numbers) / sizeof(int), expected);
}

static void Test2()
{
	int numbers[] = { 0, 1, 3, 5, 6 };
	int expected = 1;
	Test("Test2", numbers, sizeof(numbers) / sizeof(int), expected);
}

static void Test3()
{
	int numbers[] = { -1, 0, 1, 2, 4 };
	int expected = 4;
	Test("Test3", numbers, sizeof(numbers) / sizeof(int), expected);
}

static void Test4()
{
	int numbers[] = { -1, 0, 1, 2, 5 };
	int expected = -1;
	Test("Test4", numbers, sizeof(numbers) / sizeof(int), expected);
}

static void Test5()
{
	int numbers[] = { 0 };
	int expected = 0;
	Test("Test5", numbers, sizeof(numbers) / sizeof(int), expected);
}

static void Test6()
{
	int numbers[] = { 10 };
	int expected = -1;
	Test("Test6", numbers, sizeof(numbers) / sizeof(int), expected);
}

static void Test7()
{
	Test("Test7", nullptr, 0, -1);
}

int main_offer53_3(int argc, char* argv[])
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	Test6();
	Test7();

	return 0;
}