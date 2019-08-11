//#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

int main_zjtd333()
{
	int N, n;
	while (cin >> N)
	{
		vector<int> save;
		while (N--)
		{
			cin >> n;
			save.push_back(n);
		}
		int sum = 1;
		int cur = 1;
		int i = 1;
		
		//初始为波峰的考虑，找到第一个波谷
		for (; i < save.size() - 1; i++)
		{
			if (save[i] < save[i - 1] && save[i] < save[i + 1])
				break;
		}

		for (int j = i; j > 0;)
		{
			while (j > 0 && save[j] < save[j - 1])
			{
				cur++;
				sum += cur;
				j--;
			}
			while (j > 0 && save[j] == save[j - 1])
			{
				sum += cur;
				j--;
			}
		}

		i++;
		cur = 1; 	

		//这里只考虑了初始为波谷与平坡的情况，还需要考虑初始为波峰
		while (i < save.size())
		{
			while (i < save.size() && save[i - 1] < save[i])
			{
				cur++;
				sum += cur;
				i++;
			}
			while (i < save.size() && save[i - 1] == save[i])
			{
				sum += cur;
				i++;
			}
			while (i < save.size() && save[i - 1] > save[i])
			{
				cur--;
				if (cur <= 0)
					cur = 1;
				sum += cur;
				i++;
			}
		}
		cout << sum * 100 << endl;
	}

	return 0;
}