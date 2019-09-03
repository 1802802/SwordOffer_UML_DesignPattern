//#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

int main_ybx222()
{
	int num1, num2;
	while (cin >> num1 >> num2)
	{
		if (num1 == 0 || num2 == 0)
		{
			cout << "No result" << endl;
			continue;
		}
		if (num1 == num2)
		{
			cout << "The result is " << num1 << endl;
			continue;
		}
		int maxnum = max(num1, num2);
		int minnum = min(num1, num2);
		int result = minnum;
		bool flag = false;
		do
		{
			if (maxnum % result == 0 && minnum % result == 0)
			{
				cout << "The result is " << result << endl;
				flag = true;
				break;
			}
		} while (result--);
		if (!flag)
			cout << "No result" << endl;
	}

	return 0;
}