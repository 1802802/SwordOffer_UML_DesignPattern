// ������39�������г��ִ�������һ�������
// ��Ŀ����������һ�����ֳ��ֵĴ����������鳤�ȵ�һ�룬���ҳ�������֡�
// ��������һ������Ϊ9������{1,2,3,2,2,2,5,4,2}����������2�������г�����5�Σ��������鳤�ȵ�һ�룬������2����������������0��

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
using namespace std;

class Solution 
{
public:
	//1.ʹ��map�洢��ʱ�临�Ӷ�O(nlogn)���ռ临�Ӷ�O(n)������ʱ�䣺3ms��ռ���ڴ棺468k
	int MoreThanHalfNum_Solution1(vector<int> numbers) 
	{
		map<int, int> save;
		for (auto &s : numbers)
		{
			if (!save.insert({ s,1 }).second)
				save[s]++;
		}
		for (auto &s : save)
			if (s.second > numbers.size() >> 1)
				return s.first;
		return 0;
	}
	//��׼����λ�������㷨������ʱ�䣺3ms��ռ���ڴ棺472k��ʱ�临�Ӷ�O(n)
	//2.����partition������ʱ�临�Ӷ�ΪO(n)���㷨������㿪ʼ������λ�����֣�ֱ����ǰ��㵽������λ
	int MoreThanHalfNum_Solution2(vector<int> numbers)
	{
		if (!checkInvalid(numbers))
			return 0;
		int middle = numbers.size() >> 1;
		int start = 0; int end = numbers.size() - 1;
		//�����
		int index = Partition(numbers, start, end);
		//ֱ��������λ��λ����ͬ������������㲻�ϵرƽ�middle��λ�㣩
		while (index != middle)
		{
			if (index > middle)
			{
				end = index - 1;
				index = Partition(numbers, start, end);
			}
			else
			{
				start = index + 1;
				index = Partition(numbers, start, end);
			}
		}
		int result = numbers[middle];
		if (!checkMoreThanHalf(numbers, result))
			result = 0;
		return result;
	}
	//����1�����Ϸ���
	bool checkInvalid(vector<int>& numbers)
	{
		if (numbers.size() < 1)
			return false;
		return true;
	}
	//����2�������ٻ����㷨
	int Partition(vector<int>& numbers, int start, int end)
	{
		int tmp = numbers[start];
		while (start < end)
		{
			while (start < end && numbers[end] >= tmp)
				end--;
			numbers[start] = numbers[end];
			while (start < end && numbers[start] <= tmp)
				start++;
			numbers[end] = numbers[start];
		}
		numbers[start] = tmp;
		return start;
	}
	//����3�����������Ƿ�Ϊ������ǰ�����õ���result����Ϊ��ֵ���м����λ����
	bool checkMoreThanHalf(vector<int>& numbers, int result)
	{
		int num = 0;
		for (auto &s : numbers)
			if (s == result)
				num++;
		if (num * 2 > numbers.size())
			return true;
		else
			return false;
	}

	//3.����ѡȡ�㷨��׼�棨������ʽ��������ʱ�䣺3ms��ռ���ڴ棺480k��ʱ�临�Ӷ�O(n)
	int MoreThanHalfNum_Solution3(vector<int> numbers)
	{
		if (numbers.size() < 1)
			return 0;
		int result = numbers[0];
		int times = 1;
		//3.1��ѡ��ѡȡ
		for (int i = 1; i < numbers.size(); i++)
		{
			if (numbers[i] == result)
				times++;
			else
				times--;
			if (times == 0)
			{
				result = numbers[i];
				times++;
			}
		}
		//3.2��ѡ���ж��Ƿ�ѡ
		times = 0;
		for (auto &s : numbers)
			if (s == result)
				times++;
		if (times * 2 > numbers.size())
			return result;
		return 0;
	}
};

// ====================���Դ���====================
static void Test(char* testName, vector<int>& a, int length, int expectedValue, bool expectedFlag)
{
	if (testName != nullptr)
		printf("%s begins: \n", testName);

	Solution s;
	printf("Test for solution1: ");
	int result = s.MoreThanHalfNum_Solution3(a);
	if (result == expectedValue)
		printf("Passed.\n");
	else
		printf("Failed.\n");
}

// ���ڳ��ִ����������鳤��һ�������
static void Test1()
{
	vector<int> a = { 1, 2, 3, 2, 2, 2, 5, 4, 2 };
	Test("Test1", a, a.size(), 2, false);
}

// �����ڳ��ִ����������鳤��һ�������
static void Test2()
{
	vector<int> a = { 1, 2, 3, 2, 4, 2, 5, 2, 3 };
	Test("Test2", a, a.size(), 0, true);
}

// ���ִ����������鳤��һ������ֶ������������ǰ�벿��
static void Test3()
{
	vector<int> a = { 2, 2, 2, 2, 2, 1, 3, 4, 5 };
	Test("Test3", a, a.size(), 2, false);
}

// ���ִ����������鳤��һ������ֶ�����������ĺ�벿��
static void Test4()
{
	vector<int> a = { 1, 3, 4, 5, 2, 2, 2, 2, 2 };
	Test("Test4", a, a.size(), 2, false);
}

// �����ָ��
static void Test5()
{
	vector<int> a = { 1 };
	Test("Test5", a, a.size(), 1, false);
}

// �����ָ��
static void Test6()
{
	vector<int> a;
	Test("Test6", a, 0, 0, true);
}

int main_offer39(int argc, char* argv[])
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	Test6();

	return 0;
}