//#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

int main_wangyi111()
{
	int T, N, n;
	cin >> T;
	while (cin >> N)
	{
		vector<int> save;
		vector<int> digitSave(32, 0);
		for (int i = 0; i < N; i++)
		{
			cin >> n;
			save.push_back(n);
		}
		for (auto &s : save)
		{
			int cnt = 0;
			for (int i = 0; i < 32; i++)
			{
				if (((s >> i) & 0x1) == 1)
					cnt++;
			}
			digitSave[cnt]++;
		}
		int cnt = 0;
		for (int i = 0; i < 32; i++)
			if (digitSave[i] > 0)
				cnt++;
		cout << cnt << endl;
	}

	return 0;
}