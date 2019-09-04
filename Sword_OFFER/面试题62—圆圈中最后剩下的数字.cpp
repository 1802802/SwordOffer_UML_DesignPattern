// ������62��ԲȦ�����ʣ�µ�����
// ��Ŀ��0, 1, ��, n-1��n�������ų�һ��ԲȦ��������0��ʼÿ�δ����ԲȦ��
// ɾ����m�����֡�������ԲȦ��ʣ�µ����һ�����֡�

#include <map>
#include <deque>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <list>
#include "BinaryTree.h"
using namespace std;

class Solution 
{
public:

	//1.˼·��ʹ�û���������ģ��ԲȦ������ʹ�ö�̬�滮Ѱ�ҹ���
	//����ʱ�䣺29ms��ռ���ڴ棺732k����ʱ�ϴ󣬶���n�ϴ��ʱ��
	int LastRemaining_Solution(int n, int m)
	{
		if (n <= 0 || m <= 0)
			return -1;
		list<int> save;
		for (int i = 0; i < n; i++)
			save.push_back(i);
		list<int>::iterator beg = save.begin();
		while (save.size() > 1)
		{
			//1.1�ӻ��������ǰ��m��
			for (int i = 1; i < m; i++)
			{
				beg++;
				if (beg == save.end())
					beg = save.begin();
			}
			//1.2ɾ����m��λ�õĵ㣬Ȼ��beg��������Ϊ��ɾ��λ�õ���һλ��
			beg = save.erase(beg);
			if (beg == save.end())
				beg = save.begin();
		}
		return *beg;
	}

	//2.�ҵ���ѧ���ɺ�ĵݹ�f(n,m) = [f(n-1, m)] + m] % n������ n = 1ʱ��ֻ��һ�����֣����Ϊ0
	//����f(n,m)��ʾ����n������m��ʱ����ɾ�������ֵ���һλ���֣�����󱻱�������λ���֣�
	int LastRemaining_Solution2(int n, int m)
	{
		if (n <= 0 || m <= 0)
			return -1;
		if (n == 1)
			return 0;
		int first = 0;
		for (int i = 2; i <= n; i++)
			first = (first + m) % i;
		return first;
	}

};

// ====================���Դ���====================
static void Test(const char* testName, unsigned int n, unsigned int m, int expected)
{
	if (testName != nullptr)
		printf("%s begins: \n", testName);

	Solution s;
	if (s.LastRemaining_Solution2(n, m) == expected)
		printf("Solution1 passed.\n");
	else
		printf("Solution1 failed.\n");

	//if (LastRemaining_Solution2(n, m) == expected)
	//	printf("Solution2 passed.\n");
	//else
	//	printf("Solution2 failed.\n");

	printf("\n");
}

static void Test1()
{
	Test("Test1", 5, 3, 3);
}

static void Test2()
{
	Test("Test2", 5, 2, 2);
}

static void Test3()
{
	Test("Test3", 6, 7, 4);
}

static void Test4()
{
	Test("Test4", 6, 6, 3);
}

static void Test5()
{
	Test("Test5", 0, 0, -1);
}

static void Test6()
{
	Test("Test6", 4000, 997, 1027);
}

int main(int argc, char* argv[])
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	Test6();

	//list<int> save({ 1,2,3,6,5,7,1,2,4 });
	//auto s0 = save.begin();
	////list�ĵ�����������+1������vector�Ŀ���(++ǰ��׺������ʹ�ã�
	//list<int>::iterator s2 = ++save.begin();
	//auto s1 = save.erase(s0);

	//vector<int> save({ 1,2,3,6,5,7,1,2,4 });
	//auto s0 = save.begin();
	////list�ĵ�����������+1������vector�Ŀ���(++ǰ��׺������ʹ�ã�
	//vector<int>::iterator s2 = ++(++save.begin());
	//auto s1 = save.erase(s0);
	//auto s3 = s1 + 1;

	//cout << *s1 << endl;
	////cout << *s2 << endl;
	//cout << *s3 << endl;

	//map<int, int> save{ { 1,2 }, { 3,3 }, { 5,5 } };
	//auto beg = save.begin();
	//save.insert({ 2,2 });
	//auto s1 = (++save.begin());
	//cout << beg->first << " " << beg->second << endl;
	//cout << s1->first << " " << s1->second << endl;

	//vector<int> save({ 1,2,3 });
	//int *p = &save[1];
	//cout << p << " " << *p << endl;
	//save.insert(save.begin(), 6);
	//cout << p << " " << *p << endl;
	
	return 0;
}