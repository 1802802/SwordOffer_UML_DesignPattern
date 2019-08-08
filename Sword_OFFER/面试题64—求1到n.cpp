// 面试题64：股票的最大利润
// 题目：求1+2+…+n，要求不能使用乘除法、for、while、if、else、switch、case
// 等关键字及条件判断语句（A?B:C）。

#include <map>
#include <deque>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <list>
#include "BinaryTree.h"
using namespace std;

//思路：这题就是花里胡哨，什么方法都可以试一试

class temp
{
private:
	static int n;
	static int sum;
public:
	temp() { ++n; sum += n; }
	static void initial() { n = 0; sum = 0; }
	static int getsum() { return sum; }
};

//注意static成员的类外初始化
int temp::n = 0;
int temp::sum = 0;

//方法1：利用构造函数
//运行时间：4ms，占用内存：476k
int Sum_Solution1(int n)
{
	temp::initial();
	temp* t = new temp[n];  //执行n次temp的构造函数
	delete[] t;
	t = nullptr;

	return temp::getsum();
}

//方法2：使用&&操作实现短路求值
//运行时间：3ms，占用内存：504k
int Sum_Solution2(int n)
{
	int ans = n;
	//递归的终止条件为最后n=0时的短路
	ans && (ans += Sum_Solution2(n - 1));
	return ans;
}

//方法3：通过数组（bool型为1）的大小实现n(n+1)/2的类似实现
//运行时间：4ms，占用内存：492k
int Sum_Solution3(int n)
{
	//VS不能使用，但是gcc里可以
	//bool temp[n][n + 1];
	//return (sizeof(temp) >> 1);
	return 0;
}

// ====================测试代码====================
static void Test(int n, int expected)
{
	printf("Test for %d begins:\n", n);

	if (Sum_Solution1(n) == expected)
		printf("Solution1 passed.\n");
	else
		printf("Solution1 failed.\n");

	if (Sum_Solution2(n) == expected)
		printf("Solution2 passed.\n");
	else
		printf("Solution2 failed.\n");

	if (Sum_Solution3(n) == expected)
		printf("Solution3 passed.\n");
	else
		printf("Solution3 failed.\n");
}

static void Test1()
{
	const unsigned int number = 1;
	int expected = 1;
	Test(number, expected);
	//if (Sum_Solution4<number>::N == expected)
	//	printf("Solution4 passed.\n");
	//else
	//	printf("Solution4 failed.\n");
}

static void Test2()
{
	const unsigned int number = 5;
	int expected = 15;
	Test(number, expected);
	//if (Sum_Solution4<number>::N == expected)
	//	printf("Solution4 passed.\n");
	//else
	//	printf("Solution4 failed.\n");
}

static void Test3()
{
	const unsigned int number = 10;
	int expected = 55;
	Test(number, expected);
	//if (Sum_Solution4<number>::N == expected)
	//	printf("Solution4 passed.\n");
	//else
	//	printf("Solution4 failed.\n");
}

static void Test4()
{
	const unsigned int number = 0;
	int expected = 0;
	Test(number, expected);
	//if (Sum_Solution4<number>::N == expected)
	//	printf("Solution4 passed.\n");
	//else
	//	printf("Solution4 failed.\n");
}

int main_offer64(int argc, char* argv[])
{
	Test1();
	Test2();
	Test3();
	Test4();

	return 0;
}