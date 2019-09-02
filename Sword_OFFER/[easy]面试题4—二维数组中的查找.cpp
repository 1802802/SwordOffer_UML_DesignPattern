#include <iostream>
#include <vector>
using namespace std;

//方法就一种，书上的方法：从右上角开始搜索，其小于target就删行，大于target就删列
//删行原因：一行中最大的数都小于target，删列原因：一列中最小的数都大于target
//如何通过vector结构来确定题目中的行和列大小
//牛客网时间12ms，内存1628K
bool Find(int target, vector<vector<int>> array) 
{
	//1.计算得到二维数组的rows和columns，并赋予右上角的初始值
	int rows = array.size();
	int columns = array[0].size();
	int row = 0;
	int column = columns - 1;

	//2.不断地选取右上角数据
	while (row < rows && column >= 0)
	{
		if (target > array[row][column])
		{
			row++;
			continue;
		}
		if (target < array[row][column])
		{
			column--;
			continue;
		}
		if (target == array[row][column])
			return true;
	}
	return false;
}