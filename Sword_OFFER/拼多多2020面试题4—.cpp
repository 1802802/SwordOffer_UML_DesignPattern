//#include <bits/stdc++.h>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

//current指当前已经把积木放到这层了，递归函数前面的是检查放到这层合不合理，后面的是找还没有能放的更高的积木
int findbox(vector<vector<int>> &heap, vector<vector<int>> &box, int current)
{
	//1.递归基（检查合理性）
	int maxHeap = current;
	if (current == box.size())
		return box.size() - 1;
	for (int i = 0; i <= current; i++)
	{
		int sum = 0;
		for (int j = i + 1; j <= current; j++)
			sum += heap[j][1];
		//不记得题目要求应该是大于还是大于等于了
		if (sum > (7 * heap[i][1]))
			return current - 1;
	}
	//2.递归函数
	for (int i = 0; i < box.size(); i++)
	{
		if (box[i][0] < heap[current][0] && box[i][2] == 0)
		{
			heap[current + 1][0] = box[i][0];
			heap[current + 1][1] = box[i][1];
			box[i][2] = 1;
			maxHeap = max(maxHeap, findbox(heap, box, current + 1));
			//回溯操作
			box[i][2] = 0;
			heap[current + 1][0] = 0;
			heap[current + 1][1] = 0;
		}
	}
	return maxHeap;
}

int main4444()
{
	//1.数据处理部分
	int m;
	int in;
	while (cin >> m)
	{
		//box为积木数组，heap为堆的积木数组
		vector<vector<int>> box(m);
		vector<vector<int>> heap(m);
		for (int i = 0; i < m; i++)
		{
			cin >> in;
			box[i].push_back(in);
		}
		for (int i = 0; i < m; i++)
		{
			cin >> in;
			box[i].push_back(in);
			box[i].push_back(0); //0表未使用，1表使用
		}
		for (int i = 0; i < m; i++)
		{
			heap[i].push_back(0);
			heap[i].push_back(0);
		}

		//2.算法部分
		int sumMax = 0;
		for (int i = 0; i < box.size(); i++)
		{
			//2.1 初始赋值，循环以每个box为起点
			heap[0][0] = box[i][0];
			heap[0][1] = box[i][1];
			box[i][2] = 1;
			//2.2 递归取值
			sumMax = max(sumMax, findbox(heap, box, 0));
			//2.3 还原数据
			for (auto &s : box)
				s[2] = 0;
			for (auto &s : heap)
			{
				s[0] = 0;
				s[1] = 0;
			}
		}
		//加1的原因是因为数组是从0开始算的，高度是从1开始算的
		cout << sumMax + 1 << endl;
	}
	return 0;
}

//1 2 3 4 5 6 7 8 9 10
//1 1 1 1 1 1 1 1 1 10