// ������56.1��������ֻ����һ�ε���������
// ��Ŀ��һ�����������������������֮�⣬���������ֶ����������Ρ���д����
// �ҳ�������ֻ����һ�ε����֡�Ҫ��ʱ�临�Ӷ���O(n)���ռ临�Ӷ���O(1)��

#include <map>
#include <unordered_map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
#include "BinaryTree.h"
using namespace std;

class Solution 
{
public:
	//����˼·����������������ж����ͬ����ʱ���򲻶ϵ������и���λ�����飬ֱ������������ֵ��Ϊ0
	//����ʱ�䣺4ms��ռ���ڴ棺480k
	static void FindNumsAppearOnce(vector<int> data, int* num1, int *num2) 
	{
		int firstResult = 0;
		for (auto &s : data)
			firstResult ^= s;
		//��������firstResult��Ȼ��Ϊ0����Ϊ�������������ֵ��������������з��飺
		int n = 0;
		while (firstResult)
		{
			if (firstResult & 0x1 == 1)
				break;
			else
			{
				firstResult >>= 1;
				n++;
			}
		}
		//ע��num1��num2�ĳ�ʼ��
		*num1 = *num2 = 0;
		for (auto &s : data)
		{
			if (((s >> n) & (0x1)) == 1)
				(*num1) ^= s;
			else
				(*num2) ^= s;
		}
	}
};

// ====================���Դ���====================
static void Test(const char* testName, vector<int> data, int length, int expected1, int expected2)
{
	if (testName != nullptr)
		printf("%s begins: ", testName);

	Solution s;
	int result1, result2;
	s.FindNumsAppearOnce(data, &result1, &result2);

	if ((expected1 == result1 && expected2 == result2) ||
		(expected2 == result1 && expected1 == result2))
		printf("Passed.\n\n");
	else
		printf("Failed.\n\n");
}

static void Test1()
{
	vector<int> data = { 2, 4, 3, 6, 3, 2, 5, 5 };
	Test("Test1", data, sizeof(data) / sizeof(int), 4, 6);
}

static void Test2()
{
	vector<int> data = { 4, 6 };
	Test("Test2", data, sizeof(data) / sizeof(int), 4, 6);
}

static void Test3()
{
	vector<int> data = { 4, 6, 1, 1, 1, 1 };
	Test("Test3", data, sizeof(data) / sizeof(int), 4, 6);
}

int main_offer56_1(int argc, char* argv[])
{
	Test1();
	Test2();
	Test3();

	return 0;
}