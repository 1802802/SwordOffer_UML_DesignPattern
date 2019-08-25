#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iterator>
using namespace std;

bool isHavePath(vector<vector<string>> &save, vector<vector<bool>> &isVisited, int &rows, int &cols, int row, int col)
{
	if (row == rows - 1 && col == cols - 1 && save[rows - 1][cols - 1] == "1")
	{
		isVisited[row][col] = true;
		return true;
	}
	bool result = false;
	if (row < rows && col < cols && row >= 0 && col >= 0 && save[row][col] == "1" && isVisited[row][col] == false)
	{
		isVisited[row][col] = true;
		result = isHavePath(save, isVisited, rows, cols, row + 1, col) || isHavePath(save, isVisited, rows, cols, row - 1, col)
			|| isHavePath(save, isVisited, rows, cols, row, col + 1) || isHavePath(save, isVisited, rows, cols, row, col - 1);
		if (!result)
			isVisited[row][col] = false;
	}
	return result;
}

int main()
{
	//1.数据处理
	string in;
	int rows, cols;
	ifstream input("input.txt");
	vector<vector<string>> save;
	vector<string> temp;
	while (input >> in)
	{
		if (in != "\\r\\n")
		{
			temp.push_back(in);
		}
		else
		{
			save.push_back(temp);
			cols = temp.size();
			temp.clear();
		}
	}
	rows = save.size();
	vector<vector<bool>> isVisited(rows, vector<bool>(cols, false));

	//2.找
	bool isFind = isHavePath(save, isVisited, rows, cols, 0, 0);

	//3.输出
	if (isFind)
	{
		cout << "已找到路径，并输出到了out.txt文件" << endl;
		ofstream out("out.txt");
		for (auto &s1 : isVisited)
		{
			for (auto &s2 : s1)
			{
				out << s2 << " ";
			}
			out << "\\r\\n" << endl;
		}
	}
	else
		cout << "未找到路径" << endl;

	return 0;
}