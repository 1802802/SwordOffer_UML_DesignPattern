//#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

void insertionsort(vector<vector<int>> &_elem, int lo, int hi)
{
	for (int i = lo + 1, j; i < hi; i++)
	{
		for (j = i; j > lo && _elem[j][1] < _elem[j - 1][1]; j--)
			swap(_elem[j], _elem[j - 1]);
	}
}

int main_jd111()
{
	int N, H;
	while (cin >> N)
	{
		vector<vector<int>> save;
		vector<vector<int>> save2;
		for (int i = 0; i < N; i++)
		{
			cin >> H;
			save.push_back(vector<int>({ i,H }));
		}
		save2 = save;
		insertionsort(save, 0, save.size());
		//这种做法是求最少的，但是题目要求是求最多的
		//int count = 1;
		//for (int i = 0; i < save.size() - 1; i++)
		//{
		//	if (save[i][0] <= save[i + 1][0])
		//		count++;
		//}
		//这种做法是判断排序后前后比较，得到的就是最多的
		int count = 1;
		int sum1 = 0, sum2 = 0;
		for (int i = 0; i < save.size() - 1; i++)
		{
			sum1 += save[i][0];
			sum2 += save2[i][0];
			if (sum1 == sum2)
			{
				count++;
				sum1 = sum2 = 0;
			}
		}
		cout << count << endl;
	}
	return 0;
}