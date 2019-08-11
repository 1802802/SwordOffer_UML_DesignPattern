//#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

int main_wangyi333()
{
	int T;
	string input;
	cin >> T;
	while (T--)
	{
		cin >> input;
		vector<int> save;
		int count_N = 0;
		int count_noN = 0;

		//1.对input字符串的数据处理
		for (int i = 0; i < input.size();)
		{
			if (input[i] == 'N')
			{
				i++;
				count_N++;
			}
			else
			{
				save.push_back(count_N);
				count_N = 0;
				for (; i < input.size();)
				{
					if (input[i] != 'N')
					{
						i++;
						count_noN++;
					}
					else
					{
						save.push_back(count_noN);
						count_noN = 0;
						break;
					}
				}
			}
		}
		if (count_N != 0)
		{
			save.push_back(count_N);
			count_N = 0;
		}
		if (count_noN != 0)
		{
			save.push_back(count_noN);
			count_noN = 0;
		}
		save.push_back(0);

		//2.实现算法
		int maxLength = -999;
		int size = save.size();
		for (int i = 0; i < size; i += 2)
		{
			//先全加左边
			if (i - 2 > 0)
			{
				int temp = save[i];
				int flag = 2;
				if (save[i - 1] <= flag)
				{
					temp += save[i - 2];
					temp += save[i - 1];
					flag -= save[i - 1];
				}
				if ((i - 4 > 0) && (save[i - 3] <= flag))
				{
					temp += save[i - 4];
					temp += save[i - 3];
					flag -= save[i - 3];
				}
				maxLength = max(maxLength, temp);
			}

			//再全加右边
			if (i + 2 < size)
			{
				int temp = save[i];
				int flag = 2;
				if (save[i + 1] <= flag)
				{
					temp += save[i + 2];
					temp += save[i + 1];
					flag -= save[i + 1];
				}
				if ((i + 4 < size) && (save[i + 3] <= flag))
				{
					temp += save[i + 4];
					temp += save[i + 3];
					flag -= save[i + 3];
				}
				maxLength = max(maxLength, temp);
			}

			//最后先右再左
			if ((i + 2) < size)
			{
				int temp = save[i];
				int flag = 2;
				if (save[i + 1] <= flag)
				{
					temp += save[i + 2];
					temp += save[i + 1];
					flag -= save[i + 1];
				}
				if ((i - 2 > 0) && (save[i - 1] <= flag))
				{
					temp += save[i - 2];
					temp += save[i - 1];
					flag -= save[i - 1];
				}
				maxLength = max(maxLength, temp);
			}

			//最后先左再右
			if ((i - 2) > 0)
			{
				int temp = save[i];
				int flag = 2;
				if (save[i - 1] <= flag)
				{
					temp += save[i - 2];
					temp += save[i - 1];
					flag -= save[i - 1];
				}
				if ((i + 2 < size) && (save[i + 1] <= flag))
				{
					temp += save[i + 2];
					temp += save[i + 1];
					flag -= save[i + 1];
				}
				maxLength = max(maxLength, temp);
			}

			maxLength = max(save[i], maxLength);
		}
		cout << maxLength << endl;
	}
	return 0;
}