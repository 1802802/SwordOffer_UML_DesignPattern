//#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

int main_wangyi444()
{
	int n, h, q, qh;
	while (cin >> n)
	{
		vector<int> save1;
		vector<int> save2;
		while (n--)
		{
			cin >> h;
			save1.push_back(h);
		}
		cin >> q;
		while (q--)
		{
			cin >> qh;
			save2.push_back(qh);
		}

		int ans = 0;
		for (auto &s : save2)
		{
			int cnt = 0;
			for (int i = 0; i < save1.size(); i++)
			{
				if (save1[i] - s > 0)
				{
					if (i - 1 > 0 && save1[i - 1] - s > 0)
					{
						if (i + 1 < save1.size() && save1[i + 1] - s > 0)
							cnt++;
						else if (i == save1.size() - 1)
						{
							cnt++;
						}
					}
					else if (i == 0)
					{
						if (i + 1 < save1.size() && save1[i + 1] - s > 0)
							cnt++;
					}
				}
			}
			cout << cnt << endl;
		}
	}

	return 0;
}

