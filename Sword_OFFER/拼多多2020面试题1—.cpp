//#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

int main111()
{
	string a;
	string b;
	int n;
	while (getline(cin, a))
	{
		//1.数据处理
		getline(cin, b);
		vector<int> avector;
		vector<int> bvector;
		istringstream input1(a);	
		while (input1 >> n)
			avector.push_back(n);
		istringstream input2(b);
		while (input2 >> n)
			bvector.push_back(n);

		//2.算法实现
		int errorPlace = -1;
		int findNum = -1;
		int prevNum = INT_MIN;
		int postNum = INT_MAX;

		//2.1错误位置查找
		for (int i = 1; i < avector.size(); i++)
		{
			if (avector[i] < avector[i - 1])
			{
				errorPlace = i;
				prevNum = avector[i - 1];
				if ((i + 1) < avector.size())
					postNum = avector[i + 1];
			}
		}

		//2.2找不到errorPlace则跳出
		if (errorPlace == -1)
		{
			cout << "NO" << endl;
			continue;
		}


		//2.3找到则在数组B中寻找符合条件的最大值
		sort(bvector.begin(), bvector.end());
		
		for (int i = 0; i < bvector.size(); i++)
		{
			if (bvector[i] >= prevNum && bvector[i] <= postNum)
				findNum = bvector[i];
		}

		//2.4找不到findNum则跳出
		if (findNum == -1)
		{
			cout << "NO" << endl;
			continue;
		}

		//2.5将错误值修改并输出
		avector[errorPlace] = findNum;
		for (auto &s : avector)
			cout << s << " ";
		cout << endl;
	}
	return 0;
}

//1 3 7 4 10
//2 1 5 8 9