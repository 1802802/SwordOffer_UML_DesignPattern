// 面试题62：圆圈中最后剩下的数字
// 题目：0, 1, …, n-1这n个数字排成一个圆圈，从数字0开始每次从这个圆圈里
// 删除第m个数字。求出这个圆圈里剩下的最后一个数字。

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

	//1.思路：使用环形链表来模拟圆圈，或者使用动态规划寻找规律
	//运行时间：29ms，占用内存：732k（耗时较大，对于n较大的时候）
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
			//1.1从环的起点向前走m步
			for (int i = 1; i < m; i++)
			{
				beg++;
				if (beg == save.end())
					beg = save.begin();
			}
			//1.2删除第m步位置的点，然后将beg迭代器变为被删除位置的下一位置
			beg = save.erase(beg);
			if (beg == save.end())
				beg = save.begin();
		}
		return *beg;
	}

	//2.找到数学规律后的递归f(n,m) = [f(n-1, m)] + m] % n，当你 n = 1时，只有一个数字，则必为0
	//其中f(n,m)表示，在n个数走m步时，被删除的数字的下一位数字（即最后被保留的那位数字）
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

// ====================测试代码====================
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
	////list的迭代器不能用+1，但是vector的可以(++前后缀都可以使用）
	//list<int>::iterator s2 = ++save.begin();
	//auto s1 = save.erase(s0);

	//vector<int> save({ 1,2,3,6,5,7,1,2,4 });
	//auto s0 = save.begin();
	////list的迭代器不能用+1，但是vector的可以(++前后缀都可以使用）
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