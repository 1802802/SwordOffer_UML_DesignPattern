//#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

int main333()
{
	int m, n;
	int in, in2;
	cin >> m >> n;
	vector<int> task;
	map<int,int> taskRelation;
	for (int i = 0; i < m; i++)
	{
		cin >> in;
		task.push_back(in);
	}
	for (int i = 0; i < n; i++)
	{
		cin >> in >> in2;
		if (!taskRelation.insert({ in,1 }).second)
			taskRelation[in]++;
	}



	return 0;
}