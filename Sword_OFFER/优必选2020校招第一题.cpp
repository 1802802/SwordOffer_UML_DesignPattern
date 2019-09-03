//#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

//计算年月日是星期几
int main_ybx111()
{
	int year, month, day;
	while (cin >> year >> month >> day)
	{
		if (month == 1 || month == 2)
		{
			month = month + 12;
			year--;
		}
		int week = (day + 2 * month + 3 * (month + 1) / 5 + year + (year >> 2) - year / 100 + year / 400) % 7 + 1;
		switch (week)
		{
		case 1: {cout << "Monday" << endl; break; }
		case 2: {cout << "Tuesday" << endl; break; }
		case 3: {cout << "Wednesday" << endl; break; }
		case 4: {cout << "Thursday" << endl; break; }
		case 5: {cout << "Friday" << endl; break; }
		case 6: {cout << "Saturday" << endl; break; }
		case 7: {cout << "Sunday" << endl; break; }
		}
	}
	return 0;
}