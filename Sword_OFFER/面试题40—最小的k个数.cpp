// ������40����С��k����
// ��Ŀ������n���������ҳ�������С��K��������������4,5,1,6,2,7,3,8��8�����֣�����С��4��������1,2,3,4,��

#include <set>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

class Solution 
{
public:
	//1.����������O(nlogn)������ʱ�䣺3ms��ռ���ڴ棺480k
	vector<int> GetLeastNumbers_Solution(vector<int>& input, int k) 
	{
		if (input.size() < 1)
			return vector<int>();
		sort(input.begin(), input.end());
		vector<int> tmp;
		if (k > input.size())
		{
			for (int i = 0; i < input.size(); i++)
				tmp.push_back(input[i]);
		}
		else
		{
			for (int i = 0; i < k; i++)
				tmp.push_back(input[i]);
		}
		return tmp;
	}

	//2.�����޸����ݣ������ٻ����㷨�����ȶ���ʱ��O��n��
	vector<int> GetLeastNumbers_Solution2(vector<int>& input, int k)
	{
		if (input.size() < 1)
			return vector<int>();
		if (k > input.size() || k <= 0)
			return vector<int>();
		int start = 0; int end = input.size() - 1;
		//����㣨����㲻�ϵرƽ�k-1����
		int index = Partition(input, start, end);
		while (index != k - 1)
		{
			if (index > k - 1)
			{
				end = index - 1;
				index = Partition(input, start, end);
			}
			else
			{
				start = index + 1;
				index = Partition(input, start, end);
			}
		}
		vector<int> tmp;
		for (int i = 0; i < k; i++)
			tmp.push_back(input[i]);
		return tmp;
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

	//3.�������Ѵ�ȡ���ݣ�����ʱ�䣺3ms��ռ���ڴ棺476k
	vector<int> GetLeastNumbers_Solution3(vector<int>& input, int k)
	{
		if (input.size() < 1)
			return vector<int>();
		if (k > input.size() || k <= 0)
			return vector<int>();
		make_heap(input.begin(), input.end(), [](int a, int b) {return a > b; });
		vector<int> tmp;
		for (int i = 0; i < k; i++)
		{
			tmp.push_back(input[0]);
			pop_heap(input.begin(), input.end(), [](int a, int b) {return a > b; });
			input.pop_back();   //pop_heap֮��Ҫpop_back��push_back֮��Ҫpush_heap
		}
		return tmp;
	}

	//4.���ú������ʵ����С���ݵĴ洢���̣��������������ݲ���������������֮��Ƚ����ֵ��С���滻�������ӣ����滻���ֵ������ѡ�����ֵ��
	//�ص����ʺϴ���������,����ʱ�䣺4ms��ռ���ڴ棺484k������ʱ��O(nlogk)

	struct intComp 
	{
		bool operator() (const int& lhs, const int& rhs) const { return lhs > rhs; };
	};

	vector<int> GetLeastNumbers_Solution4(vector<int>& input, int k)
	{
		if (input.size() < 1)
			return vector<int>();
		if (k > input.size() || k <= 0)
			return vector<int>();

		multiset<int, intComp> minSave;
		for (auto &s : input)
		{
			if (minSave.size() < k)
				minSave.insert(s);
			else
			{
				if (*(minSave.begin()) > s)
				{
					minSave.erase(*(minSave.begin()));
					minSave.insert(s);
				}
			}
		}

		vector<int> tmp;
		for (auto iter = --minSave.end(); iter != minSave.begin(); iter--)
			tmp.push_back(*iter);
		tmp.push_back(*(minSave.begin()));
		return tmp;
	}
};

// ====================���Դ���====================
static void Test(char* testName, int* data, int n, int* expectedResult, int k)
{
	if (testName != nullptr)
		printf("%s begins: \n", testName);

	vector<int> vectorData;
	for (int i = 0; i < n; ++i)
		vectorData.push_back(data[i]);

	if (expectedResult == nullptr)
		printf("The input is invalid, we don't expect any result.\n");
	else
	{
		printf("Expected result: \n");
		for (int i = 0; i < k; ++i)
			printf("%d\t", expectedResult[i]);
		printf("\n");
	}

	printf("Result for solution1:\n");
	Solution s;
	vector<int> a = s.GetLeastNumbers_Solution3(vectorData, k);
	if (expectedResult != nullptr)
	{
		for (int i = 0; i < a.size(); ++i)
			printf("%d\t", a[i]);
		printf("\n");
	}
}

// kС������ĳ���
static void Test1()
{
	int data[] = { 4, 5, 1, 6, 2, 7, 3, 8 };
	int expected[] = { 1, 2, 3, 4 };
	Test("Test1", data, sizeof(data) / sizeof(int), expected, sizeof(expected) / sizeof(int));
}

// k��������ĳ���
static void Test2()
{
	int data[] = { 4, 5, 1, 6, 2, 7, 3, 8 };
	int expected[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
	Test("Test2", data, sizeof(data) / sizeof(int), expected, sizeof(expected) / sizeof(int));
}

// k��������ĳ���
static void Test3()
{
	int data[] = { 4, 5, 1, 6, 2, 7, 3, 8 };
	int* expected = nullptr;
	Test("Test3", data, sizeof(data) / sizeof(int), expected, 10);
}

// k����1
static void Test4()
{
	int data[] = { 4, 5, 1, 6, 2, 7, 3, 8 };
	int expected[] = { 1 };
	Test("Test4", data, sizeof(data) / sizeof(int), expected, sizeof(expected) / sizeof(int));
}

// k����0
static void Test5()
{
	int data[] = { 4, 5, 1, 6, 2, 7, 3, 8 };
	int* expected = nullptr;
	Test("Test5", data, sizeof(data) / sizeof(int), expected, 0);
}

// ����������ͬ������
static void Test6()
{
	int data[] = { 4, 5, 1, 6, 2, 7, 2, 8 };
	int expected[] = { 1, 2 };
	Test("Test6", data, sizeof(data) / sizeof(int), expected, sizeof(expected) / sizeof(int));
}

// �����ָ��
static void Test7()
{
	int* expected = nullptr;
	Test("Test7", nullptr, 0, expected, 0);
}

int main_offer40(int argc, char* argv[])
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	Test6();
	//Test7();

	return 0;
}