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


//第三题AC代码
//思想为双指针加上动态窗口的思想
#include<iostream>
#include<cstring>
using namespace std;

int main_wangyi2020_333() 
{
	int T;
	cin >> T;
	string s;
	while (T--)
	{
		cin >> s;
		int len = s.size();
		//i为前指针，j为后指针，flag为修改次数
		int flag = 2, i = 0, j = 0, ans = 0;
		while (j < len)
		{
			if (s[j] == 'N')   
				j++;
			else 
			{
				if (flag > 0)
				{ 
					flag--; j++; 
				}
				else
				{
					ans = max(ans, j - i);
					//当当前j补位N且修改次数用完时，记录当前窗口大小，并前移i直到其释放一个flag后j继续向前
					while (flag == 0)
					{
						if (s[i] == 'N')   
							i++;
						else 
						{ 
							i++; flag++; break; 
						}
					}
				}
			}
		}
		//记住结束时也要处理一下
		ans = max(ans, j - i);
		cout << ans << endl;
	}
	return 0;
}