// ������48��������ظ��ַ������ַ���
// ��Ŀ������ַ������ҳ�һ����Ĳ������ظ��ַ������ַ�������������
// �ַ����ĳ��ȡ������ַ�����ֻ������'a'��'z'���ַ���

#include <queue>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

//1.����̰���㷨������ÿ���ַ�λ�õ���ѳ��ȣ����洢��ǰ����󳤶�ֱ������
//�����⣬��Ϊ��ʱ����ĳ��ȵ���ʼλ�����ڳ�ʼλ������������ͬ�����м����
//������������⣬��Ҫ���ýضϵķ�ʽ������������ͬʱ�ж���ͬ��λ�þ��룬������ڵ�ǰ�����������ӣ�С�ڵ�ǰ��������ضϣ�
int longestSubstringWithoutDuplication_1(const string& str)
{
	int Length = 0;
	int maxLength = 0;
	string save;
	for (int i = 0; i < str.size(); i++)
	{
		if (save.find(str[i]) == -1)
		{
			save.push_back(str[i]);
			Length++;
		}
		else
		{
			save.clear();
			save.push_back(str[i]);
			maxLength = max(maxLength, Length);
			Length = 1;
		}
	}
	maxLength = max(maxLength, Length);
	return maxLength;
}

//2.ʹ�ö�̬�滮�����м���ضϵ��жϲ���������һ��26λ����������ŵ�ǰ�ַ���λ�ã�Ĭ�Ͼ�Ϊ-1��
//��ʽ���£�
//����ǰ�ַ�δ���֣���f(i)=f(i-1)+1������ǰ�ַ����֣������d<=f(i-1)��f(i)=d����d>=f(i-1)��f(i)=f(i-1)+1
int longestSubstringWithoutDuplication_2(const string& str)
{
	int longestPath = 0;
	//charPlace���ڴ洢��Ӧ���ַ��ĳ���λ�ã�bestSave�洢ÿ��λ�õ��ַ���������ַ�������
	vector<int> charPlace(26, -1);
	vector<int> bestSave(str.size() + 1, 0);
	for (int i = 0; i < str.size(); i++)
	{
		int currentChar = str[i] - 'a';
		if (charPlace[currentChar] == -1)
		{
			charPlace[currentChar] = i;
			if (i != 0)
				bestSave[i] = bestSave[i - 1] + 1;
			else
				bestSave[i] = 1;
		}
		else
		{
			int lastPlace = charPlace[currentChar];
			charPlace[currentChar] = i;
			int distance = i - lastPlace; 
			//���������ظ��ļ��������������һλ֮�䣨������ͷ�����ض���������ǰf(i)��Ϊdistance
			//������ǣ��򽫵�ǰf(i)��������
			if (distance <= bestSave[i - 1])
				bestSave[i] = distance;
			else
				bestSave[i] = bestSave[i - 1] + 1;
		}
		//ÿ�μ����굱ǰ����ַ����󣬼�¼����
		longestPath = max(longestPath, bestSave[i]);
	}
	return longestPath;
}

// ====================���Դ���====================
static void testSolution1(const std::string& input, int expected)
{
	int output = longestSubstringWithoutDuplication_1(input);
	if (output == expected)
		std::cout << "Solution 1 passed, with input: " << input << std::endl;
	else
		std::cout << "Solution 1 FAILED, with input: " << input << std::endl;
}

static void testSolution2(const std::string& input, int expected)
{
	int output = longestSubstringWithoutDuplication_2(input);
	if (output == expected)
		std::cout << "Solution 2 passed, with input: " << input << std::endl;
	else
		std::cout << "Solution 2 FAILED, with input: " << input << std::endl;
}

static void test(const std::string& input, int expected)
{
	testSolution1(input, expected);
	testSolution2(input, expected);
}

static void test1()
{
	const std::string input = "abcacfrar";
	int expected = 4;
	test(input, expected);
}

static void test2()
{
	const std::string input = "acfrarabc";
	int expected = 4;
	test(input, expected);
}

static void test3()
{
	const std::string input = "arabcacfr";
	int expected = 4;
	test(input, expected);
}

static void test4()
{
	const std::string input = "aaaa";
	int expected = 1;
	test(input, expected);
}

static void test5()
{
	const std::string input = "abcdefg";
	int expected = 7;
	test(input, expected);
}

static void test6()
{
	const std::string input = "aaabbbccc";
	int expected = 2;
	test(input, expected);
}

static void test7()
{
	const std::string input = "abcdcba";
	int expected = 4;
	test(input, expected);
}

static void test8()
{
	const std::string input = "abcdaef";
	int expected = 6;
	test(input, expected);
}

static void test9()
{
	const std::string input = "a";
	int expected = 1;
	test(input, expected);
}

static void test10()
{
	const std::string input = "";
	int expected = 0;
	test(input, expected);
}

int main_offer48(int argc, char* argv[])
{
	test1();
	test2();
	test3();
	test4();
	test5();
	test6();
	test7();
	test8();
	test9();
	test10();

	return 0;
}