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
	//˼·����vector�е���������Ϊ�ַ�����Ȼ��������Ϊ��С�ļ��ɣ�����Ҫ�Զ���һ�±ȽϺ�����������ʱ�䣺4ms��ռ���ڴ棺480k

	//����ؼ����Զ���ȽϺ�����ʵ�֣���ע�ⷵ�صĶ�����true��false���������ر�ע�⣺comparator(x,x)���뷵��false����Ϊ��ʱa<b��������b<aҲ��������
	//�Զ���ȽϺ�����Ҫע����У���Ҫ��<=֮��ķ���,�ᵼ��comparatorʧЧ
	//C++��������������������Ԫ�عؼ��ֵ�������Ҫ��Ԫ�عؼ��ֵ����ͱ��붨�����ϸ�����stick weak ordering�� 
	//������������˵��C++�������� ��<���������������һ���ϸ����򣬶��� <= ���Ͳ���һ���ϸ�����

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

	//�Զ���ȽϺ�����Ҫע����У���Ҫ��<=֮��ķ���,�ᵼ��comparatorʧЧ
	//C++��������������������Ԫ�عؼ��ֵ�������Ҫ��Ԫ�عؼ��ֵ����ͱ��붨�����ϸ�����stick weak ordering�� 
	//������������˵��C++�������� ��<���������������һ���ϸ����򣬶��� <= ���Ͳ���һ���ϸ�����
	static bool compareString(const string& a, const string& b)
	{
		string tma = a + b;
		string tmb = b + a;
		if (tma == tmb)
			return false;
		for (int i = 0; i < tma.size(); i++)
		{
			if (tma[i] < tmb[i])
				return true;
			else if(tma[i] > tmb[i])
				return false;
		}
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


int main_offer45(int argc, char* argv[])
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	Test6();

	return 0;
}