#ifndef offer13
#define offer13

#include <iostream>
using namespace std;

//仍然是经典的递归解法，在递归中回溯，牛客网运行时间：4ms，占用内存：472k
class Solution 
{
public:
	//思想：试探回溯，函数分块实现
	int movingCount(int threshold, int rows, int cols)
	{
		if (threshold < 0 || rows < 0 || cols < 0)
			return 0;
		bool* isVisited = new bool[rows*cols];
		memset(isVisited, false, rows*cols);
		int count = movingCountByPoint(threshold, rows, cols, 0, 0, isVisited);

		delete[] isVisited;
		return count;
	}

	int movingCountByPoint(int threshold, int rows, int cols, int row, int col, bool* isVisited)
	{
		int count = 0;
		//如果判断能够对应的输入数值能够满足check条件（即能够进入此位置）
		if (check(threshold, rows, cols, row, col, isVisited))
		{
			//将对应的位置置为true，然后开始进行上下左右的试探与回溯，返回计数值（进入此位置的默认1+探测值）
			isVisited[row*cols + col] = true;
			count = 1 + movingCountByPoint(threshold, rows, cols, row + 1, col, isVisited)
				+ movingCountByPoint(threshold, rows, cols, row - 1, col, isVisited)
				+ movingCountByPoint(threshold, rows, cols, row, col + 1, isVisited)
				+ movingCountByPoint(threshold, rows, cols, row, col - 1, isVisited);
		}
		return count;
	}

	bool check(int threshold, int rows, int cols, int row, int col, bool* isVisited)
	{
		//前置条件判断，包括其数据正确性与是否被访问
		if (row >= 0 && row < rows && col >= 0 && col < cols && !isVisited[row*cols + col])
		{
			int sum = 0;
			while (row)
			{
				sum += row % 10;
				row /= 10;
			}
			while (col)
			{
				sum += col % 10;
				col /= 10;
			}
			return (sum <= threshold);
		}
		return false;
	}
};

// ====================测试代码====================
static void test(char* testName, int threshold, int rows, int cols, int expected)
{
	Solution s;
	if (testName != nullptr)
		printf("%s begins: ", testName);

	if (s.movingCount(threshold, rows, cols) == expected)
		printf("Passed.\n");
	else
		printf("FAILED.\n");
}

// 方格多行多列
static void test1()
{
	test("Test1", 5, 10, 10, 21);
}

// 方格多行多列
static void test2()
{
	test("Test2", 15, 20, 20, 359);
}

// 方格只有一行，机器人只能到达部分方格
static void test3()
{
	test("Test3", 10, 1, 100, 29);
}

// 方格只有一行，机器人能到达所有方格
static void test4()
{
	test("Test4", 10, 1, 10, 10);
}

// 方格只有一列，机器人只能到达部分方格
static void test5()
{
	test("Test5", 15, 100, 1, 79);
}

// 方格只有一列，机器人能到达所有方格
static void test6()
{
	test("Test6", 15, 10, 1, 10);
}

// 方格只有一行一列
static void test7()
{
	test("Test7", 15, 1, 1, 1);
}

// 方格只有一行一列
static void test8()
{
	test("Test8", 0, 1, 1, 1);
}

// 机器人不能进入任意一个方格
static void test9()
{
	test("Test9", -10, 10, 10, 0);
}

class Test
{
public:
	Test(){}
	Test(const Test& t)
	{
		a = t.a;
	}
	int a;
};

int main_offer13(int agrc, char* argv[])
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

	Test t1;
	t1.a = 2;
	cout << &t1.a << " " << sizeof(t1) << endl;
	Test t2(t1);
	cout << &t2.a << " " << sizeof(t2) << endl;
	return 0;
}

#endif