/*
题目：
给定一个长度为偶数的数组arr，将该数组中的数字两两配对并求和，在这些和中选出最大和最小值，
请问该如何两两配对，才能让最大值和最小值的差值最小？

输入描述:
一共2行输入。
第一行为一个整数n，2<=n<=10000, 第二行为n个数，组成目标数组，每个数大于等于2，小于等于100。

输出描述:
输出最小的差值。
*/


//#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//思路：先将所有的数字存起来，然后给他们排个序，这样最小的在左边最大的在右边，直接最大最小配对，取配对中的最大值和最小值再相减即可

int main_pinduoduo2019_3()
{
	int n, m;
	cin >> n;
	vector<int> save;
	while (n--)
	{
		cin >> m;
		save.push_back(m);
	}
	
	sort(save.begin(), save.end());
	int maxSum = INT_MIN;
	int minSum = INT_MAX;
	for (int i = 0; i < save.size() / 2; i++)
	{
		maxSum = max(maxSum, save[i] + save[save.size() - 1 - i]);
		minSum = min(minSum, save[i] + save[save.size() - 1 - i]);
	}
	cout << maxSum - minSum << endl;

	return 0;
}