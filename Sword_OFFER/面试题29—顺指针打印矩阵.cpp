// 面试题29—顺时针打印矩阵
// 题目：输入一个矩阵，按照从外向里以顺时针的顺序依次打印出每一个数字，
// 例如，如果输入如下4 X 4矩阵： 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 
// 则依次打印出数字1,2,3,4,8,12,16,15,14,13,9,5,6,7,11,10.

#include <iostream>
#include <vector>
using namespace std;

class Solution 
{
public:
	//运行时间：3ms，占用内存：504k

	/*思路：也是四矩阵法，不过每个矩阵自带循环，并且端点占据数目也不同，具体如下：
	为首行重要矩阵（第一次左右矩阵占据两个端点，第二次上下矩阵与第三次右左矩阵各占据一个端点，第四次下上矩阵不占据端点）
	看图可知，第一次的从左到右打印占据了两个端点，用来适应多种不同的情况可以顺利执行（针对m×n矩阵）。
	----
	|??|
	|??|
	---|
	
	而用于n×n矩阵的顺时针swap的矩阵划分如下：
	为风车四矩阵（四个矩阵各占据一个端点），适用于将矩阵进行顺时针或逆时针旋转之类的
	----|
	|--||
	||?||
	||--|
	|----
	*/
	//

	//问题变成了四种矩形存不存在的问题，若存在则进行相应操作（其中左右矩阵必定操作）
	//而顺指针旋转之类的问题是四矩形必定存在，需要做的是数据操作。
	vector<int> printMatrix(vector<vector<int> > matrix)
	{
		vector<int> save;
		if (matrix.empty())
			return save;

		//row_start为起始行号，row_end为最大行号，col_start为起始列号，col_end为最大列号	
		int row_start = 0, row_end = matrix.size() - 1;
		int col_start = 0, col_end = matrix[0].size() - 1;

		//进入循环的条件：起始行号小于最大行号且起始列号小于最大列号（每层循环就是一个圈）
		while (row_start <= row_end && col_start <= col_end)
		{
			//1.左右矩阵没有限制（占据两个端点，需要至少一行一列才存在，所以没有限制）
			for (int i = col_start; i <= col_end; i++)
				save.push_back(matrix[row_start][i]);
			//2.上下矩阵有行限制（需要至少两行一列才存在）
			if (row_start < row_end)
				for (int i = row_start + 1; i <= row_end; i++)
					save.push_back(matrix[i][col_end]);
			//3.右左矩阵有列限制和行限制（需要至少两行两列才存在）
			if (row_start < row_end && col_start < col_end)
				for (int i = col_end - 1; i >= col_start; i--)
					save.push_back(matrix[row_end][i]);
			//4.下上矩阵最特殊，没有端点，所以其需要考虑的行限制要更大一点，同时也有列限制（需要至少三行两列才存在）
			if (row_start < row_end - 1 && col_start < col_end)
				for (int i = row_end - 1; i > row_start; i--)
					save.push_back(matrix[i][col_start]);
			//在完成一圈操作后，起始点+1，最大点-1
			row_start++; row_end--; col_start++; col_end--;
		}

		return save;
	}
};

// ====================测试代码====================
void Test(int columns, int rows)
{
	printf("Test Begin: %d columns, %d rows.\n", columns, rows);

	if (columns < 1 || rows < 1)
		return;

	vector<vector<int> > numbers(rows);
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < columns; ++j)
		{
			numbers[i].push_back(i * columns + j + 1);
		}
	}
	Solution s;
	vector<int> tmp = s.printMatrix(numbers);
	for (auto &s1 : tmp)
	{
		cout << s1 << " ";
	}
	printf("\n");
}

int main(int argc, char* argv[])
{
	/*
	1
	*/
	Test(1, 1);

	/*
	1    2
	3    4
	*/
	Test(2, 2);

	/*
	1    2    3    4
	5    6    7    8
	9    10   11   12
	13   14   15   16
	*/
	Test(4, 4);

	/*
	1    2    3    4    5
	6    7    8    9    10
	11   12   13   14   15
	16   17   18   19   20
	21   22   23   24   25
	*/
	Test(5, 5);

	/*
	1
	2
	3
	4
	5
	*/
	Test(1, 5);

	/*
	1    2
	3    4
	5    6
	7    8
	9    10
	*/
	Test(2, 5);

	/*
	1    2    3
	4    5    6
	7    8    9
	10   11   12
	13   14   15
	*/
	Test(3, 5);

	/*
	1    2    3    4
	5    6    7    8
	9    10   11   12
	13   14   15   16
	17   18   19   20
	*/
	Test(4, 5);

	/*
	1    2    3    4    5
	*/
	Test(5, 1);

	/*
	1    2    3    4    5
	6    7    8    9    10
	*/
	Test(5, 2);

	/*
	1    2    3    4    5
	6    7    8    9    10
	11   12   13   14    15
	*/
	Test(5, 3);

	/*
	1    2    3    4    5
	6    7    8    9    10
	11   12   13   14   15
	16   17   18   19   20
	*/
	Test(5, 4);

	return 0;
}


//尝试的使用四矩阵法的方法，发现失败了，这种方法还是适用于对于顺指针的交换（而且是n×n的交换），而不是打印
//思路，分四步打印，矩阵的行数rows与列数columns会限制每一步的操作（尤其是最后一步）
//1.采用风车四矩形法
vector<int> printMatrixsssss(vector<vector<int> > matrix)
{
	vector<int> save;
	vector<int> save1;
	vector<int> save2;
	vector<int> save3;
	vector<int> save4;

	if (matrix.empty())
		return save;

	int rows = matrix.size();
	int columns = matrix[0].size();
	int lsize = columns - 1;
	int num = 0;

	//1.1循环外圈（实现范围内缩）
	for (int i = 0; i < rows >> 1; i++)
	{
		//1.2循环内圈（实现顺时针操作）
		for (int j = num; j < lsize; j++)
		{
			if (i >= 0 && j >= 0)
				save1.push_back(matrix[i][j]);
			if (j >= 0 && columns - i - 1 >= 0)
				save2.push_back(matrix[j][columns - i - 1]);
			if (rows - i - 1 >= 0 && columns - j - 1 >= 0)
				save3.push_back(matrix[rows - i - 1][columns - j - 1]);
			if (rows - j - 1 >= 0 && i >= 0)
				save4.push_back(matrix[rows - j - 1][i]);
		}
		save.insert(save.end(), save1.begin(), save1.end());
		save.insert(save.end(), save2.begin(), save2.end());
		save.insert(save.end(), save3.begin(), save3.end());
		save.insert(save.end(), save4.begin(), save4.end());
		save1.clear();
		save2.clear();
		save3.clear();
		save4.clear();
		lsize--;
		num++;
	}

	return save;
}