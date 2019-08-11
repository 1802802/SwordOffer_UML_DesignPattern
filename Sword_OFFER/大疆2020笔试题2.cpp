/*
第二题：
输入：多组测试数据
第一行输入两个整数T、N，分别代表钱数和零食种类数。
接下来的N行，每行输入三个整数ai, bi, ci(1 <= i <= N) ，代表零食的价格、零食的满意度、零食的数量
输出：求出最大满意度
case:input
	100 2
	1 1 1
	1 1 1
	100 3
	26 100 4
	5 1 4
	5 2 2
	output
	2
	306
*/

//#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

int main_dajiang2020_2_1()
{
	int N, T;
	while (cin >> N >> T)
	{
		double v, l, c;
		vector<vector<int>> save(N);
		for (int i = 0; i < N; i++)
		{
			cin >> v; cin >> l; cin >> c;
			save[i].push_back(v);
			save[i].push_back(l);
			save[i].push_back(c);
		}
		bool flag = true;
		for (auto &s : save)
		{
			if (s[0] <= T)
				flag = false;
		}
		if (flag)
		{
			cout << 0 << endl;
			continue;
		}

		int currentll = 0;
		//贪心计算
		while (true)
		{
			int maxnum = INT_MAX;
			int maxc = 0;

			for (int i = 0; i < save.size(); i++)
			{
				if (((save[i][0] / save[i][1]) < maxnum) && save[i][2] != 0 && save[i][0] < T)
				{
					maxnum = save[i][0] / save[i][1];
					maxc = i;
				}
			}
			if (maxnum == INT_MAX)
			{
				cout << currentll << endl;
				break;
			}
			currentll += save[maxc][1];
			save[maxc][2]--;
			T -= save[maxc][0];
			if (T <= 0)
			{
				cout << currentll << endl;
				break;
			}
		}


	}

	return 0;
}

struct backpack
{
	int p;  //价格  
	int sat;  //满意度
} 
item[2001];   // 零食列表

int main_dajiang2020_2_2()  //多重背包问题的二进制拆分解法
{
	int money, num;						//money表示总钱数，num表示零食的种类  
	int index = 0;
	int price, satisDegree, curNum;		//拆分后零食的总数 拆分的目的是降低时间复杂度
	int i, j;  int c;					//二进制优化的方法 
	cin >> money >> num;
	for (i = 1; i <= num; i++)
	{
		c = 1;
		cin >> price >> satisDegree >> curNum;       //price表示价格，satisDegree表示满意度，curNum表示该零食的数量。  
		while (curNum - c > 0)     // 1 2 4 8 (1-15) 
		{
			curNum -= c;
			item[++index].p = c*price;
			item[index].sat = c*satisDegree;
			c *= 2;
		}
		item[++index].p = price*curNum;  //补充不足指数的差值  
		item[index].sat = satisDegree*curNum;
	}
	vector<int> dp(money + 1);   //dp[i]代表钱数为i的时候获得的最大满意度  
	for (i = 1; i <= index; i++)   //对拆分后的物品进行0-1背包  
	{
		for (j = money; j >= item[i].p; j--)
			dp[j] = max(dp[j], dp[j - item[i].p] + item[i].sat);
	}
	printf("%d/money", dp[money]);
	return 0;
}
/*
2 10
1 1 1
1 1 1
3 100
26 100 4
5 1 4
5 2 2
*/