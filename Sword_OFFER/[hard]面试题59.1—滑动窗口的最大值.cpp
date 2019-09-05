// ������59.1���������ڵ����ֵ
// ��Ŀ������һ������ͻ������ڵĴ�С���ҳ����л�����������ֵ�����ֵ��
// ���磬�����������{2,3,4,2,6,2,5,1}���������ڵĴ�С3����ôһ������6���������ڣ�
// ���ǵ����ֵ�ֱ�Ϊ{4,4,6,6,6,5}�� �������{2,3,4,2,6,2,5,1}�Ļ�������������6����
// {[2,3,4],2,6,2,5,1}�� {2,[3,4,2],6,2,5,1}�� {2,3,[4,2,6],2,5,1}�� {2,3,4,[2,6,2],5,1}�� 
// {2,3,4,2,[6,2,5],1}�� {2,3,4,2,6,[2,5,1]}��

#include <map>
#include <deque>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
#include "BinaryTree.h"
using namespace std;

class Solution 
{
public:
	//1.����˼�룺�����㷨���������д��ڣ�����ÿ�����ڵ����ֵ��ʱ�临�Ӷ�O(nk)���ռ临�Ӷ�O(1)
	//����ʱ�䣺6ms��ռ���ڴ棺472k
	vector<int> maxInWindows(const vector<int>& num, unsigned int size)
	{
		//1.1�߽�����
		if (num.empty() || size <= 0 || size > num.size())
			return vector<int>();

		int head = 0;
		int end = size - 1;
		vector<int> save;
		while (end < num.size())
		{
			int maxNum = 0;
			for (int i = head; i <= end; i++)
				maxNum = max(maxNum, num[i]);
			save.push_back(maxNum);
			head++; end++;
		}
		return save;
	}

	//2.�߼�˼�룺ʹ��˫�˶���dequeʵ�ֲ�������ʹ��deque���洢���������е����ֵ�뱸ѡ���ֵ
	vector<int> maxInWindows2(const vector<int>& num, unsigned int size)
	{
		//�߽�����
		if (num.empty() || size <= 0 || size > num.size())
			return vector<int>();

		//vector�����ֵ��deque�浱ǰ�������ڣ���ͷ������Ϊ�洰�ڵ����ֵ�����±�ֵ
		//deque�е�ֵ�����׶�Ϊ���ֵ���������ֵΪ���εı�ѡ���ֵ����һλ����
		vector<int> maxnumSave;
		deque<int> indexSave;
		for (int i = 0; i < num.size(); i++)
		{
			//2.1 �����ǰ�������ڵ�ĩ��ֵС�ڵ�ǰ��Ҫ�����ֵ����ĩ��ֵ�Ƴ�����
			while (indexSave.size() && num[indexSave.back()] <= num[i])
				indexSave.pop_back();
			//2.2 �����ǰ�������ڵ��׶�С�ڴ��ڽ��ޣ����׶�ֵ�Ƴ����ڣ���Ϊ���ֵ��
			while (indexSave.size() && i - indexSave.front() + 1 > size)
				indexSave.pop_front();
			//2.3 ������Ҫ���������i����indexSave������ ��������ô����Ҫ�壬��С֮��Ƚϣ�
			indexSave.push_back(i);
			if (size && i + 1 >= size)//�����������׵�ַi���ڵ���sizeʱ�ſ�ʼд�봰�����ֵ
				maxnumSave.push_back(num[indexSave.front()]);
		}
		return maxnumSave;
	}

	//3.ʹ�����ȼ�����Ҳ����ʵ�֣������ڷ���1��
};

// ====================���Դ���====================
static void Test(const char* testName, const vector<int>& num, unsigned int size, const vector<int>& expected)
{
	if (testName != nullptr)
		printf("%s begins: ", testName);

	Solution s;
	vector<int> result = s.maxInWindows2(num, size);

	vector<int>::const_iterator iterResult = result.begin();
	vector<int>::const_iterator iterExpected = expected.begin();
	while (iterResult < result.end() && iterExpected < expected.end())
	{
		if (*iterResult != *iterExpected)
			break;

		++iterResult;
		++iterExpected;
	}

	if (iterResult == result.end() && iterExpected == expected.end())
		printf("Passed.\n");
	else
		printf("FAILED.\n");
}

