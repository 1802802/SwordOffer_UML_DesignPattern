//题目：从1-N的数字里选出M个数字组成一个数组，要求每个数字在每个位置的期望相同
#include <iostream>
#include <vector>
#include <random>
#include <time.h>
using namespace std;

//1.思路为借助洗牌算法的完全随机性，选其中的M形成数组
vector<int> NewArray(int n, int m)
{
	if (n < m)
		return vector<int>();

	vector<int> base(n);
	for (int i = 1; i <= n; i++)
		base[i - 1] = i;
	//以下为著名的Knuth-Durstenfeld Shuffle 洗牌算法，注意取余为%(i+1)
	for (int i = n - 1; i >= n - m; i--)
	{
		srand((unsigned)time(NULL));
		swap(base[i], base[rand() % (i + 1)]);
	}
	vector<int> save(m);
	for (int i = n - m, j = 0; i <= n - 1; i++, j++)
		save[j] = base[i];
	return save;
}

int main_zizhu3()
{
	int n = 10;
	int a = 10, b = 5;
	while (n--)
	{
		auto t = NewArray(a, b);
		for (auto &s : t)
			cout << s << " ";
		cout << endl;
	}
	return 0;
}