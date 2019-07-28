/*
输入描述:
第一行包含一个正整数 N，表示树的品种数量。
第二行包含 N 个正整数，第 i (1 <= i <= N) 个数表示第 i 个品种的树的数量。
数据范围：1 <= N <= 1000，1 <= M <= 2000
3
4 2 1

输出描述:
输出一行，包含 M 个正整数，分别表示第 i 棵树的品种编号 (品种编号从1到 N)。
若存在多种可行方案，则输出字典序最小的方案。若不存在满足条件的方案，则输出"-"
1 2 1 2 1 3 1
*/

#include <iostream>
#include <vector>
#include <map>
using namespace std;

int main_pinduoduo2019_2()
{
	int treeTypeNum = 0;
	while (cin >> treeTypeNum)
	{
		map<int, int> treeMap;
		int treeType = 0;
		int treeSum = 0;
		for (int i = 1; i <= treeTypeNum; i++)
		{
			cin >> treeType;
			treeSum += treeType;
			treeMap.insert({ i ,treeType });
		}

		for (auto &s : treeMap)
		{
			if (s.second > treeSum >> 1)
			{
				cout << "-" << endl;
				return 0;
			}
		}

		vector<int> save;
		save.push_back(0);
		for (int i = 1; i <= treeMap.size();)
		{
			if (treeMap[i])
			{
				if (i == save.back())
				{		
					bool flag = false;
					for (int j = i + 1; j <= treeMap.size(); j++)
					{
						if (treeMap[j])
						{
							save.push_back(j);
							//cout << "j:" << j << " ";
							treeMap[j]--;
							flag = true;
							break;
						}
					}
					if (!flag && treeMap[i] != 0)
					{
						//cout << "treeMap[i]:" << treeMap[i] << endl;
						cout << "-" << endl;
						return 0;
					}
				}
				else
				{
					save.push_back(i);
					//cout << "i:" << i << " ";
					treeMap[i]--;
				}
			}
			else
				i++;
		}
		for (auto &s : treeMap)
		{
			if (s.second != 0)
			{
				cout << "-" << endl;
				return 0;
			}
		}
		for (int i = 1; i < save.size(); i++)
			cout << save[i] << " ";
		cout << endl;
		return 0;
	}
}

//686 1 3 1 1 2 5 1 2 2 1 5 4 4 2 1 1 3 1 4 4 1 1 3 2 1 1 2 4 3 3 2 3 1 4 4 1 1 2 1 2 1 2 1 3 2 1 3 3 2 2 2 1 1 1 4 1 1 3 1 1 1 2 5 2 1 1 3 1 1 3 1 2 1 1 1 3 3 1 2 3 2 3 1 2 1 3 1 2 1 1 4 2 3 1 1 1 6 2 1 6 3 6 3 3 1 1 1 1 1 2 2 1 3 1 2 1 1 1 1 1 1 1 1 1 1 3 1 1 1 1 1 2 3 1 1 1 5 1 2 2 1 1 1 2 2 1 4 2 1 1 4 1 4 1 1 2 1 2 2 2 2 2 2 3 2 1 1 1 1 5 1 3 1 1 2 4 3 1 2 1 4 1 2 2 3 4 1 3 2 1 2 3 1 2 4 2 1 1 3 1 4 4 2 4 2 7 1 2 4 3 1 3 1 5 2 1 1 1 2 3 1 1 1 4 1 1 5 1 1 2 1 1 5 3 1 3 2 2 1 1 3 1 1 1 3 2 4 1 1 3 3 3 1 1 1 4 2 2 5 1 6 1 1 1 5 1 2 1 5 5 1 1 3 4 3 1 2 3 2 3 3 5 1 1 2 1 1 1 6 1 1 4 1 1 2 1 1 1 2 1 2 2 1 1 1 1 3 2 1 2 2 1 1 2 2 1 5 3 1 1 3 4 6 1 2 4 1 3 1 2 1 1 1 5 1 1 5 1 2 2 3 1 1 1 2 1 2 1 2 1 1 2 4 2 1 1 2 2 1 4 2 1 1 1 5 3 1 4 2 2 3 2 1 1 3 2 1 2 1 1 2 1 2 3 2 3 2 2 4 4 5 1 2 1 2 1 1 1 1 4 1 1 1 6 2 1 2 3 4 1 2 1 1 3 1 4 1 3 1 1 2 1 2 1 2 2 2 4 2 4 2 1 1 1 1 1 1 2 2 1 4 1 1 4 1 3 1 4 1 2 3 1 1 3 1 1 1 2 2 1 1 1 2 1 5 5 2 2 1 3 6 3 1 4 1 1 4 1 1 2 1 2 2 3 1 7 1 3 1 1 1 1 2 1 3 1 1 2 2 1 1 4 2 3 1 2 1 1 1 3 3 2 1 1 2 1 1 1 5 2 4 5 4 2 2 1 1 2 5 1 1 2 6 1 4 2 3 1 3 2 2 4 5 1 1 2 4 1 3 4 1 1 4 1 1 1 2 5 2 4 1 2 1 2 5 2 2 4 1 1 1 1 4 1 1 1 1 1 3 1 1 4 1 4 2 4 1 1 3 1 1 3 2 1 1 1 1 1 1 2 1 4 1 1 1 1 4 1 1 7 1 3 2 1 3 1 3 5 3 3 3 2 3 2 7 3 1 4 5 1 2 1 2 2 1 1 1 3 4 4 2 2 1 1 1 5 6 2 6 1 2 4 4 3 1 2 6 5 2 4 3 1 2 3 3 1 1 1 2 1 1 3 3 1 5 1 6 2 2 2 1 2 2 1 5 1 