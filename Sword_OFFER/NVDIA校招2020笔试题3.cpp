#include <iostream>
#include <queue>
#include <deque>
#include <thread>
#include <string>
#include <vector>
using namespace std;

bool checkNum(string &input)
{
	int num = 0, Bch = 0, Lch = 0, other = 0;
	for (auto &s : input)
	{
		if (num + Bch + Lch + other >= 3)
			return true;
		if (s >= '0' && s <= '9')
			num = 1;
		else if (s >= 'a' && s <= 'z')
			Lch = 1;
		else if (s >= 'A' && s <= 'Z')
			Bch = 1;
		else
			other = 1;
	}
	return false;
}

bool checkSame(string &input)
{
	for (int i = 0; i < input.size() - 2; i++)
	{
		string temp = input.substr(i, 3);
		for (int j = i + 3; j < input.size() - 2; j++)
		{
			string compare = input.substr(j, 3);
			if (temp == compare)
				return false;
		}
	}
	return true;
}

int main_nvdia333()
{
	string input;
	while (cin >> input)
	{
		if (input.size() <= 8)
		{
			cout << "NG" << endl;
			continue;
		}
		else if (!checkNum(input))
		{
			cout << "NG" << endl;
			continue;
		}
		else if (!checkSame(input))
		{
			cout << "NG" << endl;
			continue;
		}
		else
			cout << "OK" << endl;
	}
	return 0;
}