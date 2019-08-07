// ������61���˿��Ƶ�˳��
// ��Ŀ�����˿����������5���ƣ��ж��ǲ���һ��˳�ӣ�����5�����ǲ��������ġ�
// 2��10Ϊ���ֱ���AΪ1��JΪ11��QΪ12��KΪ13������С�����Կ����������֡�
// �������ƣ����д�С��Ϊ��ӣ�����Ϊ 0���ж����������Ƿ������˳�ӣ�

#include <map>
#include <deque>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <list>
#include "BinaryTree.h"
using namespace std;

//˼·������ȷ�����������Ȼ��ȷ������ܷ����ȱ����������ǰ���ֵ���ɣ�
//˼·2������ķ�ʽ����sort������������ʹ�ù�ϣ����ʵ��
class Solution 
{
public:
	//����ʱ�䣺3ms��ռ���ڴ棺468k
	bool IsContinuous(vector<int> numbers) 
	{
		//1.�߽�����
		if (numbers.size() < 5)
			return false;
		//2.�����������
		int zeroNum = 0;
		int gapNum = 0;
		for (auto &s : numbers)
			if (s == 0)
				zeroNum++;
		//3.�������飬Ȼ�����ǰ���ȱ�ܺ�
		sort(numbers.begin(), numbers.end());
		//ע��small��big�ĳ�ֵ�ӵ�һ����0����λ��ʼ
		int small = zeroNum;
		int big = small + 1;
		while (small < numbers.size() && big < numbers.size())
		{
			if (numbers[small] == numbers[big])
				return false;
			//��Ϊ�Ѿ��Ź����ˣ�ֱ�Ӽ���ȥ����
			gapNum += numbers[big++] - numbers[small++] - 1;
			//��ʹ��hash������Ļ�����Ҫ����ǰ��ָ���big��ֵ����small = big������
		}
		return (gapNum <= zeroNum) ? true : false;
	}

	//����ʱ�䣺5ms��ռ���ڴ棺480k
	bool IsContinuous2(vector<int> numbers)
	{
		//1.�߽�����
		if (numbers.size() < 5)
			return false;
		//2.�����������
		int totalNum[14] = { 0 };
		for (auto &s : numbers)
			totalNum[s]++;
		int zeroNum = totalNum[0];
		int gapNum = 0;
		int small = 1;
		int big = 1;
		while (small < 14 && big < 14)
		{
			for (int i = big; i < 14; i++)
			{
				if (totalNum[i] == 1)
				{
					//hash��ļ��㣬big��smallǰ���ƶ�˫ָ��
					if (small == i)
						continue;
					big = i;
					break;
				}
				else if (totalNum[i] > 1)
					return false;
			}
			gapNum += big - small - 1;
			small = big;
			big++;
			//��ʹ��hash������Ļ�����Ҫ����ǰ��ָ���big��ֵ����small = big������
		}
		return (gapNum <= zeroNum) ? true : false;
	}
};

// ====================���Դ���====================
static void Test(const char* testName, vector<int> numbers, int length, bool expected)
{
	if (testName != nullptr)
		printf("%s begins: ", testName);

	Solution s;
	if (s.IsContinuous2(numbers) == expected)
		printf("Passed.\n");
	else
		printf("Failed.\n");
}

static void Test1()
{
	vector<int> numbers = { 1, 3, 2, 5, 4 };
	Test("Test1", numbers, sizeof(numbers) / sizeof(int), true);
}

static void Test2()
{
	vector<int> numbers = { 1, 3, 2, 6, 4 };
	Test("Test2", numbers, sizeof(numbers) / sizeof(int), false);
}

static void Test3()
{
	vector<int> numbers = { 0, 3, 2, 6, 4 };
	Test("Test3", numbers, sizeof(numbers) / sizeof(int), true);
}

static void Test4()
{
	vector<int> numbers = { 0, 3, 1, 6, 4 };
	Test("Test4", numbers, sizeof(numbers) / sizeof(int), false);
}

static void Test5()
{
	vector<int> numbers = { 1, 3, 0, 5, 0 };
	Test("Test5", numbers, sizeof(numbers) / sizeof(int), true);
}

static void Test6()
{
	vector<int> numbers = { 1, 3, 0, 7, 0 };
	Test("Test6", numbers, sizeof(numbers) / sizeof(int), false);
}

static void Test7()
{
	vector<int> numbers = { 1, 0, 0, 5, 0 };
	Test("Test7", numbers, sizeof(numbers) / sizeof(int), true);
}

static void Test8()
{
	vector<int> numbers = { 1, 0, 0, 7, 0 };
	Test("Test8", numbers, sizeof(numbers) / sizeof(int), false);
}

static void Test9()
{
	vector<int> numbers = { 3, 0, 0, 0, 0 };
	Test("Test9", numbers, sizeof(numbers) / sizeof(int), true);
}

static void Test10()
{
	vector<int> numbers = { 0, 0, 0, 0, 0 };
	Test("Test10", numbers, sizeof(numbers) / sizeof(int), true);
}

// �ж���
static void Test11()
{
	vector<int> numbers = { 1, 0, 0, 1, 0 };
	Test("Test11", numbers, sizeof(numbers) / sizeof(int), false);
}

// ³���Բ���
static void Test12()
{
	Test("Test12", vector<int>(), 0, false);
}

int main_offer61(int argc, char* argv[])
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
	Test10();
	Test11();
	Test12();

	return 0;
}
