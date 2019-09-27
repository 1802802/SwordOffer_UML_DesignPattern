#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int nextArr[4][2] = { 1,0,-1,0,0,1,0,-1 };

int findPath(vector<vector<int>> &f, vector<vector<int>> &matrix, int &rows, int &cols, int x, int y)
{
	if (f[x][y] != -1)
		return f[x][y];
	f[x][y] = 1;
	for (int i = 0; i < 4; i++)
	{
		//a和b是移动后的x与y的位置
		int a = x + nextArr[i][0];
		int b = y + nextArr[i][1];
		if (a >= 0 && a < rows && b >= 0 && b < cols && matrix[a][b] < matrix[x][y])
			f[x][y] = max(f[x][y], 1 + findPath(f, matrix, rows, cols, a, b));
	}
	return f[x][y];
}

int main()
{
	vector<vector<int>> matrix;
	matrix.push_back({ 9,9,6 });
	matrix.push_back({ 1,2,5 });
	matrix.push_back({ 6,1,3 });
	int rows = matrix.size();
	int cols = matrix[0].size();
	int result = 0;
	vector<vector<int>> f(rows, vector<int>(cols, -1));
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
			result = max(result, findPath(f, matrix, rows, cols, i, j));
	}
	cout << result << endl;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
			cout << f[i][j] << " ";
		cout << endl;
	}
	return 0;
}