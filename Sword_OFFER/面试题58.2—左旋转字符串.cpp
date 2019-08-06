// ������58.2������ת�ַ���
// ��Ŀ���ַ���������ת�����ǰ��ַ���ǰ������ɸ��ַ�ת�Ƶ��ַ�����β����
// �붨��һ������ʵ���ַ�������ת�����Ĺ��ܡ����������ַ���"abcdefg"����
// ��2���ú�������������ת2λ�õ��Ľ��"cdefgab"��

#include <map>
#include <unordered_map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
#include "BinaryTree.h"
using namespace std;

//�������ص����ڣ�����ת�ֲ���ǰnλ���n-1λ������������ת
//����ʱ�䣺3ms��ռ���ڴ棺476k
class Solution 
{
public:
	string LeftRotateString(string& str, int n) 
	{
		//�߽�������ʩ��
		if (str.size() <= 0 || str.size() < n)
			return string();

		Reverse(str, 0, n - 1);
		Reverse(str, n, str.size() - 1);
		Reverse(str, 0, str.size() - 1);
		return str;
	}

	static void Reverse(string& str, int i, int j)
	{
		while (i < j)
		{
			swap(str[i], str[j]);
			i++; j--;
		}
	}
};

// ====================���Դ���====================
static void Test(const char* testName, string input, int num ,string expectedResult)
{
	if (testName != nullptr)
		printf("%s begins: ", testName);

	Solution s;
	cout << s.LeftRotateString(input, num) << endl;

	if ((input.empty() && expectedResult.empty())
		|| (!input.empty() && input == expectedResult))
		printf("Passed.\n\n");
	else
		printf("Failed.\n\n");
}

// ���ܲ���
static void Test1()
{
	string input = "abcdefg";
	string expected = "cdefgab";

	Test("Test1", input, 2, expected);
}

// �߽�ֵ����
static void Test2()
{
	string input = "abcdefg";
	string expected = "bcdefga";

	Test("Test2", input, 1, expected);
}

// �߽�ֵ����
static void Test3()
{
	string input = "abcdefg";
	string expected = "gabcdef";

	Test("Test3", input, 6, expected);
}

// ³���Բ���
static void Test4()
{
	Test("Test4", string(), 6, string());
}

// ³���Բ���
static void Test5()
{
	string input = "abcdefg";
	string expected = "abcdefg";

	Test("Test5", input, 0, expected);
}

// ³���Բ���
static void Test6()
{
	string input = "abcdefg";
	string expected = "abcdefg";

	Test("Test6", input, 7, expected);
}

int main_offer58_2(int argc, char* argv[])
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	Test6();

	return 0;
}