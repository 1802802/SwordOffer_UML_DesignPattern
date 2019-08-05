// 面试题57.1：和为s的两个数字
// 题目：输入一个递增排序的数组和一个数字S，在数组中查找两个数，使得他们的和正好是S，
// 如果有多对数字的和等于S，输出两个数的乘积最小的。

#include <map>
#include <unordered_map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
#include "BinaryTree.h"
using namespace std;

class Solution 
{
public:
	//双指针一前一后进行相加操作，大了则大指针前移，小了则小指针后移
	//运行时间：3ms，占用内存：480k
	vector<int> FindNumbersWithSum(vector<int> array, int sum) 
	{
		int head = 0;
		int end = array.size() - 1;
		while (head < end)
		{
			if (array[head] + array[end] < sum)
				head++;
			else if (array[head] + array[end] > sum)
				end--;
			else
				return vector<int>({ array[head], array[end] });
		}
		return vector<int>();
	}
};

int main_offer57_1()
{
	vector<int> array({ 1,2,4,7,11,15 });
	Solution s;
	vector<int> temp = s.FindNumbersWithSum(array, 15);
	for (auto &s : temp)
		cout << s << endl;
	return 0;
}
