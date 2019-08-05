//#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

int main_dajiang2()
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
		//Ì°ÐÄ¼ÆËã
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

/*
2 10
1 1 1
1 1 1
3 100
26 100 4
5 1 4
5 2 2
*/