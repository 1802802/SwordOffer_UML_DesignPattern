// 面试题47—礼物的最大价值
// 题目：在一个m×n的棋盘的每一格都放有一个礼物，每个礼物都有一定的价值
// （价值大于0）。你可以从棋盘的左上角开始拿格子里的礼物，并每次向左或
// 者向下移动一格直到到达棋盘的右下角。给定一个棋盘及其上面的礼物，请计
// 算你最多能拿到多少价值的礼物？

#include <queue>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

//1.动态规划，算出礼物格子中所有位置的最佳状态
int getMaxValue_solution1(const int* values, int rows, int cols)
{
	//1.1边界条件
	if (values == nullptr || rows < 0 || cols < 0)
		return 0;
	//1.2数据存储，二维数组
	vector<vector<int> > save(rows, vector<int>(cols, 0));
	//1.3数据处理，所有礼物位置都算一遍
	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < cols; col++)
		{
			int lastUp = (row == 0) ? 0 : save[row - 1][col];
			int lastLeft = (col == 0) ? 0 : save[row][col - 1];
			save[row][col] = max(lastUp, lastLeft) + values[row*cols + col];
		}
	}
	for (auto &s1 : save)
	{
		for (auto &s2 : s1)
		{
			cout << s2 << " ";
		}
		cout << endl;
	}
	return save[rows - 1][cols - 1];
}

//2.贪心，每一步只取当前最优解（和DP很接近，但是当出现右左相同时，可能会出问题）
int getMaxValue_solution2(const int* values, int rows, int cols)
{
	//1.1边界条件
	if (values == nullptr || rows < 0 || cols < 0)
		return 0;
	//1.2数据存储，二维数组
	vector<vector<int> > save(rows, vector<int>(cols, 0));
	//1.3数据处理，只取当前最佳（如果右下两个相同时，会产生二义性导致结果出问题）
	int row = 0; int col = 0; int maxSum = values[0];
	while (row < rows - 1 || col < cols - 1)
	{
		int moveRight = 0;
		int moveDown = 0;

		//当某一种行驶路径到达最大值后，则不计算那个方向的数据
		if (row < rows - 1)
			moveDown = values[(row + 1) * cols + col];

		if (col < cols - 1)
			moveRight = values[row * cols + col + 1];

		if (moveRight >= moveDown)
		{
			maxSum += moveRight;
			//将col限制在最大值
			if (col < cols - 1)
				col++;
		}
		else
		{
			maxSum += moveDown;
			//将row限制在最大值
			if (row < rows - 1)
				row++;
		}
	}
	return maxSum;
}

// ====================测试代码====================
static void test(const char* testName, const int* values, int rows, int cols, int expected)
{
	if (getMaxValue_solution1(values, rows, cols) == expected)
		std::cout << testName << ": solution1 passed." << std::endl;
	else
		std::cout << testName << ": solution1 FAILED." << std::endl;

	if (getMaxValue_solution2(values, rows, cols) == expected)
		std::cout << testName << ": solution2 passed." << std::endl;
	else
		std::cout << testName << ": solution2 FAILED." << std::endl;
}

static void test1()
{
	// 三行三列
	int values[][3] = {
		{ 1, 2, 3 },
		{ 4, 5, 6 },
		{ 7, 8, 9 }
	};
	int expected = 29;
	test("test1", (const int*)values, 3, 3, expected);
}

static void test2()
{
	//四行四列
	int values[][4] = {
		{ 1, 10, 3, 8 },
		{ 12, 2, 9, 6 },
		{ 5, 7, 4, 11 },
		{ 3, 7, 16, 5 }
	};
	int expected = 53;
	test("test2", (const int*)values, 4, 4, expected);
}

static void test3()
{
	// 一行四列
	int values[][4] = {
		{ 1, 10, 3, 8 }
	};
	int expected = 22;
	test("test3", (const int*)values, 1, 4, expected);
}

static void test4()
{
	int values[4][1] = {
		{ 1 },
		{ 12 },
		{ 5 },
		{ 3 }
	};
	int expected = 21;
	test("test4", (const int*)values, 4, 1, expected);
}

static void test5()
{
	// 一行一列
	int values[][1] = {
		{ 3 }
	};
	int expected = 3;
	test("test5", (const int*)values, 1, 1, expected);
}

static void test6()
{
	// 空指针
	int expected = 0;
	test("test6", nullptr, 0, 0, expected);
}

int main_offer47(int argc, char* argv[])
{
	test1();
	test2();
	test3();
	test4();
	test5();

	return 0;
}