#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

//matrixΪ��ͼ�е�ÿ�������е�ս�����
int findPath(vector<vector<int>> &matrix)
{
	//1.f�ĳ�ʼ����Ϊ��֮����ڱȽϣ���ʼ��ΪINT_MAX
	vector<vector<int>> f(matrix.size(), vector<int>(matrix[0].size(), INT_MAX));
	int rows = matrix.size();
	int cols = matrix[0].size();
	//2.���յ���г�ʼ������Ҫ�Ǹ��ݸõ����ֵ���м���
	f[rows - 1][cols - 1] = max(1, 1 - matrix[rows - 1][cols - 1]);
	//3.���յ�������ܣ�ע����ڱ߽�Ĵ�����һ���ж����
	for (int i = rows - 1; i >= 0; i--)
	{
		for (int j = cols - 1; j >= 0; j--)
		{
			int lastLeft = (i + 1 < rows) ? (max(1, f[i + 1][j] - matrix[i][j])) : (f[i][j]);
			int	lastDown = (j + 1 < cols) ? (max(1, f[i][j + 1] - matrix[i][j])) : (f[i][j]);
			f[i][j] = min(lastLeft, lastDown);
		}
	}
	//4.����������ʾ����
	for (auto &s1 : f)
	{
		for (auto &s2 : s1)
			cout << s2 << " ";
		cout << endl;
	}
	
	return f[0][0];
}

int main_shengdoushi()
{
	vector<vector<int>> matrix;
	matrix.push_back(vector<int>({ -2,-3,3 }));
	matrix.push_back(vector<int>({ -5,-10,1 }));
	matrix.push_back(vector<int>({ 0,30,-5 }));
	cout << findPath(matrix) << endl;

	return 0;
}