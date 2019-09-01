#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <sstream>
using namespace std;

int main_pdd333()
{
	int n, m, k;
	while (cin >> n >> m >> k)
	{
		vector<vector<int>> save(m + 1, vector<int>(n + 1, 0));
		vector<int> temp(m*n, 0);
		for (int i = 1; i < m + 1; i++)
		{
			for (int j = 1; j < n + 1; j++)
			{
				save[i][j] = i * j;
				temp[(i - 1)*m + j - 1] = save[i][j];
			}
		}
		sort(temp.begin(), temp.end(), [](int &a, int &b) {return a > b; });
		cout << temp[k - 1] << endl;
	} 

	return 0;
}

/*
几乎每一个人都用 乘法表。但是你能在乘法表中快速找到第k小的数字吗？

给定高度m 、宽度n 的一张 m * n的乘法表，以及正整数k，你需要返回表中第 k 小的数字。
*/



class Solution
{
public:
	//函数功能：获得在m*n的乘法表中，找出有多少个值 <= num。返回满足条件的值的数量
	int fun(int m, int n, int num)
	{
		int count = 0;
		for (int i = 1; i <= m; ++i) //行从第一行开始
		{
			count += min(num / i, n);//此表达式的含义：num在乘法表的第i行中，有多少个值小于或等于该值（<=num的个数）（这个除i简直神仙思想）
		}
		return count;
	}

	int findKthNumber(int m, int n, int k)
	{
		if (k == 1)
			return 1;
		if (k == m*n)
			return m*n;
		int lo = 1, hi = m*n, mi = 0;
		//跟普通二分不一样，普通二分把下标来当作边界，而这里的二分则是把值来当作边界
		while (lo < hi)
		{
			mi = (lo + hi) >> 1;
			int temp = fun(m, n, mi);
			if (temp < k)
				lo = mi + 1;
			else
				hi = mi;  //核心在于这里的收敛，不直接跳出
			//temp >= k， 在temp>k时，为什么不取 right = mid-1，而是right = mid。
			//因为我们的目标值可能存在重复，比如 123334，如果我选择要找第3小的数，而mid当前恰好=3，那么temp得到的结果会是5（<=mid）。
			//如果我们选择right = mid-1=2。那么将会运行错误导致结果错误。
			//在temp = k时，为什么不能立马返回结果呢，而是继续运行缩小边界？
			//因为我们当前的mid可能是一个不在乘法表中的值，毕竟mid=(left+right) >> 1; 所以立即返回可能返回错误答案。
			//所以一定收缩范围 直到left=right，最终返回的一定是正确值
			//（若答案t的temp = k， 而某一非表值x的temp也=k， 那么t一定比x小，最终x也会被right缩小导致出局）。
		}
		return lo;
	}
};

int main_pdd3_3()
{
	int n, m, k;
	while (cin >> n >> m >> k)
	{
		int find = m*n - k + 1;
		map<int, int> temp;

		for (int i = 1; i < m + 1; i++)
		{
			for (int j = 1; j < n + 1; j++)
			{
				temp[i*j]++;
				if (find--)
					break;
			}
		}
		
		find = m*n;
		for (auto &s : temp)
		{
			find -= s.second;
			if (find < 0)
			{
				cout << s.first << endl;
				break;
			}
		}
	}

	return 0;
}