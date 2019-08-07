// ������63����Ʊ���������
// ��Ŀ�������ĳ��Ʊ�ļ۸���ʱ���Ⱥ�˳��洢�������У������������׸ù�
// Ʊ���ܻ�õ������Ƕ��٣�����һֻ��Ʊ��ĳЩʱ��ڵ�ļ۸�Ϊ{9, 11, 8, 5,
// 7, 12, 16, 14}������������ڼ۸�Ϊ5��ʱ�����벢�ڼ۸�Ϊ16ʱ����������
// �ջ���������11��

#include <map>
#include <deque>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <list>
#include "BinaryTree.h"
using namespace std;

//��Ʊ����������������֣���Ҫ���úÿ���һ�����ǵĹ���

//˼·����̬�滮������ÿ��λ�õ����������ֵ�������0��Ϊ��Сֵ�������Ǹ�ֵʱ
//dp[i] = max( dp[i - 1] + n[i] - n[i - 1], dp[i - 1] )
//�����Ǹ�ֵʱ�����ò���

int MaxDiff(const int* numbers, unsigned length)
{
	if (numbers == nullptr && length < 2)
		return 0;

	vector<int> maxArray(length, -99999);
	int maxValue = INT_MIN;
	int minValue = numbers[0];

	for (int i = 1; i < length; i++)
	{
		maxArray[i] = max({ maxArray[i - 1] + numbers[i] - numbers[i - 1], maxArray[i - 1], numbers[i] - minValue });
		maxValue = max(maxValue, maxArray[i]);
		if (numbers[i] < minValue)
			minValue = numbers[i];
	}

	//for (auto &s : maxArray)
	//	cout << s << " ";
	//cout << endl;
	return maxValue;
}

//˼·2����¼ǰ�����Сֵ�����ϵؼ������Ч�棨ע�ⲻҪֻ��������������ֵ����Ҫ����������ģ�
int MaxDiff2(const int* numbers, unsigned length)
{
	if (numbers == nullptr && length < 2)
		return 0;

	int minValue = INT_MAX;
	int maxDiff = INT_MIN;

	for (int i = 0; i < length; i++)
	{
		if (numbers[i] < minValue)
		{
			maxDiff = max(maxDiff, numbers[i] - minValue);
			minValue = numbers[i];
		}
		else
			maxDiff = max(maxDiff, numbers[i] - minValue);
	}
	
	return maxDiff;
}

// ==================== Test Code ====================
static void Test(const char* testName, const int* numbers, unsigned int length, int expected)
{
	if (testName != nullptr)
		printf("%s begins: ", testName);

	if (MaxDiff2(numbers, length) == expected)
		printf("Passed.\n");
	else
		printf("FAILED.\n");
}

static void Test1()
{
	int numbers[] = { 4, 1, 3, 2, 5 };
	Test("Test1", numbers, sizeof(numbers) / sizeof(int), 4);
}

// �۸����
static void Test2()
{
	int numbers[] = { 1, 2, 4, 7, 11, 16 };
	Test("Test2", numbers, sizeof(numbers) / sizeof(int), 15);
}

// �۸�ݼ�
static void Test3()
{
	int numbers[] = { 16, 11, 7, 4, 2, 1 };
	Test("Test3", numbers, sizeof(numbers) / sizeof(int), -1);
}

// �۸�ȫ����ͬ
static void Test4()
{
	int numbers[] = { 16, 16, 16, 16, 16 };
	Test("Test4", numbers, sizeof(numbers) / sizeof(int), 0);
}

static void Test5()
{
	int numbers[] = { 9, 11, 5, 7, 16, 1, 4, 2 };
	Test("Test5", numbers, sizeof(numbers) / sizeof(int), 11);
}

static void Test6()
{
	int numbers[] = { 2, 4 };
	Test("Test6", numbers, sizeof(numbers) / sizeof(int), 2);
}

static void Test7()
{
	int numbers[] = { 4, 2 };
	Test("Test7", numbers, sizeof(numbers) / sizeof(int), -2);
}

static void Test8()
{
	Test("Test8", nullptr, 0, 0);
}

int main_offer63(int argc, char* argv[])
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	Test6();
	Test7();
	Test8();

	return 0;
}