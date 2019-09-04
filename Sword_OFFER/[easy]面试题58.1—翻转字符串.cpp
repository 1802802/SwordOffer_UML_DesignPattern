// ������58.1����ת����˳��
// ��Ŀ������һ��Ӣ�ľ��ӣ���ת�����е��ʵ�˳�򣬵��������ַ���˳�򲻱䡣
// Ϊ������������ź���ͨ��ĸһ���������������ַ���"I am a student. "��
// �����"student. a am I"��

#include <map>
#include <unordered_map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
#include "BinaryTree.h"
using namespace std;

//˼·�������ַ����ķ�ת���޷������ַ�ʽ�������巭ת���پֲ���ת���Ⱦֲ���ת�������巭ת
//����ʱ�䣺3ms��ռ���ڴ棺476k
class Solution 
{
public:
	string ReverseSentence1(string &str)
	{
		for (int i = 0, j = 0; i < str.size();)
		{
			for (; j < str.size(); j++)
			{
				if (str[j] == ' ')
					break;
			}
			rotate(str, i, j - 1);
			i = ++j;
		}
		rotate(str, 0, str.size() - 1);
		return str;
	}

	void rotate(string &str, int lo, int hi)
	{
		while (lo < hi)
			swap(str[lo++], str[hi--]);
	}

	string ReverseSentence(string& str) 
	{
		if (str.size() <= 0)
			return str;
		//1.�����巭ת
		Reverse(str, 0, str.size());
		//2.�ٸ��ݿո�λ������ÿ�����ʵľֲ���ת
		for (int i = 0, j = 0; i < str.size();)
		{
			//2.1�ҵ��¸��ո��λ�ã�ֱ���ҵ����ߵ�ͷ
			for (; j < str.size(); j++)
			{
				if (str[j] == ' ')
					break;
			}
			//2.2�ֲ���ת
			Reverse(str, i, j);
			i = ++j;
		}
		return str;
	}

	//˼·2���Ⱦֲ���ת�������巭ת��Ч��һ��
	string ReverseSentence2(string& str)
	{
		if (str.size() <= 0)
			return str;
		//1.���ݿո�λ������ÿ�����ʵľֲ���ת
		for (int i = 0, j = 0; i < str.size();)
		{
			//2.1�ҵ��¸��ո��λ�ã�ֱ���ҵ����ߵ�ͷ
			for (; j < str.size(); j++)
			{
				if (str[j] == ' ')
					break;
			}
			//2.2�ֲ���ת
			Reverse(str, i, j);
			i = ++j;
		}
		//2.�����巭ת
		Reverse(str, 0, str.size());
		return str;
	}

	void Reverse(string& str, int i ,int j)
	{
		while (i < j)
		{
			swap(str[i], str[j - 1]);
			i++; j--;
		}
	}
};

// ====================���Դ���====================
static void Test(const char* testName, string input, string expectedResult)
{
	if (testName != nullptr)
		printf("%s begins: \n", testName);

	Solution s;
	cout << s.ReverseSentence1(input) << endl;
	cout << expectedResult << endl;

	if ((input.empty() && expectedResult.empty())
		|| (!input.empty() && input == expectedResult))
		printf("Passed.\n\n");
	else
		printf("Failed.\n\n");
}

// ���ܲ��ԣ��������ж������
static void Test1()
{
	string input = "   I am  a student.";
	string expected = "student. a  am I   ";

	Test("Test1", input, expected);
}

// ���ܲ��ԣ�������ֻ��һ������
static void Test2()
{
	string input = "Wonderful";
	string expected = "Wonderful";

	Test("Test2", input, expected);
}

// ³���Բ���
static void Test3()
{
	Test("Test3", string(), string());
}

// �߽�ֵ���ԣ����Կ��ַ���
static void Test4()
{
	Test("Test4", "", "");
}

// �߽�ֵ���ԣ��ַ�����ֻ�пո�
static void Test5()
{
	string input = "   ";
	string expected = "   ";
	Test("Test5", input, expected);
}

int main_offer58_1(int argc, char* argv[])
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();

	return 0;
}