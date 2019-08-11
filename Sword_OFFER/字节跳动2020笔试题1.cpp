//#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

//80%表示没有考虑到0点换时间的情况
int main_zjtd111()
{
	int N, Hi, Mi, X, A, B;
	while (cin >> N)
	{
		vector<vector<int>> alarm;
		while (N--)
		{
			cin >> Hi >> Mi;
			vector<int> temp({ Hi,Mi });
			alarm.push_back(temp);
		}
		cin >> X;
		cin >> A >> B;

		int lastTime = A * 60 + B - X;
		bool flag = false;

		for (int i = alarm.size() - 1; i >= 0; i--)
		{
			if (alarm[i][0] * 60 + alarm[i][1] <= lastTime)
			{
				cout << alarm[i][0] << " " << alarm[i][1] << endl;
				flag = true;
				break;
			}
		}

		if (!flag)
		{
			lastTime = (A + 24) * 60 + B - X;
			for (int i = alarm.size() - 1; i >= 0; i--)
			{
				if (alarm[i][0] * 60 + alarm[i][1] <= lastTime)
				{
					cout << alarm[i][0] << " " << alarm[i][1] << endl;
					break;
				}
			}
		}
	}

	return 0;
}