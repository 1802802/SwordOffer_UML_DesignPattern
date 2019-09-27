#include <iostream>
#include <queue>
#include <deque>
#include <thread>
#include <time.h>
#include <vector>
using namespace std;

int main_nvdia555()
{
	int x, y, z;
	while (cin >> x >> y >> z)
	{
		vector<vector<int>> m1(x, vector<int>(y, 0));
		vector<vector<int>> m2(y, vector<int>(z, 0));
		vector<vector<int>> result(x, vector<int>(z, 0));
		int temp;
		for (int i = 0; i < x; i++)
		{
			for (int j = 0; j < y; j++)
			{
				cin >> temp;
				m1[i][j] = temp;
			}
		}
		for (int i = 0; i < y; i++)
		{
			for (int j = 0; j < z; j++)
			{
				cin >> temp;
				m2[i][j] = temp;
			}
		}
		for (int i = 0; i < x; i++)
		{
			for (int j = 0; j < z; j++)
			{
				for (int t = 0; t < y; t++)
					result[i][j] += m1[i][t] * m2[t][j];
			}
		}
		for (int i = 0; i < x; i++)
		{
			for (int j = 0; j < z; j++)
			{
				cout << result[i][j] << " ";
			}
			cout << endl;
		}
	}
	return 0;
}