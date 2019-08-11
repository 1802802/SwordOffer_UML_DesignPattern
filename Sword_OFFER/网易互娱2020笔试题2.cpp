//#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

//×´Ì¬»úË¼Ïë
int main_wangyi222()
{
	int T, m, t, m1, t1, m2, t2;
	cin >> T;
	while (T--)
	{
		cin >> m >> t >> m1 >> t1 >> m2 >> t2;
		int currentM = 0;
		bool open = false;
		bool close = false;
		for (int i = 0; i < t; i++)
		{
			if (i%t1 == 0)
				open = 1 - open;
			if (i%t2 == 0)
				close = 1 - close;
			if (open)
				currentM += m1;
			if (close)
				currentM -= m2;
			if (currentM > m)
				currentM = m;
			if (currentM < 0)
				currentM = 0;
		}
		cout << currentM << endl;
	}

	return 0;
}

/*
5
10 2 1 5 2 5
10 2 10 5 2 5
10 2 3 5 2 5
100 100 3 4 4 3
10000 1000 10 5 5 3
*/