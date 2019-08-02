// 面试题45—把数组排成最小的数
// 题目：输入一个正整数数组，把数组里所有数字拼接起来排成一个数，打印能拼接出的所有数字中最小的一个。
// 例如输入数组{3，32，321}，则打印出这三个数字能排成的最小数字为321323。

#include <queue>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

class Solution 
{
public:
	//思路：将vector中的所有数变为字符串，然后将其排序为最小的即可（其中要自定义一下比较函数），运行时间：4ms，占用内存：480k

	//本题关键：自定义比较函数的实现：（注意返回的东西是true和false）（其中特别注意：comparator(x,x)必须返回false，因为此时a<b不成立而b<a也不成立）
	//自定义比较函数需要注意的有：不要用<=之类的符号,会导致comparator失效
	//C++关联容器的有序容器对元素关键字的类型有要求，元素关键字的类型必须定义了严格弱序（stick weak ordering） 
	//拿内置类型来说，C++都定义了 “<”操作符，这就是一个严格弱序，而“ <= ”就不是一个严格弱序

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

	//自定义比较函数需要注意的有：不要用<=之类的符号,会导致comparator失效
	//C++关联容器的有序容器对元素关键字的类型有要求，元素关键字的类型必须定义了严格弱序（stick weak ordering） 
	//拿内置类型来说，C++都定义了 “<”操作符，这就是一个严格弱序，而“ <= ”就不是一个严格弱序
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

// ====================测试代码====================
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

// 数组中只有一个数字
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