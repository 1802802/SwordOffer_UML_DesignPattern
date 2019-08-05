// ������53.2��0��n-1��ȱʧ������
// ��Ŀ��һ������Ϊn-1�ĵ������������е��������ֶ���Ψһ�ģ�����ÿ������
// ���ڷ�Χ0��n-1֮�ڡ��ڷ�Χ0��n-1��n������������ֻ��һ�����ֲ��ڸ�����
// �У����ҳ�������֡�

#include <map>
#include <unordered_map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
#include "List.h"
using namespace std;

//˼·���±�����ֵĶԱȣ��ж��±�λ�õ����ֺ��±�Ĵ�С�Ƚϣ����ֲ���
int GetMissingNumber(const int* numbers, int length)
{
	if (numbers == nullptr || length <= 0)
		return -1;
	int lo = 0;
	int hi = length;
	while (lo < hi)
	{
		int mi = (lo + hi) >> 1;
		//˵��ȱʧ��mi���������
		if (numbers[mi] > mi)
			hi = mi;
		//˵��ȱʧ��mi���ұ�����
		else if (numbers[mi] == mi)
			lo = mi + 1;
	}
	//���lo��hi�����뵽��ȱʧ���Ǹ������
	if (lo == hi)
		return lo;
	else
		return -1;
}

// ====================���Դ���====================
static void Test(const char* testName, int numbers[], int length, int expected)
{
	if (testName != nullptr)
		printf("%s begins: ", testName);

	int result = GetMissingNumber(numbers, length);
	if (result == expected)
		printf("Passed.\n");
	else
		printf("Failed.\n");
}

// ȱʧ���ǵ�һ������0
static void Test1()
{
	int numbers[] = { 1, 2, 3, 4, 5 };
	int expected = 0;
	Test("Test1", numbers, sizeof(numbers) / sizeof(int), expected);
}

// ȱʧ�������һ������
static void Test2()
{
	int numbers[] = { 0, 1, 2, 3, 4 };
	int expected = 5;
	Test("Test2", numbers, sizeof(numbers) / sizeof(int), expected);
}

// ȱʧ�����м�ĳ������0
static void Test3()
{
	int numbers[] = { 0, 1, 2, 4, 5 };
	int expected = 3;
	Test("Test3", numbers, sizeof(numbers) / sizeof(int), expected);
}

// ������ֻ��һ�����֣�ȱʧ���ǵ�һ������0
static void Test4()
{
	int numbers[] = { 1 };
	int expected = 0;
	Test("Test4", numbers, sizeof(numbers) / sizeof(int), expected);
}

// ������ֻ��һ�����֣�ȱʧ�������һ������1
static void Test5()
{
	int numbers[] = { 0 };
	int expected = 1;
	Test("Test5", numbers, sizeof(numbers) / sizeof(int), expected);
}

// ������
static void Test6()
{
	int expected = -1;
	Test("Test6", nullptr, 0, expected);
}

int main_offer53_2(int argc, char* argv[])
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	Test6();

	return 0;
}