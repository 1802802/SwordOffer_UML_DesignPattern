// ������47�����������ֵ
// ��Ŀ����һ��m��n�����̵�ÿһ�񶼷���һ�����ÿ�����ﶼ��һ���ļ�ֵ
// ����ֵ����0��������Դ����̵����Ͻǿ�ʼ�ø�����������ÿ�������
// �������ƶ�һ��ֱ���������̵����½ǡ�����һ�����̼��������������
// ����������õ����ټ�ֵ�����

#include <queue>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

//1.��̬�滮������������������λ�õ����״̬
int getMaxValue_solution1(const int* values, int rows, int cols)
{
	//1.1�߽�����
	if (values == nullptr || rows < 0 || cols < 0)
		return 0;
	//1.2���ݴ洢����ά����
	vector<vector<int> > save(rows, vector<int>(cols, 0));
	//1.3���ݴ�����������λ�ö���һ��
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

//2.̰�ģ�ÿһ��ֻȡ��ǰ���Ž⣨��DP�ܽӽ������ǵ�����������ͬʱ�����ܻ�����⣩
int getMaxValue_solution2(const int* values, int rows, int cols)
{
	//1.1�߽�����
	if (values == nullptr || rows < 0 || cols < 0)
		return 0;
	//1.2���ݴ洢����ά����
	vector<vector<int> > save(rows, vector<int>(cols, 0));
	//1.3���ݴ���ֻȡ��ǰ��ѣ��������������ͬʱ������������Ե��½�������⣩
	int row = 0; int col = 0; int maxSum = values[0];
	while (row < rows - 1 || col < cols - 1)
	{
		int moveRight = 0;
		int moveDown = 0;

		//��ĳһ����ʻ·���������ֵ���򲻼����Ǹ����������
		if (row < rows - 1)
			moveDown = values[(row + 1) * cols + col];

		if (col < cols - 1)
			moveRight = values[row * cols + col + 1];

		if (moveRight >= moveDown)
		{
			maxSum += moveRight;
			//��col���������ֵ
			if (col < cols - 1)
				col++;
		}
		else
		{
			maxSum += moveDown;
			//��row���������ֵ
			if (row < rows - 1)
				row++;
		}
	}
	return maxSum;
}

// ====================���Դ���====================
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
	// ��������
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
	//��������
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
	// һ������
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
	// һ��һ��
	int values[][1] = {
		{ 3 }
	};
	int expected = 3;
	test("test5", (const int*)values, 1, 1, expected);
}

static void test6()
{
	// ��ָ��
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