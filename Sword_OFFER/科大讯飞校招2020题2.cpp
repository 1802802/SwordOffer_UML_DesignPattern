#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
using namespace std;

int main_222()
{
	string input;
	while (cin >> input)
	{
		for (auto &s : input)
			if (s == ',')
				s = ' ';
		istringstream in(input);
		int sum1 = 0;
		while (in >> input)
		{
			bool flag = true;
			for (auto &s : input)
			{
				if ((s < '0') || (s > '9'))
				{
					flag = false;
					break;
				}
			}
			if (!flag)
				continue;
			if ((input.size() > 1) && (input.front() >= '0') && (input.back() >= '0') && (input.front() <= '9') && (input.back() <= '9'))
				if ((input.back() - '0') + (input.front() - '0') >= 8)
					sum1++;
		}
		cout << sum1 << endl;
	}

	return 0;
}