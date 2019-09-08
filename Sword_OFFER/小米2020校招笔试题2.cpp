//#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

/*
5
120
40
60
5
15
8000
*/

int minnum = 999999;

void fun(vector <int> &prices, long long money, int cur, int sum)
{
	for (int i = cur; i >= 0; i--)
	{
		int cal_money = money;
		int calsum = sum;
		calsum += (cal_money / prices[i]);
		cal_money = (cal_money % prices[i]);
		if (cal_money == 0)
		{
			minnum = min(minnum, calsum);
			return;
		}
		else
		{
			if (calsum > minnum)
				return;
			fun(prices, cal_money, cur - 1, calsum);
		}
	}
	return;
}

int solution(vector < int > prices, int budget)
{
	sort(prices.begin(), prices.end());
	for (int i = prices.size() - 1; i >= 0; i--)
	{
		long long money = budget;
		int sum = 0;
		fun(prices, money, i, sum);
	}
	if(minnum == 999999)
		return -1;
	return minnum;
}

int main_xiaomi222() {
	int res;

	int _prices_size = 0;
	cin >> _prices_size;
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	vector<int> _prices;
	int _prices_item;
	for (int _prices_i = 0; _prices_i<_prices_size; _prices_i++) {
		cin >> _prices_item;
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		_prices.push_back(_prices_item);
	}


	int _budget;
	cin >> _budget;
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');



	res = solution(_prices, _budget);
	cout << res << endl;

	return 0;

}