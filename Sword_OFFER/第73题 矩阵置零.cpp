#include <iostream>
#include <list>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
using namespace std;

class Solutionleecode73
{
public:
	//1.暴力解法
	void setZeroes1(vector<vector<int>>& matrix)
	{
		if (matrix.empty())
			return;
		multimap<int, int> zero;
		int rows = matrix.size();
		int cols = matrix[0].size();
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				if (matrix[i][j] == 0)
					zero.insert({ i,j });
			}
		}
		for (auto &s : zero)
		{
			for (int i = 0; i < rows; i++)
				matrix[i][s.second] = 0;
			for (int j = 0; j < cols; j++)
				matrix[s.first][j] = 0;
		}
		return;
	}

	//2.遍历数组，每当扫描到0则将其所处行列的首元素置为0，然后遍历除首行列外的所有元素，根据首行列的数来置0（就地算法）
	void setZeroes2(vector<vector<int>>& matrix)
	{
		if (matrix.empty())
			return;
		bool zerocol = false;
		bool zerorow = false;
		int rows = matrix.size();
		int cols = matrix[0].size();
		//注意从第0行第1列开始
		for (int i = 0; i < rows; i++)
		{
			if (!zerocol && matrix[i][0] == 0)
				zerocol = true;
			for (int j = 1; j < cols; j++)
			{
				if (matrix[i][j] == 0)
				{
					matrix[i][0] = 0;
					matrix[0][j] = 0;
				}
			}
		}
		for (int i = 1; i < rows; i++)
		{
			for (int j = 1; j < cols; j++)
			{
				if (matrix[i][0] == 0 || matrix[0][j] == 0)
					matrix[i][j] = 0;
			}
		}
		if (matrix[0][0] == 0)
		{
			zerorow = true;
			zerocol = true;
		}
		if (zerorow)
		{
			for (int i = 0; i < cols; i++)
				matrix[0][i] = 0;
		}
		if (zerocol)
		{
			for (int i = 0; i < rows; i++)
				matrix[i][0] = 0;
		}
		return;
	}
	//3.自己的想法
	void setZeroes(vector<vector<int>>& matrix)
	{
		if (matrix.empty())
			return;
		bool zerocol = false;
		bool zerorow = false;
		int rows = matrix.size();
		int cols = matrix[0].size();

		//1.确定首行首列是否置0
		for (int i = 0; i < rows; i++)
		{
			if (matrix[i][0] == 0)
			{
				zerocol = true;
				break;
			}
		}

		for (int j = 0; j < cols; j++)
		{
			if (matrix[0][j] == 0)
			{
				zerorow = true;
				break;
			}
		}

		//2.遍历除首行首列外的数据，并将其在首行首列中做标志
		for (int i = 1; i < rows; i++)
		{
			for (int j = 1; j < cols; j++)
			{
				if (matrix[i][j] == 0)
				{
					matrix[i][0] = 0;
					matrix[0][j] = 0;
				}
			}
		}

		//3.根据首行首列的标志，对其他数据进行置0处理
		for (int i = 1; i < rows; i++)
		{
			for (int j = 1; j < cols; j++)
			{
				if (matrix[i][0] == 0 || matrix[0][j] == 0)
					matrix[i][j] = 0;
			}
		}

		//4.根据首行首列是否置0，进行操作
		if (zerorow)
		{
			for (int i = 0; i < cols; i++)
				matrix[0][i] = 0;
		}
		if (zerocol)
		{
			for (int i = 0; i < rows; i++)
				matrix[i][0] = 0;
		}
	}
};

int main_leecode73()
{
	Solutionleecode73 s;
	vector<vector<int>> matrix;
	matrix.push_back(vector<int>({ -4, 214748364, 6, -7, 0 }));
	matrix.push_back(vector<int>({ -8, 6, -8, -6, 0 }));
	matrix.push_back(vector<int>({ 2147483647, 2, -9, -6, -10 }));
	s.setZeroes(matrix);

	int past[27][2] = { 0 };

	return 0;
}