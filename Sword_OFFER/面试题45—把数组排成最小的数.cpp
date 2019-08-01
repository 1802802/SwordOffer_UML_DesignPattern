// ������45���������ų���С����
// ��Ŀ������һ�����������飬����������������ƴ�������ų�һ��������ӡ��ƴ�ӳ���������������С��һ����
// ������������{3��32��321}�����ӡ���������������ųɵ���С����Ϊ321323��

#include <queue>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

class Solution 
{
public:
	//˼·����vector�е���������Ϊ�ַ�����Ȼ��������Ϊ��С�ļ��ɣ�����Ҫ�Զ���һ�±ȽϺ�����
	string PrintMinNumber(vector<int> numbers) 
	{
		string input = "";
		if (numbers.size() < 1)
			return input;
		vector<string> save;
		for (auto &s : numbers)
			save.push_back(to_string(s));
		sort(save.begin(), save.end(), compareString);
		for (auto &s : save)
			input.append(s.begin(), s.end());
		return input;
	}

	static bool compareString(const string& a, const string& b)
	{
		string tma = a;
		tma.append(b.begin(), b.end());
		string tmb = b;
		tmb.append(a.begin(), a.end());
		for (int i = 0; i < tma.size(); i++)
		{
			if (tma[i] > b[i])
				return a > b;
			else if (tma[i] < b[i])
				return a < b;
		}
		return a > b;
	}

	static bool CompareString(const string& a, const string& b)
	{	
		if (a.size() >= b.size())
		{
			int maxSize = a.size();
			int minSize = b.size();
			for (int i = 0; i < minSize; i++)
			{
				if (a[i] > b[i])
					return a > b;
				else if (a[i] < b[i])
					return a < b;
			}
			for (int i = minSize, j = 0; i < maxSize; i++, j++)
			{
				if (a[i] > b[j])
					return a > b;
				else if (a[i] < b[j])
					return a < b;
			}
			return a > b;
		}
		else
		{
			int maxSize = b.size();
			int minSize = a.size();
			for (int i = 0; i < minSize; i++)
			{
				if (a[i] > b[i])
					return a > b;
				else if (a[i] < b[i])
					return a < b;
			}
			for (int i = minSize, j = 0; i < maxSize; i++, j++)
			{
				if (a[j] > b[i])
					return a > b;
				else if (a[j] < b[i])
					return a < b;
			}
		}
		return a > b;
	}
};

// ====================���Դ���====================
static void Test(const char* testName, vector<int> numbers, int length, const char* expectedResult)
{
	if (testName != nullptr)
		printf("%s begins:\n", testName);

	if (expectedResult != nullptr)
		printf("Expected result is: \t%s\n", expectedResult);

	Solution s;
	printf("Actual result is: \t");
	cout<< s.PrintMinNumber(numbers);

	printf("\n");
}

static void Test1()
{
	vector<int> numbers = { 3, 5, 1, 4, 2 };
	Test("Test1", numbers, sizeof(numbers) / sizeof(int), "12345");
}

static void Test2()
{
	vector<int> numbers = { 3, 32, 321 };
	Test("Test2", numbers, sizeof(numbers) / sizeof(int), "321323");
}

static void Test3()
{
	vector<int> numbers = { 3, 323, 32123 };
	Test("Test3", numbers, sizeof(numbers) / sizeof(int), "321233233");
}

static void Test4()
{
	vector<int> numbers = { 1, 11, 111 };
	Test("Test4", numbers, sizeof(numbers) / sizeof(int), "111111");
}

// ������ֻ��һ������
static void Test5()
{
	vector<int> numbers = { 321 };
	Test("Test5", numbers, sizeof(numbers) / sizeof(int), "321");
}

static void Test6()
{
	Test("Test6", vector<int>(), 0, "Don't print anything.");
}


int main(int argc, char* argv[])
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	Test6();

	return 0;
}