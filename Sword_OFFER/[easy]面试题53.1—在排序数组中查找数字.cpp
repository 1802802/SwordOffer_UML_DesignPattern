// ������53.1�������������в�������
// ��Ŀ��ͳ��һ�����������������г��ֵĴ�����

#include <map>
#include <unordered_map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
#include "List.h"
using namespace std;

class Solution 
{
public:
	//������ĺܶ��֣�������˳����ң�map��֮��Ķ��У��������Ҫʵ��ʱ�临�Ӷ�ΪO(logn)
	//˼·��Ҫ��λΪʹ�ö��ֲ����ҵ���Ӧ���ֵĵ�һ���������һ������������һ�����ĵ�һ��������Ȼ����������ӵ�
	//����ʱ�䣺3ms��ռ���ڴ棺604k
	int GetNumberOfK(vector<int> data, int k) 
	{
		if (data.size() < 1)
			return 0;
		//����һ�ֺ�ɧ����������k+1�ѵ�һ������ȥ��k�ѵ�һ����������BinarySearchFirst��Ҫ����lo������-1
		//ԭ�����ڷ���lo�᷵�����ʧ�ܵ�λ��
		//int i1 = BinarySearchFirst(data, k);
		//int i2 = BinarySearchFirst(data, k + 1);
		//return i2 - i1;

		//����Ϊ��ͳ��������һ�������׺�β
		int i1 = BinarySearchFirst(data, k);
		int i2 = BinarySearchLast(data, k);
		cout << "i2:" << i2 << endl;
		cout << "i1:" << i1 << endl;
		if (i2 == -1 && i1 == -1)
			return 0;
		return i2 - i1 + 1;
		
	}

	int BinarySearchFirst(vector<int>& data, int k)
	{
		int lo = 0; int hi = data.size();
		while (lo < hi)
		{
			int mi = (lo + hi) >> 1;
			if (data[mi] > k)
				hi = mi;
			else if (data[mi] < k)
				lo = mi + 1;
			else
			{
				//�˴��жϵ�ǰk�Ƿ�Ϊ�������еĵ�һ��k��������λ��Ϊ0������������򷵻�λ��mi����������������
				//�ɹ��򷵻�k�ĵ�һ������index��ʧ���򷵻�k����������һλֵ�ĵ�һ������index������ǰ����Ϊ���һλʱ
				//�򷵻ص���hi�����ֵ����data��size()λ�������Ϊ��������.end()λ��
				if ((mi > 0 && data[mi - 1] != k) || mi == 0)
					return mi;
				else
					hi = mi;
			}
		}
		return -1;
	}

	int BinarySearchLast(vector<int>& data, int k)
	{
		int lo = 0; int hi = data.size();
		while (lo < hi)
		{
			int mi = (lo + hi) >> 1;
			if (data[mi] > k)
				hi = mi;
			else if (data[mi] < k)
				lo = mi + 1;
			else
			{
				//�˴��жϵ�ǰk�Ƿ�Ϊ�������е����һ��k��������λ��Ϊhi - 1������������򷵻�λ��mi����������������
				if ((mi < hi - 1 && data[mi + 1] != k) || mi == hi - 1)
					return mi;
				else
					lo = mi + 1;
			}
		}
		return -1;
	}
};

// ====================���Դ���====================
static void Test(const char* testName, vector<int> data, int length, int k, int expected)
{
	if (testName != nullptr)
		printf("%s begins: ", testName);
	Solution s;
	int result = s.GetNumberOfK(data, k);
	if (result == expected)
		printf("Passed.\n");
	else
		printf("Failed.\n");
}

// ���ҵ����ֳ�����������м�
static void Test1()
{
	vector<int> data = { 1, 2, 3, 3, 3, 3, 4, 5 };
	Test("Test1", data, sizeof(data) / sizeof(int), 3, 4);
}

// ���ҵ��������������Ŀ�ͷ
static void Test2()
{
	vector<int> data = { 3, 3, 3, 3, 4, 5 };
	Test("Test2", data, sizeof(data) / sizeof(int), 3, 4);
}

// ���ҵ��������������Ľ�β
static void Test3()
{
	vector<int> data = { 1, 2, 3, 3, 3, 3 };
	Test("Test3", data, sizeof(data) / sizeof(int), 3, 4);
}

// ���ҵ����ֲ�����
static void Test4()
{
	vector<int> data = { 1, 3, 3, 3, 3, 4, 5 };
	Test("Test4", data, sizeof(data) / sizeof(int), 2, 0);
}

// ���ҵ����ֱȵ�һ�����ֻ�С��������
static void Test5()
{
	vector<int> data = { 1, 3, 3, 3, 3, 4, 5 };
	Test("Test5", data, sizeof(data) / sizeof(int), 0, 0);
}

// ���ҵ����ֱ����һ�����ֻ��󣬲�����
static void Test6()
{
	vector<int> data = { 1, 3, 3, 3, 3, 4, 5 };
	Test("Test6", data, sizeof(data) / sizeof(int), 6, 0);
}

// �����е����ִ�ͷ��β���ǲ��ҵ�����
static void Test7()
{
	vector<int> data = { 3, 3, 3, 3 };
	Test("Test7", data, sizeof(data) / sizeof(int), 3, 4);
}

// �����е����ִ�ͷ��βֻ��һ���ظ������֣����ǲ��ҵ�����
static void Test8()
{
	vector<int> data = { 3, 3, 3, 3 };
	Test("Test8", data, sizeof(data) / sizeof(int), 4, 0);
}

// ������ֻ��һ�����֣��ǲ��ҵ�����
static void Test9()
{
	vector<int> data = { 3 };
	Test("Test9", data, sizeof(data) / sizeof(int), 3, 1);
}

// ������ֻ��һ�����֣����ǲ��ҵ�����
static void Test10()
{
	vector<int> data = { 3 };
	Test("Test10", data, sizeof(data) / sizeof(int), 4, 0);
}

// ³���Բ��ԣ������ָ��
static void Test11()
{
	Test("Test11", vector<int>(), 0, 0, 0);
}

int main_offer53(int argc, char* argv[])
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

	return 0;
}