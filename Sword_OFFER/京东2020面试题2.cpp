//#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

int main_jd222()
{
	int n, m, x, y;

	while (cin >> n >> m)
	{
		vector<vector<int>> save(2 * n + 1, vector<int>(2 * n + 1, 0));
		vector<int> indeg(2 * n + 1, 0);
		vector<int> out;
		for (int i = 0; i < m; i++)
		{
			cin >> x >> y;
			save[x][y] = 1;
			save[y][x] = 1;
			indeg[x]++;
			indeg[y]++;
		}
		int count = 0;
		while (true)
		{
			int MAX = 0;
			for (int i = 1; i < n + 1; i++)
			{
				if (indeg[i] > indeg[MAX])
					MAX = i;
			}
			if (indeg[MAX] <= 1)
				break;
			else if (MAX <= n)
			{
				for (int i = n + 1; i < 2 * n + 1; i++)
				{
					if (save[MAX][i] == 1 || save[i][MAX] == 1)
						indeg[i]--;
				}
			}
			else if (MAX <= 2 * n)
			{
				for (int i = 1; i < n + 1; i++)
				{
					if (save[i][MAX] == 1 || save[MAX][i] == 1)
						indeg[i]--;
				}
			}
			indeg[MAX] = 0;
			count++;
			out.push_back(MAX);
		}
		cout << count << endl;
		for (auto &s : out)
			cout << s << endl;
	}

	return 0;
}

/*
2 2
1 3
1 4
*/