static void Test1()
{
	int num[] = { 2, 3, 4, 2, 6, 2, 5, 1 };
	vector<int> vecNumbers(num, num + sizeof(num) / sizeof(int));

	int expected[] = { 4, 4, 6, 6, 6, 5 };
	vector<int> vecExpected(expected, expected + sizeof(expected) / sizeof(int));

	unsigned int size = 3;

	Test("Test1", vecNumbers, size, vecExpected);
}

static void Test2()
{
	int num[] = { 1, 3, -1, -3, 5, 3, 6, 7 };
	vector<int> vecNumbers(num, num + sizeof(num) / sizeof(int));

	int expected[] = { 3, 3, 5, 5, 6, 7 };
	vector<int> vecExpected(expected, expected + sizeof(expected) / sizeof(int));

	unsigned int size = 3;

	Test("Test2", vecNumbers, size, vecExpected);
}

// �������鵥������
static void Test3()
{
	int num[] = { 1, 3, 5, 7, 9, 11, 13, 15 };
	vector<int> vecNumbers(num, num + sizeof(num) / sizeof(int));

	int expected[] = { 7, 9, 11, 13, 15 };
	vector<int> vecExpected(expected, expected + sizeof(expected) / sizeof(int));

	unsigned int size = 4;

	Test("Test3", vecNumbers, size, vecExpected);
}

// �������鵥���ݼ�
static void Test4()
{
	int num[] = { 16, 14, 12, 10, 8, 6, 4 };
	vector<int> vecNumbers(num, num + sizeof(num) / sizeof(int));

	int expected[] = { 16, 14, 12 };
	vector<int> vecExpected(expected, expected + sizeof(expected) / sizeof(int));

	unsigned int size = 5;

	Test("Test4", vecNumbers, size, vecExpected);
}

// �������ڵĴ�СΪ1
static void Test5()
{
	int num[] = { 10, 14, 12, 11 };
	vector<int> vecNumbers(num, num + sizeof(num) / sizeof(int));

	int expected[] = { 10, 14, 12, 11 };
	vector<int> vecExpected(expected, expected + sizeof(expected) / sizeof(int));

	unsigned int size = 1;

	Test("Test5", vecNumbers, size, vecExpected);
}

// �������ڵĴ�С��������ĳ���
static void Test6()
{
	int num[] = { 10, 14, 12, 11 };
	vector<int> vecNumbers(num, num + sizeof(num) / sizeof(int));

	int expected[] = { 14 };
	vector<int> vecExpected(expected, expected + sizeof(expected) / sizeof(int));

	unsigned int size = 4;

	Test("Test6", vecNumbers, size, vecExpected);
}

// �������ڵĴ�СΪ0
static void Test7()
{
	int num[] = { 10, 14, 12, 11 };
	vector<int> vecNumbers(num, num + sizeof(num) / sizeof(int));

	vector<int> vecExpected;

	unsigned int size = 0;

	Test("Test7", vecNumbers, size, vecExpected);
}

// �������ڵĴ�С������������ĳ���
static void Test8()
{
	int num[] = { 10, 14, 12, 11 };
	vector<int> vecNumbers(num, num + sizeof(num) / sizeof(int));

	vector<int> vecExpected;

	unsigned int size = 5;

	Test("Test8", vecNumbers, size, vecExpected);
}

// ��������Ϊ��
static void Test9()
{
	vector<int> vecNumbers;
	vector<int> vecExpected;

	unsigned int size = 5;

	Test("Test9", vecNumbers, size, vecExpected);
}

int main_offer59_1(int argc, char* argv[])
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

	return 0;
}