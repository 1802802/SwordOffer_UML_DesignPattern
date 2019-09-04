// 面试题57.2：为s的连续正数序列
// 题目：输入一个正数s，打印出所有和为s的连续正数序列（至少含有两个数）。
// 例如输入15，由于1+2+3+4+5=4+5+6=7+8=15，所以结果打印出3个连续序列1～5、4～6和7～8。

#include <map>
#include <unordered_map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
#include "BinaryTree.h"
using namespace std;

//思路：双指针法，一前一后，序列和大于s则递增小指针，序列和小于s则递增大指针
//运行时间：5ms，占用内存：616k
class Solution 
{
public:
	vector<vector<int> > FindContinuousSequence(int sum) 
	{
		vector<vector<int>> save;

		int first = 1;
		int second = 2;
		int mix = first + second;

		while (first < second)
		{
			//1.计算当前first到second序列的和大小，大则递增first，小则递增second，相等则存入并双递增
			
			//for (int i = first; i <= second; i++)
			//	mix += i;
			if (mix > sum)
			{
				mix -= first;
				first++;
			}
			else if (mix < sum)
			{
				second++;
				mix += second;
			}
			else
			{
				//2.找到一次序列后加入数组，然后将前后指针均+1
				vector<int> temp;
				for (int i = first; i <= second; i++)
					temp.push_back(i);
				save.push_back(temp);
				first++;
				second++;
				mix += second - first + 1;
			}
		}
		return save;
	}
};

int main_offer57_2()
{
	Solution s;
	auto tmp = s.FindContinuousSequence(15);
	for (auto &s1 : tmp)
	{
		for (auto &s2 : s1)
		{
			cout << s2 << " ";
		}
		cout << endl;
	}

	return 0;
}