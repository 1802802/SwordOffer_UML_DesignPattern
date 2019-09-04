// 面试题49—丑数
// 题目：把只包含质因子2、3和5的数称作丑数（Ugly Number）。
// 例如6、8都是丑数，但14不是，因为它包含质因子7。 
// 习惯上我们把1当做是第一个丑数。求按从小到大的顺序的第N个丑数。

#include <queue>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

class Solution 
{
public:
	//1.暴力无脑法（效率堪忧）
	int GetUglyNumber_Solution1(int index) 
	{
		int i = 1;
		int sum = 0;
		while (1)
		{
			int current = i;
			while (current % 2 == 0)
				current /= 2;
			while (current % 3 == 0)
				current /= 3;
			while (current % 5 == 0)
				current /= 5;

			if (current == 1)
				sum++;
			if (index == sum)
				return i;
			i++;
			cout << i << endl;
		}
	}

	//2.采用动态规划，丑数为所有公因子2,3,5的单个无数倍数组成，而其大小即为不同倍数下的数据大小，运行时间：3ms，占用内存：476k
	//所以用2,3,5来不断计算自己的倍数，如果自己的数被选中则倍数+1，由此不断地存储丑数在数组中
	int GetUglyNumber_Solution2(int index)
	{
		if (index < 7)
			return index;
		//先分配内存较好，不然要不断地移动数据到新内存
		vector<int> uglyNumberSave(index);
		uglyNumberSave[0] = 1;
		int times_2 = 0; int times_3 = 0; int times_5 = 0;
		for (int i = 1; i < index; i++)
		{
			//注意这里的等式处理，很灵性，使相乘的因子一直保持只有2,3,5
			int next_2 = uglyNumberSave[times_2] * 2;
			int next_3 = uglyNumberSave[times_3] * 3;
			int next_5 = uglyNumberSave[times_5] * 5;
			//注意min与max函数的参只能有两个，多个的话用initialize_list实现
			//initialize_list作为一个模板类，不仅仅是用作初始化容器类，而且本身也可以单独用作容器使用，只是比较寒碜，只提供了begin(), end(), size()三个方法。
			uglyNumberSave[i] = min({ next_2, next_3, next_5 });
			//三个if连等于，其原因在于需要保证uglynumber前面的数不能出现重复值（即curnum可能有等于多个next的情况）
			if (next_2 == uglyNumberSave[i])
				times_2++;
			if (next_3 == uglyNumberSave[i])
				times_3++;
			if (next_5 == uglyNumberSave[i])
				times_5++;
		}
		return uglyNumberSave[index - 1];
	}
};

// ====================测试代码====================
static void Test(int index, int expected)
{
	Solution s;
	if (s.GetUglyNumber_Solution2(index) == expected)
		printf("solution1 passed\n");
	else
		printf("solution1 failed\n");

	//if (GetUglyNumber_Solution2(index) == expected)
	//	printf("solution2 passed\n");
	//else
	//	printf("solution2 failed\n");
}

int main_offer49(int argc, char* argv[])
{
	Test(1, 1);

	Test(2, 2);
	Test(3, 3);
	Test(4, 4);
	Test(5, 5);
	Test(6, 6);
	Test(7, 8);
	Test(8, 9);
	Test(9, 10);
	Test(10, 12);
	Test(11, 15);

	Test(1500, 859963392);

	Test(0, 0);

	return 0;
}
