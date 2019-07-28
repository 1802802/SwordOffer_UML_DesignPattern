//#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

int main2222()
{
	string a;
	while (getline(cin, a))
	{
		//1.数据处理
		a.push_back(' ');
		string tmp;
		vector<string> save;
		for (int i = 0; i < a.size(); i++)
		{
			if (a[i] != ' ')
				tmp.push_back(a[i]);
			else
			{
				save.push_back(tmp);
				tmp.clear();
			}
		}

		//2.算法实现
		if (save.size() < 2)
		{
			cout << "false" << endl;
			continue;
		}
		for (int i = 0; i < save.size() - 1; i++)
		{
			map<char, int> same;
			for (auto &s1 : save[i])
			{
				for (auto &s2 : save[i + 1])
				{
					if (s1 == s2)
					{
						if (!same.insert({ s1,1 }).second)
							same[s1]++;
					}
				}
			}
			if (same.size() < 1)
			{
				cout << "false" << endl;
				break;
			}
			else
			{
				bool flag = false;
				for (auto &s : same)
					if (s.second >= 2)
						flag = true;
				if (!flag)
				{
					cout << "false" << endl;
					break;
				}
				cout << "true" << endl;
				break;
			}
		}

	}
	return 0;
}